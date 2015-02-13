#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>

#define HOW_LONG 3

#define SUCCESS             0
#define FEW_ARGUMENTS       1
#define FEW_PHILOSOPHER     0
#define ERROR_SEMAPHORE     3
#define ERROR_MEMORY        4
#define ERROR_CREATE_THREAD 5
#define ERROR_CANCEL_THREAD 6

#define CHECK_NOT_NULL(ptr, return_value)                   \
    do                                                      \
    {                                                       \
        if (ptr == NULL)                                    \
        {                                                   \
            printf("ERROR. Code: %d\n", return_value);      \
            return return_value;                            \
        }                                                   \
    } while (0)

int N;
sem_t*  using_forks;

void* philosopher(void* arg)
{
    int id = *((int*) arg);
    while (1)
    {
        printf("Philosopher[%d] finished think.\n", id);
        
        //take right fork        
        sem_wait(&using_forks[id]);
        printf("Philosopher[%d] rate right fork.\n", id);

        //take left fork
        sem_wait(&using_forks[id > 0 ? id-1 : N-1]);
        printf("Philosopher[%d] take left \n", id);
        
        int time1 = rand() % HOW_LONG;
        printf("Philosopher[%d] is eating now.\n", id);
        usleep(time1);
        printf("Philosopher[%d] stopped eating.\n", id);

        //put right  fork       
        sem_post(&using_forks[id]);

        //put left fork
        sem_post(&using_forks[id > 0 ? id-1 : N-1]);
                
        time1 = rand() % HOW_LONG;
        printf("Philosopher[%d] is thinking now.\n", id);
        usleep(time1);
    }
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (argc < 2)
    {
        printf("Few arguments.\n");
        return FEW_ARGUMENTS;
    }

    sscanf(argv[1], "%d", &N);
    if (N < 2)
    {
        printf("Few philosophers.\n");
        return FEW_PHILOSOPHER;
    }

    using_forks = (sem_t*) malloc(N * sizeof(sem_t));
    CHECK_NOT_NULL(using_forks, ERROR_MEMORY);

    int i;
    for (i = 0; i < N; ++i)
    {
        if (sem_init(&(using_forks[i]), 0, 1) == -1)
        {
            printf("Can't create semaphore.\n");
            return ERROR_SEMAPHORE;
        }
    }

    pthread_t *philosophers = (pthread_t*) malloc(N * sizeof(pthread_t));
    CHECK_NOT_NULL(philosophers, ERROR_MEMORY);

    int* id = (int*) malloc(N * sizeof(int));
    CHECK_NOT_NULL(id, ERROR_MEMORY);

    for (i = 0; i < N; i++)
    {
        id[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopher, &id[i]) != 0)
        {
            printf("Error by creating thread.\n");
            return ERROR_CREATE_THREAD;
        }
    }

    sleep(1000);

    for (i = 0; i < N; i++)
    {
        if (philosophers[i] != -1)
        {
            if (pthread_cancel(philosophers[i]) != 0)
            {
                printf("Error cancel thread.\n");
                return ERROR_CANCEL_THREAD;
            }
        }
    }

    free(using_forks);
    free(id);
    free(philosophers);

    return SUCCESS;
}
