#include "list.h"

#include <string.h>

typedef struct ListElt_
{
    void*               _data;
    struct ListElt_*    _next;
} ListElt;

typedef struct
{
    size_t      _size;
    ListElt*    _head;
    ListElt*    _tail;

    int         (*_match)(const void*, const void*);
    void        (*_destroy)(void*);
} List;

void list_init(List* l, void (*destroy)(void*))
{
    l->_size = 0;
    l->_head = NULL;
    l->_tail = NULL;
    l->_destroy = destroy;
}

void list_destroy(List* l)
{
    void* data;
    /* Remove each element. */
    while (list_size(l) > 0) {
        if (!list_rm_next(l, NULL, (void**)&data) && l->_destroy) {
            /* Call the user-defined function for dynamic allocated data. */
            l->_destroy(data);
        }
    }
    /* Clear structure. */
    memset(l, 0, sizeof(List));
}

int list_ins_next(List* l, ListElt* e, const void* data)
{
    ListElt* new;
    /* Allocate memory for the new element. */
    if (!(new = (ListElt*)malloc(sizeof(ListElt)))) {
        return -1;
    }
    new->_data = (void*)data;

    if (!e) {
        /* Head insertion. */
        if (!list_size(l)) {
            l->_tail = new;
        }
        new->_next = l->_head;
        l->_head = new;
    } else {
        /* Insertion on the rest of the list. */
        if (!e->_next) {
            l->_tail = new;
        }
        new->_next = e->_next;
        e->_next = new;
    }
    /* Adjust list size. */
    l->_size++;

    return 0;
}

int list_rm_next(List* l, ListElt* e, void** data)
{
    ListElt* old;
    /* Deletion is only allowed in a non-empty list. */
    if (!list_size(l)) {
        return -1;
    }
    if (!e) {
        /* Head deletion. */
        *data = l->_head->_data;
        old = l->_head;
        l->_head = l->_head->_next;

        if (!list_size(l)) {
            l->_tail = NULL;
        }
    } else {
        /* Deletion on the rest of the list. */
        if (!e->_next) {
            return -1;
        }
        *data = e->_next->_data;
        old = e->_next;
        e->_next = e->_next->_next;

        if (!e->_next) {
            l->_tail = e;
        }
    }
    /* Free the memory allocated for the abstract datatype. */
    free(old);
    /* Adjust list size; */
    l->_size--;

    return 0;
}