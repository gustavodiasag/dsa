#ifndef QUEUE_H
#define QUEUE_h

#include "list.h"

/** Queue data structured implemented as a linked-list. */
typedef List Queue;

/** Evaluates the element count of a queue specified by `q`. */
#define queue_size list_size

/**
 * Initializes a queue.
 * 
 * Since queues are linked-lists, `queue_init` is defined as `list_init`.
 */
#define queue_init list_init

/**
 * Destroys a queue.
 * 
 * Since queues are linked-lists, `queue_destroy` is defined as `list_destroy`.
 */
#define queue_destroy list_destroy

/** Evaluates the data at the top of a queue specified by `q`. */
#define queue_peek(q) ((q)->head ? (q)->head->data : NULL)

/**
 * Enqueues an element on a queue specified by `q`.
 *
 * Returns 0 if queueing the element is successfull, or -1 otherwise.
 */
int queue_enqueue(Queue* q, const void* data);

/**
 * Dequeues an element from a queue specified by `q`. Once finished, `data`
 * points to the data stored in the element that was dequeued.
 *
 * Returns 0 if popping the element was successfull, or -1 otherwise.
 */
int queue_dequeue(Queue* q, void** data);

#endif