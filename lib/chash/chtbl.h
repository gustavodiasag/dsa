#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>

#include "list/list.h"

/** Chained hash-table data structure.*/
typedef struct _CHTbl {
    List*   _table;
    size_t  _buckets;
    size_t  _size;

    int     (*_h)(const void* key);
    int     (*_match)(const void* key1, const void* key2);
    void    (*_destroy)(void* data);
} CHTbl;

/** 
 * Evaluates the number of elements in a chained hash-table specified by
 * `htbl`.
 */
#define chtbl_size(htbl) ((htbl)->_size)

/**
 * Initializes a chained hash-table specified by `htbl`. This operation must be
 * called for a list in order for it to be used in any context.
 * 
 * The `buckets` parameter specifies the number of buckets allocated in the
 * hash table. 
 * 
 * The `h` parameter is a user-defined hash function for the table's keys.
 * 
 * The `match` parameter is a function used by various set operations to
 * determine if two members match. It must return 1 if `key1` is equal to
 * `key2` or 0 otherwise.
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the hash-table stores heap-allocated data. If the hash-table
 * elements do not contain data that must be freed, `destroy` must be set to
 * NULL.
 * 
 * Returns 0 if initializing the hash-table is successfull, or -1 otherwise.
 */
int chtbl_init(CHTbl* htbl,
               size_t buckets,
               int(*h)(const void*),
               int(*match)(const void*, const void*),
               void(*destroy)(void*));

/**
 * Destroys a chained hash-table specified by `htbl`. No operation is allowed
 * to happen in the hash-table after a call to it.
 * 
 * Removes all the elements from the chained hash-table by calling the function
 * `destroy, defined in `chtbl-init`.
 */
void chtbl_destroy(CHTbl* htbl);

/**
 * Inserts an element that contains a pointer to `data` into a chained
 * hash-table specified by `htbl`.
 * 
 * Returns 0 if inserting the element is successfull, 1 if the element is
 * alredy in the chained hash-table, or -1 otherwise.
 */
int chtbl_insert(CHTbl* htbl, const void* data);

/**
 * Removes the element matching `data` from the chained hash-table specified by
 * `htbl`. Once finished, `data` points to the data stored in the element that
 * was removed.
 * 
 * Returns 0 if removing the element is successfull, or -1 otherwise.
 */
int chtbl_remove(CHTbl* htbl, void** data);

/**
 * Determines whether an element matches `data` in a chained hash-table
 * specified by `htbl`. If a match is found, `data` points to the matching data
 * in the chained hash-table.
 * 
 * Returns 0 if the element is found, or -1 otherwise.
 */
int chtbl_lookup(const CHTbl* htbl, void** data);

#endif