
#include <stdlib.h>
#include <pthread.h>
#include "area51/blockingQueue.h"
#include "area51/threadpool.h"

void threadpool_submit(struct thread_pool *pool, struct Node *job) {
    blockingqueue_add(&pool->queue, job);
}
