#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/** Individual element of a singly linked-list. */
typedef struct ListElt ListElt;

/** Singly linked-list data structure. */
typedef struct List List;

/** Evaluates element count of a singly linked-list specified by `l`. */
#define list_size(l) ((l)->_size)

/**
 * Evaluates the element at the head of a singly linked-list specified by `l`.
 */
#define list_head(l) ((l)->_head)

/**
 * Evaluates the element at the tail of a singly linked-list specified by `l`.
 */
#define list_tail(l) ((l)->_tail)

/**
 * Evaluates whether the element specified by `e` is the head of a singly
 * linked-list specified by `l`.
 */
#define list_is_head(l, e) ((e) == (l)->_head)

/**
 * Evaluates whether the element specified by `e` is the tail of a singly
 * linked-list specified by `l`.
 */
#define list_is_tail(l, e) ((e) == (l)->_tail)

/** Evaluates the data stored in a list element specified by `e`. */
#define list_data(e) ((e)->_data)

/** Evaluates the list element after the one specified by `e`. */
#define list_next(e) ((e)->_next)

/**
 * Initializes a singly linked-list specified by `l`.
 *
 * The `destroy` function pointer specifies a way to free allocations when the
 * list stores heap-allocated data. Otherwise, `destroy` must be set to NULL.
 */
void list_init(List* l, void (*destroy)(void*));

/** Removes the elements and deallocates a linked-list specified by `l`. */
void list_destroy(List* l);

/**
 * Inserts an element after the one specified by `e` from a singly linked-list
 * specified by `l`. If `e` is NULL, the new element is inserted at the head.
 *
 * Returns 0 if the element is successfully inserted, or -1 otherwise.
 */
int list_ins_next(List* l, ListElt* e, const void* data);

/**
 * Removes the element after the one specified by `e` from a singly linked-list
 * specified by `l`. If `elt` is NULL, the element at the head is removed. Once
 * finished, `data` points to the data stored on the element removed.
 *
 * Returns 0 if the element is successfully removed, or -1 otherwise.
 */
int list_rm_next(List* l, ListElt* e, void** data);

#endif