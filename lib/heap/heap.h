#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

/** Heap data structure. */
typedef struct Heap Heap;

/** Evaluates the size of a heap specified by `h`. */
#define heap_size(h) ((h)->_size)

/**
 * Initializes a heap specified by `h`.
 *
 * The `match` function pointer specifies a comparison function for heap
 * elements and `destroy` specifies a way to free allocations when the heap
 * stores heap-allocated data. Otherwise, `destroy` must be set to NULL.
 */
void heap_init(Heap* h, int (*match)(const void*, const void*),
               void (*destroy)(void*));

/** Removes the elements and deallocates a heap specified by `h`. */
void heap_destroy(Heap* h);

/**
 * Inserts an element containing `data` into a heap specified by `h`.
 *
 * Returns 0 if inserting the element is successfull, or -1 otherwise.
 */
int heap_insert(Heap* h, const void* data);

/**
 * Extracts the element at the top of a heap specified by `h`. Once finished,
 * `data` points to the data stored in the node that was extracted.
 *
 * Returns 0 if extracting the node is successfull, or -1 otherwise.
 */
int heap_extract(Heap* h, void** data);

#endif