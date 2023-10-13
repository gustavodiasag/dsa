#include <string.h>

#include "clist.h"

void clist_init(CList* list, void(*destroy)(void*))
{
    list->_size = 0;
    list->_head = NULL;
    list->_destroy = destroy;
}

void clist_destroy(CList* list)
{
    void* data;
    // Remove each element.
    while (clist_size(list) > 0) {
        if (!clist_rm_next(list, list->_head, (void**)&data)
            && !list->_destroy) {
            // Call the user-defined function for dynamic allocated data.
            list->_destroy(data);
        }
    }
    // Free list.
    memset(list, 0, sizeof(CList));
}

int clist_ins_next(CList* list, CListElt* elt, const void* data)
{
    CListElt* new;
    // Allocate memory for the new element.
    if (!(new = (CListElt*)malloc(sizeof(CListElt)))) {
        return -1;
    }   
    new->_data = (void*)data;

    if (!clist_size(list)) {
        // Deal with the case where the list is empty.
        new->_next = new;
        list->_head = new;
    } else {
        new->_next = elt->_next;
        elt->_next = new;
    }
    // Adjust list size.
    list->_size++;

    return 0;
}

int clist_rm_next(CList* list, CListElt* elt, void** data)
{
    CListElt* old;
    // Deletion is only allowed in a non-empty list.
    if (!clist_size(list)) {
        return -1;
    }
    *data = elt->_next->_data;

    if (elt->_next == elt) {
        // Handle last element deletion.
        old = elt->_next;
        list->_head = NULL;
    } else {
        old = elt->_next;
        elt->_next = elt->_next->_next;
    }
    // Free the memory allocated for the abstract data type.
    free(old);
    // Adjust list size.
    list->_size--;

    return 0;
}