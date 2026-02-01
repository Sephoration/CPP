// pool优化版 thrd_pool.c

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include "thrd_pool.h"

typedef struct task_t
{
    handler_pt func;
    void *arg;
} task_t;

typedef struct task_queue_t
{
    uint32_t head;
    uint32_t tail;
    uint32_t count;
    task_t *queue;
} task_queue_t;

struct thread_pool_t
{
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    pthread_t *threads;

    task_queue_t task_queue;

    int closed;
    int started;
    int thrd_count;
    int queue_size;
};

static int thread_pool_free(thread_pool_t *pool);

static void *
thread_worker(void *arg)
{
    thread_pool_t *pool = (thread_pool_t *)arg;
    task_queue_t *que;
    task_t task;

    for (;;)
    {
        pthread_mutex_lock(&pool->mutex);
        que = &pool->task_queue;

        while (que->count == 0 && !pool->closed)
        {
            pthread_cond_wait(&pool->condition, &pool->mutex);
        }

        if (pool->closed == 1)
        {
            pthread_mutex_unlock(&pool->mutex);
            break;
        }

        task = que->queue[que->head];
        que->head = (que->head + 1) % pool->queue_size;
        que->count--;

        pthread_mutex_unlock(&pool->mutex);
        (*(task.func))(task.arg);
    }

    pool->started--;
    pthread_exit(NULL);
    return NULL;
}

thread_pool_t *
thread_pool_create(int thrd_count, int queue_size)
{
    thread_pool_t *pool;

    if (thrd_count <= 0 || queue_size <= 0)
    {
        return NULL;
    }

    pool = (thread_pool_t *)malloc(sizeof(*pool));
    if (pool == NULL)
    {
        return NULL;
    }

    pool->closed = pool->started = 0;
    pool->thrd_count = 0;
    pool->queue_size = queue_size;

    pool->task_queue.head = pool->task_queue.tail = pool->task_queue.count = 0;
    pool->task_queue.queue = (task_t *)malloc(sizeof(task_t) * queue_size);
    if (pool->task_queue.queue == NULL)
    {
        free(pool);
        return NULL;
    }

    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thrd_count);
    if (pool->threads == NULL)
    {
        free(pool->task_queue.queue);
        free(pool);
        return NULL;
    }

    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->condition, NULL);

    int i = 0;
    for (; i < thrd_count; i++)
    {
        if (pthread_create(&pool->threads[i], NULL, thread_worker, (void *)pool) != 0)
        {
            pool->closed = 1;
            pthread_cond_broadcast(&pool->condition);
            pthread_mutex_unlock(&pool->mutex);
            thread_pool_free(pool);
            return NULL;
        }

        pool->thrd_count++;
        pool->started++;
    }

    return pool;
}

static int thread_pool_free(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return -1;
    }

    // 先销毁同步原语
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->condition);

    // 再释放内存
    if (pool->threads)
    {
        free(pool->threads);
    }

    if (pool->task_queue.queue)
    {
        free(pool->task_queue.queue);
    }

    free(pool);
    return 0;
}

int thread_pool_destroy(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return -1;
    }

    pthread_mutex_lock(&pool->mutex);

    if (pool->closed == 1)
    {
        pthread_mutex_unlock(&pool->mutex);
        return -1;
    }

    pool->closed = 1;
    pthread_mutex_unlock(&pool->mutex);

    // 唤醒所有等待的线程
    pthread_cond_broadcast(&pool->condition);

    // 等待所有线程结束
    wait_all_done(pool);

    // 释放资源
    thread_pool_free(pool);
    return 0;
}

int thread_pool_post(thread_pool_t *pool, handler_pt func, void *arg)
{
    if (pool == NULL || func == NULL)
    {
        return -1;
    }

    if (pthread_mutex_lock(&pool->mutex) != 0)
    {
        return -2;
    }

    if (pool->closed == 1)
    {
        pthread_mutex_unlock(&pool->mutex);
        return -3;
    }

    if (pool->queue_size == pool->task_queue.count)
    {
        pthread_mutex_unlock(&pool->mutex);
        return -4;
    }

    task_queue_t *task_queue = &(pool->task_queue);
    task_t *task = &(task_queue->queue[task_queue->tail]);
    task->func = func;
    task->arg = arg;
    task_queue->tail = (task_queue->tail + 1) % pool->queue_size;
    task_queue->count++;

    int signal_ret = pthread_cond_signal(&pool->condition);
    pthread_mutex_unlock(&pool->mutex);

    return (signal_ret == 0) ? 0 : -5;
}

int wait_all_done(thread_pool_t *pool)
{
    if (pool == NULL)
        return 1;

    int i, ret = 0;
    for (i = 0; i < pool->thrd_count; i++)
    {
        if (pthread_join(pool->threads[i], NULL) != 0)
        {
            ret = 1;
        }
    }
    return ret;
}