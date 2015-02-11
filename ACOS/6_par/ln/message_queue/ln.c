#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>

//return
#define FEW_ARGUMENTS 	0
#define	SUCCESS			0
#define ERROR_CHILD		2
#define	ERROR_MQ_UNLINK	5
#define ERROR_OPEN		6
#define ERROR_SEND		7
#define ERROR_RECEIVE	8

#define PI 				3.141592653
#define EXP				2.718281828459045
#define ITER_COUNT 		50
#define SIZE_BUF		2048
#define NAME_OF_QUEUE 	"/myMessageQueue"


/*
*
*
*
*
*
*
*
*
*
*
* arctg
*
*
*
*
*
*
*
*
*
*
*/

#define NAME_OF_QUEUE_2 	"/myMessageQueue2"

mqd_t arc_mq_deskriptor;
pid_t arc_child[2];

void arc_message_send(double message, int num)
{
	mqd_t arc_mq_deskriptor_send = mq_open(NAME_OF_QUEUE_2, O_WRONLY);
	if (arc_mq_deskriptor_send == (mqd_t) -1)
	{
		printf("Can't open message queue.\n");
		mq_unlink(NAME_OF_QUEUE_2);
		exit(ERROR_OPEN);
	}

	char buf[SIZE_BUF];
	sprintf(buf, "%lf", message);
	if (mq_send(arc_mq_deskriptor_send, buf, sizeof(buf), num) != 0)
	{
		printf("Can't send message.\n");
		mq_unlink(NAME_OF_QUEUE_2);
		exit(ERROR_SEND);	
	}
	mq_close(arc_mq_deskriptor_send);
}

void arc_child_proc(double x, int num, int fd[2])
{
	//inital value
	double k = num ? -x*x*x : x;
	double t = num ? k / 3 : k;

	arc_message_send(t, num); 
	int i;
    for (i = 1; i < ITER_COUNT; ++i)
	{
		k *= x*x*x*x;
		t = k / (num ? (4*i + 3) : (4*i + 1));
		arc_message_send(t, num);
	}
}

double arc_receive_message()
{
	mqd_t arc_mq_deskriptor_receive = mq_open(NAME_OF_QUEUE_2, O_RDONLY);
	if (arc_mq_deskriptor_receive == (mqd_t) -1)
	{
		printf("Can't open message queue.\n");
		mq_unlink(NAME_OF_QUEUE_2);
		exit(ERROR_OPEN);
	}
	char buf[SIZE_BUF];

	if (mq_receive(arc_mq_deskriptor_receive, buf, sizeof(buf), NULL) < 0)
	{
		printf("Can't receive message.\n");
		mq_unlink(NAME_OF_QUEUE_2);
		exit(ERROR_RECEIVE);
	}

	mq_close(arc_mq_deskriptor_receive);
	return atof(buf);
}

double arc_parent_proc()
{
	double sum = 0.0;
	
	int i;
	for (i = 0; i < 2 * ITER_COUNT; ++i)
	{
		sum += arc_receive_message();
	}

	return sum;
}

double arctg(double x)
{
  	//arctg(x) = arccrg(1/x) = arctg(-1/x) + pi/2
  	printf("%lf\n", x);
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
	arc_mq_deskriptor = mq_open(NAME_OF_QUEUE_2, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR, &messageQueue);
	if (arc_mq_deskriptor == (mqd_t) -1)
	{
		printf("Can't open message queue.\n");
		mq_unlink(NAME_OF_QUEUE_2);
		exit(ERROR_OPEN);
	}
	mq_close(arc_mq_deskriptor);

	int i;
	for (i = 0; i < 2; ++i)
	{
		arc_child[i] = fork();
		if (arc_child[i] < 0)
		{
			printf("Can't create arc_child.\n");
			exit(ERROR_CHILD);
		}
		if (arc_child[i] == 0)
		{  
			arc_child_proc(x, i, fd[i]);
		    exit(0);
		}
	}

    double res = arc_parent_proc();

    int status;
    waitpid(arc_child[0], &status, 0);
	waitpid(arc_child[1], &status, 0);
	
	if (mq_unlink(NAME_OF_QUEUE_2) != 0)
	{
		printf("Error Message Queue unlink.\n");
        exit(ERROR_MQ_UNLINK);
    }
    return res+dop;
}

/*
*
*
*
*
*
*
*
*
*
*
* end arctg
*
*
*
*
*
*
*
*
*
*
*/

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
	x--;
	double k = num ? -x*x : x;
	double t = num ? k / 2 : k;

	message_send(t, num); 

	int i;
    for (i = 1; i < ITER_COUNT; ++i)
	{
		k *= x*x;
		t = k / (num ? (2*i + 2) : (2*i + 1));

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
  	if (argc < 3)
    {	
        printf("Few arguments.\n");
		return FEW_ARGUMENTS;
	}

  	double a = 0.0;
  	double b = 0.0;

  	sscanf(argv[1], "%lf", &a);
	sscanf(argv[2], "%lf", &b);
	
	if ((a == 0) && (b == 00))
	{
		printf("Not exist.\n");
		return SUCCESS;
	}

	//Ln(x) = ln(x) + i(fi + 2*pi*k)
	//Ln(x) = ln(x) + i(fi), k = 0
	double re = sqrt(a*a + b*b);
	double x = re;
	int k = 0;

	//ln(re) = k + ln(x), re = x * e^k;
	while ((((x-1) >= 0) ? (x-1) : (1-x)) > 1)
	{
		k++;
		x /= EXP;
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

	double res = parent_proc(fd);

	int status;
    waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
	
	double fi = ((a == 0) ? 0 : arctg(b/a));
	res += k;
	printf("Ln(%lf + i*%lf) =  %lf + i*%lf\n", a, b, res, fi);

	if (mq_unlink(NAME_OF_QUEUE) != 0)
	{
		printf("Error Message Queue unlink.\n");
        return ERROR_MQ_UNLINK;
    }
    return SUCCESS;
}