#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list/list.h"

/** Chained hash table data structure. */
typedef struct CHTbl CHTbl;

/** Evaluates the element count in a hash table specified by `h`. */
#define chtbl_size(h) ((htbl)->_size)

/**
 * Initializes a hash table specified by `h`, with size specified by
 * `buckets`.
 *
 * The function pointer `h` specifies a user-defined hash function for the
 * table's keys, `match` specifies a comparison function for keys and `destroy`
 * specifies a way to free allocations when the table stores heap-allocated
 * data. Otherwise, `destroy` must be set to NULL.
 *
 * Returns 0 if initializing the hash table is successfull, or -1 otherwise.
 */
int chtbl_init(CHTbl* h, size_t buckets, int (*hash)(const void*),
               int (*match)(const void*, const void*),
               void (*destroy)(void*));

/** Removes the entries and deallocates a hash table specified by `h`. */
void chtbl_destroy(CHTbl* h);

/**
 * Inserts an element that contains a pointer to `data` into a hash table
 * specified by `h`.
 *
 * Returns 0 if inserting the element is successfull, 1 if the element is
 * alredy in the chained hash table, or -1 otherwise.
 */
int chtbl_insert(CHTbl* h, const void* data);

/**
 * Removes an entry with key matching `data` from a hash table specified by
 * `h`. Once finished, `data` points to the data stored in the element that
 * was removed.
 *
 * Returns 0 if removing the element is successfull, or -1 otherwise.
 */
int chtbl_remove(CHTbl* h, void** data);

/**
 * Determines whether an element key matches `data` in a hash table specified
 * by `h`. If a match is found, `data` points to the matching data.
 *
 * Returns 0 if the element is found, or -1 otherwise.
 */
int chtbl_lookup(const CHTbl* h, void** data);

#endif