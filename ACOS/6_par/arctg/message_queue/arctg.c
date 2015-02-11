#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>

//return
#define FEW_ARGUMENTS 	0
#define	SUCCESS			0
#define ERROR_CHILD		2
#define	ERROR_MQ_UNLINK	5
#define ERROR_OPEN		6
#define ERROR_SEND		7
#define ERROR_RECEIVE	8

#define PI 				3.141592653
#define ITER_COUNT 		50
#define SIZE_BUF		2048
#define NAME_OF_QUEUE 	"/myMessageQueue"

mqd_t mq_deskriptor;
pid_t child[2];

void message_send(double message, int num)
{
	mqd_t mq_deskriptor_send = mq_open(NAME_OF_QUEUE, O_WRONLY);
	if (mq_deskriptor_send == (mqd_t) -1)
	{
		printf("Can't open message queue.\n");
		mq_unlink(NAME_OF_QUEUE);
		exit(ERROR_OPEN);
	}

	char buf[SIZE_BUF];
	sprintf(buf, "%lf", message);
	if (mq_send(mq_deskriptor_send, buf, sizeof(buf), num) != 0)
	{
		printf("Can't send message.\n");
		mq_unlink(NAME_OF_QUEUE);
		exit(ERROR_SEND);	
	}
	mq_close(mq_deskriptor_send);
}

void child_proc(double x, int num, int fd[2])
{
	//inital value
	double k = num ? -x*x*x : x;
	double t = num ? k / 3 : k;

	message_send(t, num); 

	int i;
    for (i = 1; i < ITER_COUNT; ++i)
	{
		k *= x*x*x*x;
		t = k / (num ? (4*i + 3) : (4*i + 1));

		message_send(t, num);
	}
}

double receive_message()
{
	mqd_t mq_deskriptor_receive = mq_open(NAME_OF_QUEUE, O_RDONLY);
	if (mq_deskriptor_receive == (mqd_t) -1)
	{
		printf("Can't open message queue.\n");
		mq_unlink(NAME_OF_QUEUE);
		exit(ERROR_OPEN);
	}
	char buf[SIZE_BUF];

	if (mq_receive(mq_deskriptor_receive, buf, sizeof(buf), NULL) < 0)
	{
		printf("Can't receive message.\n");
		mq_unlink(NAME_OF_QUEUE);
		exit(ERROR_RECEIVE);
	}

	mq_close(mq_deskriptor_receive);
	return atof(buf);
}

double parent_proc()
{
	double sum = 0.0;
	
	int i;
	for (i = 0; i < 2 * ITER_COUNT; ++i)
	{
		sum += receive_message();
	}

	return sum;
}

int main(int argc, char* argv[])
{
  	if (argc < 2)
    {	
        printf("Few arguments.\n");
		return FEW_ARGUMENTS;
	}

	double x = 0.0;
  	double y = 0.0;

  	sscanf(argv[1], "%lf", &x);
  	y = x;

  	//arctg(x) = arccrg(1/x) = arctg(-1/x) + pi/2
  	double dop = 0;
	if ((x >= 0.0 ? x : -x) > 1)
	{
        x = -1/x;
        dop = PI/2;
    }

    int fd[2][2];    

	struct mq_attr messageQueue;
	messageQueue.mq_maxmsg 	= 10;
	messageQueue.mq_msgsize = SIZE_BUF;
	mq_deskriptor = mq_open(NAME_OF_QUEUE, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR, &messageQueue);
	if (mq_deskriptor == (mqd_t) -1)
	{
		printf("Can't open message queue.\n");
		mq_unlink(NAME_OF_QUEUE);
		return ERROR_OPEN;
	}
	mq_close(mq_deskriptor);

	int i;
	for (i = 0; i < 2; ++i)
	{
		child[i] = fork();
		if (child[i] < 0)
		{
			printf("Can't create child.\n");
			return ERROR_CHILD;
		}
		if (child[i] == 0)
		{  
			child_proc(x, i, fd[i]);
		    return 0;
		}
	}

    double res = parent_proc();
	printf("arctg(%lf) =  %lf\n", y, res+dop);

	int status;
    waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
	
	if (mq_unlink(NAME_OF_QUEUE) != 0)
	{
		printf("Error Message Queue unlink.\n");
        return ERROR_MQ_UNLINK;
    }
    return SUCCESS;
}