#include <math.h>
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
#define EXP 			2.718281828459045

#define ITER_COUNT 		50

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

pid_t arc_child[2];
volatile sig_atomic_t arc_flag[2] = {0,0};

void arc_signal_handler_0(int signo)
{
	arc_flag[0] = 1;
}

void arc_signal_handler_1(int signo)
{
    arc_flag[1] = 1;
}
 
void arc_start_handler()
{
	if (signal(SIGUSR1, arc_signal_handler_0) == SIG_ERR)
	{
		printf("Signal SIGUSR1.\n");
		exit(ERROR_SIG);
	}

	if (signal(SIGUSR2, arc_signal_handler_1) == SIG_ERR)
	{
        printf("Signal SIGUSR2.\n");
        exit(ERROR_SIG);
    }
}	

void arc_wait_parent(int num)
{
	while (arc_flag[num == 0 ? 0 : 1] == 0)
	{
	}
	arc_flag[num == 0 ? 0 : 1] = 0;
}

void arc_child_proc(double x, int num, int fd[2])
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
		arc_wait_parent(num); 
		
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

pid_t arc_wait_child(int* signal_num)
{
    while ((arc_flag[0] == 0) && (arc_flag[1] == 0))
    {
    }

    int t = arc_flag[0];

	*signal_num = t ? SIGUSR1 : SIGUSR2;
	arc_flag[t ? 0 : 1] = 0;
	return arc_child[t ? 0 : 1];
	
}

double arc_get_result(int fd)
{
    double res;
    if (read(fd, &res, sizeof(double)) != sizeof(double))
    {
        printf("Read error.\n");
        exit(ERROR_READ);
    }
    return res;
}

double arc_parent_proc(int fd[2][2])
{
	int signal_num;
	pid_t child_id;
	double sum = 0.0;
	
	int i;
	for (i = 0; i < 2 * ITER_COUNT; ++i)
	{
		child_id = arc_wait_child(&signal_num);
		sum += arc_get_result(fd[(arc_child[0] == child_id) ? 0 : 1][0]);
		kill(child_id, signal_num);
	}

	return sum;
}

double arctg(double x)
{
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
			exit(ERROR_PIPE);
		}
	}

	arc_start_handler();

	for (i = 0; i < 2; ++i)
	{
		arc_child[i] = fork();
		if (arc_child[i] < 0)
		{
			printf("Can't create child.\n");
			exit(ERROR_CHILD);
		}
		if (arc_child[i] == 0)
		{  
			arc_child_proc(x, i, fd[i]);
		    exit(0);
		}
	}

    double res = arc_parent_proc(fd);
	res += dop;
		
	int status;
    waitpid(arc_child[0], &status, 0);
	waitpid(arc_child[1], &status, 0);

	return res;
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
    x--;
	//inital value
	int signal_num = num ? SIGUSR2 : SIGUSR1;
	double k = num ? -x*x : x;
	double t = num ? k / 2 : k;

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
		
		k *= x*x;
		t = k / (num ? (2*i + 2) : (2*i + 1));

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
	
	double fi = ((a == 0) ? 0 : arctg(b/a));
	res += k;
	printf("Ln(%lf + i*%lf) =  %lf + i*%lf\n", a, b, res, fi);
    return SUCCESS;
}