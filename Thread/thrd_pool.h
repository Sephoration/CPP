#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

typedef struct thread_pool_t thread_pool_t; // 设置结构体别名
typedef void (*handler_pt)(void *);         // 定义函数指针类型

// 创建线程池
thread_pool_t *thread_pool_create(int thrd_count, int queue_size);

// 销毁线程池
int thread_pool_destroy(thread_pool_t *pool);

// 向线程池中添加任务
int thread_pool_post(thread_pool_t *pool, handler_pt func, void *arg);

// 等待所有任务完成
int wait_all_done(thread_pool_t *pool);

#endif