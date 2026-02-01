// pool原版 thrd_pool.c

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include "thrd_pool.h"

typedef struct task_t
{
    handler_pt func; // 任务函数指针
    void *arg;       // 任务函数参数
} task_t;

// 任务队列结构体
typedef struct task_queue_t
{
    uint32_t head;
    uint32_t tail;
    uint32_t count;
    task_t *queue;
} task_queue_t;

struct thread_pool_t
{
    pthread_mutex_t mutex;    // 互斥锁
    pthread_cond_t condition; // 任务队列非空条件变量
    pthread_t *threads;       // 线程数组

    task_queue_t task_queue; // 任务队列

    int closed;
    int started;
    int thrd_count;
    int queue_size;
};

static int
thread_pool_free(thread_pool_t *pool);

// 入口函数
static void *
thread_worker(void *arg)
{
    thread_pool_t *pool = (thread_pool_t *)arg;
    task_queue_t *que;
    task_t task;

    for (;;) // 死循环
    {
        pthread_mutex_lock(&pool->mutex);
        que = &pool->task_queue;

        // 虚假唤醒，linux之前的版本，1.可能被信号唤醒，2.业务场景造成

        // 等待任务到来
        while (que->count == 0 && !pool->closed)
        {
            // 先释放 mutex
            // 阻塞在 condition 上，线程就休眠
            // 解除阻塞
            // 加上 mutex
            pthread_cond_wait(&pool->condition, &pool->mutex);
        }

        // 取任务执行任务
        if (pool->closed == 1)
        {
            break;
        }

        // 获取任务
        task = que->queue[que->head];
        que->head = (que->head + 1) % pool->queue_size;
        que->count--;

        // 释放锁
        pthread_mutex_unlock(&pool->mutex);

        // 执行任务
        (*(task.func))(task.arg);
    }

    pool->started--;
    pthread_mutex_unlock(&pool->mutex);
    pthread_exit(NULL);
    return NULL;
}

// 创建线程池
thread_pool_t *
thread_pool_create(int thrd_count, int queue_size)
{
    // 新建线程池指针
    thread_pool_t *pool;

    // 参数检查
    if (thrd_count <= 0 || queue_size <= 0)
    {
        return NULL;
    }

    // 分配内存
    pool = (thread_pool_t *)malloc(sizeof(*pool));
    if (pool == NULL)
    {
        return NULL;
    }

    pool->closed = pool->started = 0;
    pool->thrd_count = 0;
    pool->queue_size = queue_size;

    // 初始化任务队列
    pool->task_queue.head = pool->task_queue.tail = pool->task_queue.count = 0;
    pool->task_queue.queue = (task_t *)malloc(sizeof(task_t) * queue_size);
    if (pool->task_queue.queue == NULL)
    {
        free(pool);
        return NULL;
    }

    // 分配线程数组内存
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thrd_count);
    if (pool->threads == NULL)
    {
        free(pool->task_queue.queue);
        free(pool);
        return NULL;
    }

    int i = 0;
    for (; i < thrd_count; i++)
    {
        if (pthread_create(&pool->threads[i], NULL, thread_worker, (void *)pool) != 0)
        {
            thread_pool_free(pool);
            return NULL;
        }

        pool->thrd_count++;
        pool->started++;
    }

    pthread_mutex_init(&pool->mutex, NULL); // 初始化互斥锁
    pthread_cond_init(&pool->condition, NULL);
    return pool;
}

static int
thread_pool_free(thread_pool_t *pool)
{
    if (pool == NULL || pool->started <= 0)
    {
        return -1;
    }

    // 释放内存
    if (pool->threads)
    {
        free(pool->threads);
        pool->threads = NULL;

        pthread_mutex_lock(&pool->mutex);
        pthread_mutex_destroy(&pool->mutex);
        pthread_cond_destroy(&pool->condition);
    }

    if (pool->task_queue.queue)
    {
        free(pool->task_queue.queue);
        pool->task_queue.queue = NULL;
    }

    // free(pool);
    thread_pool_free(pool);
    return 0;
}

// 销毁线程池
int thread_pool_destroy(thread_pool_t *pool)
{
    if (pool == NULL)
    {
        return -1;
    }

    // 互斥锁
    if (pthread_mutex_lock(&pool->mutex) != 0)
    {
        return -2;
    }

    if (pool->closed == 1)
    {
        return -1;
    }

    pool->closed = 1;

    if (pthread_cond_broadcast(&pool->condition) != 0 || pthread_mutex_unlock(&pool->mutex) != 0)
    {
        pthread_mutex_unlock(&pool->mutex);
        return -2;
    }

    wait_all_done(pool);
    thread_pool_free(pool);
    return 0;
}

// 向线程池中添加任务
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

    if (pthread_cond_signal(&pool->condition) != 0 || pthread_mutex_unlock(&pool->mutex) != 0)
    {
        return -5;
    }

    pthread_mutex_unlock(&(pool->mutex));
    return 0;
}

// 向线程池中添加任务
int wait_all_done(thread_pool_t *pool)
{
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
