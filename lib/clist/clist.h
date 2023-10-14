#ifndef CLIST_H
#define CLIST_H

#include <stdlib.h>

/** Individual element of a circular linked-list. */
typedef struct _CListElt {
    void*               _data;
    struct _CListElt*   _next;
} CListElt;

/** Circular linked-list data structure. */
typedef struct _CList {
    size_t      _size;
    CListElt*   _head;

    int         (*_match)(const void* key1, const void* key2);
    void        (*_destroy)(void* data);
} CList;

/** 
 * Evaluates the number of elements in a circular linked-list specified by
 * `list`.
 */
#define clist_size(list) ((list)->_size)

/**
 * Evaluates the element at the head of a circular linked-list specified by
 * `list`.
 */
#define clist_head(list) ((list)->_head)

/** Evaluates the data stored in the element specified by `elt`. */
#define clist_data(elt) ((elt)->_data)

/** Evaluates the element right after the one specified by `elt`. */
#define clist_next(elt) ((elt)->_next)

/**
 * Initializes a circular linked-list specified by `list`. This operation must
 * be called for a list in order for it to be used in any context.
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the list stores heap-allocated data. If the list elements do
 * no contain data that must be freed, `destroy` shall be set to NULL. 
 */
void clist_init(CList* list, void(*destroy)(void*));

/**
 * Destroys a doubly linked-list specified by `list`. No operation is allowed
 * to happen in a list after a call to it.
 * 
 * Removes all the elements from the doubly linked-list calling the function
 * `destroy, defined in `list-init`.
 */
void clist_destroy(CList* list);

/**
 * Inserts an element right after the one specified by `elt` from a circular
 * linked-list specified by `list`. 
 * 
 * Returns 0 if the element is successfully inserted, or -1 otherwise.
 */
int clist_ins_next(CList* list, CListElt* elt, const void* data);

/**
 * Removes the element right after the one specified by `elt` from a circular
 * linked-list specified by `list`. Once finished, `data` points to the data
 * stored on the element removed.
 * 
 * Returns 0 if the element is successfully removed, or -1 otherwise.
 */
int clist_rm_next(CList* list, CListElt* elt, void** data);

#endif