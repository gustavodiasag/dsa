#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

/** Heap data structure. */
typedef struct _Heap {
    size_t  _size;
    void**  _tree;

    int     (*_compare)(const void* key1, const void* key2);
    void    (*_destroy)(void* data);
} Heap;

/** Evaluates the size of a heap specified by `heap`. */
#define heap_size(heap) ((heap)->_size)

/**
 * Initializes a heap specified by `heap`. This operaetion must be called for a
 * heap in order for it to be used in any context.
 * 
 * The `compare` parameter is a function used by heap operations to compare
 * nodes when reorganizing the heap. This function should return 1 if `key1 >
 * key2`, 0 if `key1 == key2` or -1 if `key1 < key2`.
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the heap stores heap-allocated data. If the hash-table
 * elements do not contain data that must be freed, `destroy` must be set to
 * NULL.
 */
void heap_init(Heap* heap,
               int(*compare)(const void*, const void*),
               void(*destroy)(void*));

/**
 * Destroys a heap specified by `heap`. No operation is allowed to happen in
 * the heap after a call to it.
 */
void heap_destroy(Heap* heap);

/**
 * Inserts a node that contains a pointer to `data` into a heap specified by
 * `heap`.
 * 
 * Returns 0 if inserting the element is successfull, or -1 otherwise.
 */
int heap_insert(Heap* heap, const void* data);

/**
 * Extracts the node at the top of a heap specified by `heap`. Once finished,
 * `data` points to the data stored in the node that was extracted.
 * 
 * Returns 0 if extracting the node is successfull, or -1 otherwise.
 */
int heap_extract(Heap* heap, void** data);

#endif