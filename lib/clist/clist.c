#include "clist.h"

#include <string.h>

typedef struct _CListElt
{
    void*               _data;
    struct _CListElt*   _next;
} CListElt;

typedef struct _CList
{
    size_t      _size;
    CListElt*   _head;

    int         (*_match)(const void*, const void*);
    void        (*_destroy)(void*);
} CList;


void clist_init(CList* l, void (*destroy)(void*))
{
    l->_size = 0;
    l->_head = NULL;
    l->_destroy = destroy;
}

void clist_destroy(CList* l)
{
    void* data;
    /* Remove each element. */
    while (clist_size(l) > 0) {
        if (!clist_rm_next(l, l->_head, (void**)&data) &&
            !l->_destroy) {
            /* Call the user-defined function for dynamic allocated data. */
            l->_destroy(data);
        }
    }
    /* Clear structure. */
    memset(l, 0, sizeof(CList));
}

int clist_ins_next(CList* l, CListElt* e, const void* data)
{
    CListElt* new;
    /* Allocate memory for the new element. */
    if (!(new = (CListElt*)malloc(sizeof(CListElt)))) {
        return -1;
    }
    new->_data = (void*)data;

    if (!clist_size(l)) {
        /* Deal with the case where the list is empty. */
        new->_next = new;
        l->_head = new;
    } else {
        new->_next = e->_next;
        e->_next = new;
    }
    /* Adjust list size. */
    l->_size++;

    return 0;
}

int clist_rm_next(CList* l, CListElt* e, void** data)
{
    CListElt* old;
    /* Deletion is only allowed in a non-empty list. */
    if (!clist_size(l)) {
        return -1;
    }
    *data = e->_next->_data;

    if (e->_next == e) {
        /* Handle last element deletion. */
        old = e->_next;
        l->_head = NULL;
    } else {
        old = e->_next;
        e->_next = e->_next->_next;
    }
    /* Free the memory allocated for the abstract data type. */
    free(old);
    /* Adjust list size. */
    l->_size--;

    return 0;
}