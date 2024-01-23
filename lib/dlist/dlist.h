#ifndef DLIST_H
#define DLIST_h

#include <stdlib.h>

/** Individual element of a doubly linked-list. */
typedef struct DListElt DListElt;

/** Doubly linked-list data structure. */
typedef struct DList DList;

/** Evaluates element count of a doubly linked-list specified by `l`. */
#define dlist_size(l) ((l)->_size)

/**
 * Evaluates the element at the head of a doubly linked-list specified by `l`.
 */
#define dlist_head(l) ((l)->_head)

/**
 * Evaluates the element at the tail of a doubly linked-list specified by `l`.
 */
#define dlist_tail(l) ((l)->_tail)

/**
 * Evaluates whether an element specified by `e` is the head of a doubly
 * linked-list.
 */
#define dlist_is_head(e) ((e)->_prev == NULL)

/**
 * Evaluates whether an element specified by `e` is the tail of a doubly
 * linked-list.
 */
#define dlist_is_tail(e) ((e)->_next == NULL)

/** Evaluates the data stored in a list element specified by `e`. */
#define dlist_data(e) ((e)->_data)

/** Evaluates the list element before the one specified by `e`. */
#define dlist_prev(e) ((e)->_prev)

/** Evaluates the list element after the one specified by `elt`. */
#define dlist_next(e) ((e)->_next)

/**
 * Initializes a doubly linked-list specified by `l`.
 *
 * The `destroy` function pointer specifies a way to free allocations when the
 * list stores heap-allocated data. Otherwise, `destroy` must be set to NULL.
 */
void dlist_init(DList* l, void (*destroy)(void*));

/** 
 * Removes the elements and deallocates a doubly linked-list specified by `l`.
 */
void dlist_destroy(DList* l);

/**
 * Inserts an element after the one specified by `e` from a doubly linked-list
 * specified by `l`.
 *
 * Returns 0 if the element is successfully inserted, or -1 otherwise.
 */
int dlist_ins_next(DList* l, DListElt* e, const void* data);

/**
 * Inserts an element before the one specified by `e` from a doubly linked-list
 * specified by `l`.
 *
 * Returns 0 if the element is successfully inserted, or -1 otherwise.
 */
int dlist_ins_prev(DList* l, DListElt* e, const void* data);

/**
 * Removes an element specified by `e` from a doubly linked-list specified by
 * `l`. Once finished, `data` points to the data stored on the element removed.
 *
 * Returns 0 if the element is successfully removed, or -1 otherwise.
 */
int dlist_remove(DList* l, DListElt* e, void** data);

#endif
