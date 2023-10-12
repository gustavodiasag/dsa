#ifndef DLIST_H
#define DLIST_h

#include <stdlib.h>

/** Individual element of the doubly linked-list. */
typedef struct _DListElt {
    void*               _data;
    struct _DListElt*   _prev;
    struct _DListElt*   _next;
} DListElt;

/** Doubly linked-list data structure. */
typedef struct _DList {
    size_t      _size;
    DListElt*   _head;
    DListElt*   _tail;
    
    int         (*_match)(const void* key1, const void* key2);
    void        (*_destroy)(void* data);
} DList;

/** 
 * Evaluates the number of elements in a doubly linked-list specified by
 * `list`.
 */
#define dlist_size(list) ((list)->_size)

/**
 * Evaluates the element at the head of a doubly linked-list specified by
 * `list`.
 */
#define dlist_head(list) ((list)->_head)

/**
 * Evaluates the element at the tail of a doubly linked-list specified by
 * `list`.
 */
#define dlist_tail(list) ((list)->_tail)

/** 
 * Evaluates whether the element specified by `elt` is the head of a doubly
 * linked-list.
 */
#define dlist_is_head(elt) ((elt)->_prev == NULL)

/**
 * Evaluates whether the element specified by `elt` is the tail of a doubly
 * linked-list.
 */
#define dlist_is_tail(elt) ((elt)->_next == NULL)

/** Evaluates the data stored in the element specified by `elt`. */
#define dlist_data(elt) ((elt)->_data)

/** Evaluates the element right before the one specified by `elt`. */
#define dlist_prev(elt) ((elt)->_prev)

/** Evaluates the element right after the one specified by `elt`. */
#define dlist_next(elt) ((elt)->_next)

/**
 * Initializes a doubly linked-list specified by `list`. This operation must be
 * called for a list in order for it to be used in any context.
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the list stores heap-allocated data. If the list elements do
 * no contain data that must be freed, `destroy` shall be set to NULL. 
 */
void dlist_init(DList* list, void(*destroy)(void*));

/**
 * Destroys a doubly linked-list specified by `list`. No operation is allowed
 * to happen in a list after a call to it.
 * 
 * Removes all the elements from the doubly linked-list calling the function
 * `destroy, defined in `list-init`.
 */
void dlist_destroy(DList* list);

/**
 * Inserts an element right after the one specified by `elt` from the doubly
 * linked-list specified by `list`. 
 * 
 * Returns 0 if the element is successfully inserted, or -1 otherwise.
 */
int dlist_ins_next(DList* list, DListElt* elt, const void *data);

/**
 * Inserts an element right before the one specified by `elt` from the doubly
 * linked-list specified by `list`. 
 * 
 * Returns 0 if the element is successfully inserted, or -1 otherwise.
 */
int dlist_ins_prev(DList* list, DListElt* elt, const void *data);

/**
 * Removes the element specified by `elt` from the doubly linked-list specified
 * by `list`. Once finished, `data` points to the data stored on the element
 * removed.
 * 
 * Returns 0 if the element is successfully removed, or -1 otherwise. 
 */
int dlist_remove(DList* list, DListElt* elt, void** data);

#endif
