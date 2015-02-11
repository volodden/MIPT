#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//return
#define FEW_ARGUMENTS 	0
#define	SUCCESS			0
#define ERROR_PIPE		1
#define ERROR_CHILD		2
#define ERROR_SIG		3
#define ERROR_WRITE		4
#define ERROR_READ		5

#define PI 				3.141592653

#define ITER_COUNT 		50

pid_t child[2];
volatile sig_atomic_t flag[2] = {0,0};

void signal_handler_0(int signo)
{
	flag[0] = 1;
}

void signal_handler_1(int signo)
{
    flag[1] = 1;
}
 
void start_handler()
{
	if (signal(SIGUSR1, signal_handler_0) == SIG_ERR)
	{
		printf("Signal SIGUSR1.\n");
		exit(ERROR_SIG);
	}

	if (signal(SIGUSR2, signal_handler_1) == SIG_ERR)
	{
        printf("Signal SIGUSR2.\n");
        exit(ERROR_SIG);
    }
}	

void wait_parent(int num)
{
	while (flag[num == 0 ? 0 : 1] == 0)
	{
	}
	flag[num == 0 ? 0 : 1] = 0;
}

void child_proc(double x, int num, int fd[2])
{
    close(fd[0]);

	//inital value
	int signal_num = num ? SIGUSR2 : SIGUSR1;
	double k = num ? -x*x*x : x;
	double t = num ? k / 3 : k;

	if (write(fd[1], &t, sizeof(double)) != sizeof(double))
	{
        printf("Write error.\n");
        exit(ERROR_WRITE);
	}

	kill(getppid(), signal_num);

	int i;
    for (i = 1; i < ITER_COUNT; ++i)
    {
		wait_parent(num); 
		
		k *= x*x*x*x;
		t = k / (num ? (4*i + 3) : (4*i + 1));

		if (write(fd[1], &t, sizeof(double)) != sizeof(double))
    	{
           	printf("Write error.\n");
           	exit(ERROR_WRITE);
		}

		kill(getppid(), signal_num);
	}
}

pid_t wait_child(int* signal_num)
{
    while ((flag[0] == 0) && (flag[1] == 0))
    {
    }

    int t = flag[0];

	*signal_num = t ? SIGUSR1 : SIGUSR2;
	flag[t ? 0 : 1] = 0;
	return child[t ? 0 : 1];
	
}

double get_result(int fd)
{
    double res;
    if (read(fd, &res, sizeof(double)) != sizeof(double))
    {
        printf("Read error.\n");
        exit(ERROR_READ);
    }
    return res;
}

double parent_proc(int fd[2][2])
{
	int signal_num;
	pid_t child_id;
	double sum = 0.0;
	
	int i;
	for (i = 0; i < 2 * ITER_COUNT; ++i)
	{
		child_id = wait_child(&signal_num);
		sum += get_result(fd[(child[0] == child_id) ? 0 : 1][0]);
		kill(child_id, signal_num);
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
	
	int i;
	for (i = 0; i < 2; ++i)
	{
		if (pipe(fd[i]) != 0)
		{
			printf("Can't create pipe.\n");
			return ERROR_PIPE;
		}
	}

	start_handler();

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
	
	printf("arctg(%lf) =  %lf\n", y, res+dop);
    return SUCCESS;
}