#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

#define SUCCESS 			0
#define FEW_ARGUMENTS 		1
#define ERROR_READ 			2
#define ERROR_WRITE			3
#define ERROR_CHILD 		4
#define ERROR_CREATE_PIPE	5
#define ERROR_MEMORY		6
#define ERROR_EXEC			7
#define ERROR_DUP2			8

#define CHECK_NOT_NULL(ptr, return_value)                   \
    do                                                      \
    {                                                       \
        if (ptr == NULL)                                    \
        {                                                   \
            printf("ERROR. Code: %d\n", return_value);      \
            return return_value;                            \
        }                                                   \
    } while (0)

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		printf("Few arguments\n");
		return FEW_ARGUMENTS;
	}

	int count_child = argc - 1;
	int count_pipes	= argc - 2;
	int i = 0;

	int** fd = (int**) malloc(count_pipes * sizeof(int*));
	CHECK_NOT_NULL(fd, ERROR_MEMORY);
	for (i = 0; i < count_pipes; ++i)
	{
		fd[i] = (int*) malloc(2 * sizeof(int));
		CHECK_NOT_NULL(fd[i], ERROR_MEMORY);
	}

	for (i = 0; i < count_pipes; ++i)
	{
		if (pipe(fd[i]) != 0)
		{
			printf("Error create pipe.\n");
			return ERROR_CREATE_PIPE;
		}
	}

	pid_t* child = (pid_t*) malloc(count_child * sizeof(pid_t));
	CHECK_NOT_NULL(child, ERROR_MEMORY);

	for (i = 0; i < count_child; ++i)
	{
		child[i] = fork();
		if (child[i] < 0)
		{
			printf("Error create child\n");
			return ERROR_CHILD;
		}

		if (child[i] == 0)
		{
			//printf("%s\n", argv[i+1]);

			int j;
			for (j = 0; j < count_pipes; ++j)
			{
				if (j != i-1)
				{
					close(fd[j][0]);
				}
				if (j != i)
				{
					close(fd[j][1]);
				}
			}

			if (i > 0)
			{
				if (dup2(fd[i-1][0], STDIN_FILENO) == -1)
				{
					return ERROR_DUP2;
				}
				close(fd[i-1][0]);
			}
			if (i < count_pipes)
			{
				if (dup2(fd[i][1], STDOUT_FILENO) == -1)
				{
					return ERROR_DUP2;
				}
				close(fd[i][1]);
			}
			execl("/bin/sh", "sh", "-c", argv[i+1], NULL);
			return 0;
		}
	}

	for (i = 0; i < count_pipes; ++i)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}

//	printf("--> end -->\n");
	int status;
	for (i = 0; i < count_child; ++i)
	{
//		printf("wait2 %d begin\n", i);
		waitpid(child[i], &status, 0);
//		printf("wait2 %d end\n", i);
	}

	for (i = 0; i < count_pipes; ++i)
	{
		free(fd[i]);
	}
	free(fd);
	free(child);

	return SUCCESS;
}
