#include "dlist.h"

#include <string.h>

typedef struct _DListElt
{
    void*               _data;
    struct _DListElt*   _prev;
    struct _DListElt*   _next;
} DListElt;

typedef struct
{
    size_t      _size;
    DListElt*   _head;
    DListElt*   _tail;

    int         (*_match)(const void*, const void*);
    void        (*_destroy)(void*);
} DList;

void dlist_init(DList* l, void (*destroy)(void*))
{
    l->_size = 0;
    l->_head = NULL;
    l->_tail = NULL;
    l->_destroy = destroy;
}

void dlist_destroy(DList* l)
{
    void* data;
    /* Remove each element. */
    while (dlist_size(l) > 0) {
        if (!dlist_remove(l, dlist_tail(l), (void**)&data) &&
            l->_destroy) {
            /* Call the user-defined function for dynamic allocated data. */
            l->_destroy(data);
        }
    }
    /* Clear structure. */
    memset(l, 0, sizeof(DList));
}

int dlist_ins_next(DList* l, DListElt* e, const void* data)
{
    DListElt* new;
    /* Do not allow a NULL element when a list is not empty. */
    if (!e && dlist_size(l)) {
        return -1;
    }
    // Allocate memory for the new element.
    if (!(new = (DListElt*)malloc(sizeof(DListElt)))) {
        return -1;
    }
    new->_data = (void*)data;

    if (!dlist_size(l)) {
        /* Deal with the case where the list is empty. */
        l->_head = new;
        l->_head->_prev = NULL;
        l->_head->_next = NULL;
        l->_tail = new;
    } else {
        new->_next = e->_next;
        new->_prev = e;

        if (!e->_next) {
            l->_tail = new;
        } else {
            e->_next->_prev = new;
        }
        e->_next = new;
    }
    /* Adjust list size. */
    l->_size++;

    return 0;
}

int dlist_ins_prev(DList* l, DListElt* e, const void* data)
{
    DListElt* new;

    if (!e && dlist_size(l)) {
        return -1;
    }
    if (!(new = (DListElt*)malloc(sizeof(DListElt)))) {
        return -1;
    }
    new->_data = (void*)data;

    if (!dlist_size(l)) {
        l->_head = new;
        l->_head->_prev = NULL;
        l->_head->_next = NULL;
        l->_tail = new;
    } else {
        new->_prev = e->_prev;
        new->_next = e;

        if (!e->_prev) {
            l->_head = new;
        } else {
            e->_prev->_next = new;
        }
        e->_prev = new;
    }
    l->_size++;

    return 0;
}

int dlist_remove(DList* l, DListElt* e, void** data)
{
    /* Deletion is only allowed in a non-empty list. */
    if (!e || !dlist_size(l)) {
        return -1;
    }
    *data = e->_data;

    if (e == l->_head) {
        /* Head deletion. */
        l->_head = e->_next;

        if (!l->_head) {
            l->_tail = NULL;
        } else {
            e->_next->_prev = NULL;
        }
    } else {
        /* Deletion on the rest of the list. */
        e->_prev->_next = e->_next;

        if (!e->_next) {
            l->_tail = e->_prev;
        } else {
            e->_next->_prev = e->_prev;
        }
    }
    /* Free the memory allocated for the abstract data type. */
    free(e);
    /* Adjust list size. */
    l->_size--;

    return 0;
}