#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

/** Individual element of a circular linked-list. */
typedef struct CListElt CListElt;

/** Circular linked-list data structure. */
typedef struct CList CList;

/** Evaluates the element count of a circular linked-list specified by `l`. */
#define clist_size(l) ((l)->_size)

/**
 * Evaluates the element at the head of a circular linked-list specified by
 * `l`.
 */
#define clist_head(l) ((l)->_head)

/** Evaluates the data stored in a list element specified by `e`. */
#define clist_data(e) ((e)->_data)

/** Evaluates the list element right after the one specified by `e`. */
#define clist_next(e) ((e)->_next)

/**
 * Initializes a circular linked-list specified by `l`.
 *
 * The `destroy` function pointer specifies a way to free allocations when the
 * list stores heap-allocated data. Otherwise, `destroy` must be set to NULL.
 */
void clist_init(CList* l, void (*destroy)(void*));

/** 
 * Removes the elements and deallocates a circular linked-list specified by
 * `l`.
 */
void clist_destroy(CList* l);

/**
 * Inserts an element after the one specified by `e` in a circular linked-list
 * specified by `l`.
 *
 * Returns 0 if the element is successfully inserted, or -1 otherwise.
 */
int clist_ins_next(CList* l, CListElt* e, const void* data);

/**
 * Removes the element after the one specified by `e` from a circular linked-
 * list specified by `l`. Once finished, `data` points to the data stored on
 * the element removed.
 *
 * Returns 0 if the element is successfully removed, or -1 otherwise.
 */
int clist_rm_next(CList* l, CListElt* e, void** data);

#endif