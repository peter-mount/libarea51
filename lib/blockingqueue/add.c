/**
 * A concurrent linked queue
 */

#include <pthread.h>
#include "area51/blockingQueue.h"
#include <area51/list.h>

void blockingqueue_add(struct blocking_queue *queue, Node *node) {
    pthread_mutex_lock(&queue->mutex);

    list_addTail(&queue->list, node);

    pthread_mutex_unlock(&queue->mutex);

    // Signal waiting threads
    pthread_cond_signal(&queue->condition);
}
