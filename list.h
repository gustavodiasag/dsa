#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct ListElt_ {
    void*               data;
    struct ListElt_*    next;
} ListElt;

typedef struct _List {
    size_t      _size;
    ListElt*    _head;
    ListElt*    _tail;
    
    int         (*_match)(const void*, const void*);
    void        (*_destroy)(void*);
} List;

/** Evaluates the number of elements in a linked-list specified by `list`. */
#define list_size(list) ((list)->_size)

/** Evaluates the element at the head of a linked-list specified by `list`. */
#define list_head(list) ((list)->_head)

/** Evaluates the element at the tail of a linked-list specified by `list`. */
#define list_tail(list) ((list)->_tail)

/** 
 * Evaluates whether the element specified by `elt` is the head of a
 * linked-list specified by `list`.
 */
#define list_is_head(list, elt) ((elt) == (list)->_head)

/**
 * Evaluates whether the element specified by `elt` is the tail of a
 * linked-list specified by `list`.
 */
#define list_is_tail(list, elt) ((elt) == (list)->_tail)

/** Evaluates the data stored in the element specified by `elt`. */
#define list_data(elt) ((elt)->data)

/** Evaluates the element right after the one specified by `elt`. */
#define list_next(elt) ((elt)->next)

/**
 * Initializes the linked-list specified by `list`. This operation must be
 * called for a list in order for it to be used in any context.
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the list stores heap-allocated data. If the list elements do
 * no contain data that must be freed, `destroy` shall be set to NULL. 
 */
void list_init(List* list, void(destroy)(void*));

/**
 * Destroys the linked-list specified by `list`. No operation is allowed to
 * happen in a list after a call to it.
 * 
 * Removes all the elements from the linked-list calling the function `destroy,
 * defined in `list-init`.
 */
void list_destroy(List* list);

/**
 * Inserts an element right after the one specified by `elt` from the
 * linked-list specified by `list`. If `element` is NULL, the new element is
 * inserted at the head of the list. 
 * 
 * Returns 0 if the element is successfully inserted, or -1 otherwise.
 */
int list_ins_next(List* list, ListElt* elt, const void* data);


/**
 * Removes the element right after the one specified by `elt` from the
 * linked-list specified by `list`. If `elt` is NULL, the element at the head
 * of the list is removed. Once finished, `data` points to the data stored on
 * the element removed.
 * 
 * Returns 0 if the element is successfully removed, or -1 otherwise.
 */
int list_rm_next(List* list, ListElt* elt, void** data);

#endif