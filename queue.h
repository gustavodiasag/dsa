#ifndef QUEUE_H
#define QUEUE_h

#include "list.h"

/** Queue data structured implemented as a linked-list. */
typedef List Queue;

/** 
 * Initializes a queue so that it can be used in other operations. Since a
 * queue is a linked-list and requires the same initialization, `queue_init` is
 * defined to `list_init`.
 */
#define queue_init list_init

/** Evaluates the number of elements in a queue specified by `queue`. */
#define queue_size list_size

/** 
 * Evaluates the data stored in the element at the top of a queue specified by
 * `queue`.
 */
#define queue_peek(queue) \
    ((queue)->head ?(queue)->head->data : NULL)

/**
 * Destroys a queue. Sine a queue is a linked-list and requires being destroyed
 * in the same way, `queue_destroy` is defined to `list_destroy`.
*/
#define queue_destroy list_destroy

/**
 * Enqueues an element at the tail of the queue specified by `queue`. The new
 * element contains a pointer to `data`, so the memory referenced by `data`
 * should remain valid as long as the element remains in the queue.
 * 
 * Returns 0 if pushing the element is successfull or -1 otherwise. 
 */
int queue_enqueue(Queue* queue, const void* data);

/**
 * Dequeues an element from the head of the queue specified by `queue`. Once
 * finished, `data` points to the data stored in the element that was dequeued.
 * 
 * Returns 0 if popping the element was successfull or -1 otherwise.
 */
int queue_dequeue(Queue* queue, void** data);

#endif