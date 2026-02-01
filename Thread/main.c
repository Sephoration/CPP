#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "thrd_pool.h"

int nums = 0;
int done = 0;

pthread_mutex_t lock;

void do_task(void *arg)
{
    usleep(100000);
    pthread_mutex_lock(&lock);
    done++;
    printf("doing %d task\n", done);
    pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv)
{
    int thread = 8;
    int queue_size = 256;

    pthread_mutex_init(&lock, NULL);

    thread_pool_t *pool = thread_pool_create(thread, queue_size);

    if (pool == NULL)
    {
        printf("thread pool create failed\n");
        return 1;
    }

    while (thread_pool_post(pool, do_task, NULL) == 0)
    {
        pthread_mutex_lock(&lock);
        nums++;
        pthread_mutex_unlock(&lock);
    }

    printf("total %d tasks\n", nums);

    wait_all_done(pool);

    printf("did %d tasks\n", done);
    thread_pool_destroy(pool);

    pthread_mutex_destroy(&lock);
    return 0;
}
