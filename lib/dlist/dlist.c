#include <string.h>

#include "dlist.h"

void dlist_init(DList* list, void(*destroy)(void*))
{
    list->_size = 0;
    list->_head = NULL;
    list->_tail = NULL;
    list->_destroy = destroy;
}

void dlist_destroy(DList* list)
{
    void* data;
    // Remove each element.
    while (dlist_size(list) > 0) {
        if (!dlist_remove(list, dlist_tail(list), (void**)&data)
            && list->_destroy) {
            // Call the user-defined function for dynamic allocated data.
            list->_destroy(data);
        }
    }
    // Clear structure.
    memset(list, 0, sizeof(DList));
}

int dlist_ins_next(DList* list, DListElt* elt, const void* data)
{
    DListElt* new;
    // Do not allow a NULL element when a list is not empty.
    if (!elt && dlist_size(list)) {
        return -1;
    }
    // Allocate memory for the new element.
    if (!(new = (DListElt*)malloc(sizeof(DListElt)))) {
        return -1;
    }
    new->_data = (void*)data;

    if (!dlist_size(list)) {
        // Deal with the case where the list is empty.
        list->_head = new;
        list->_head->_prev = NULL;
        list->_head->_next = NULL;
        list->_tail = new;
    } else {
        new->_next = elt->_next;
        new->_prev = elt;

        if (!elt->_next) {
            list->_tail = new;
        } else {
            elt->_next->_prev = new;
        }
        elt->_next = new;
    }
    // Adjust list size.
    list->_size++;

    return 0;
}

int dlist_ins_prev(DList* list, DListElt* elt, const void* data)
{
    DListElt* new;
    
    if (!elt && dlist_size(list)) {
        return -1;
    }
    if (!(new = (DListElt*)malloc(sizeof(DListElt)))) {
        return -1;
    }
    new->_data = (void*)data;

    if (!dlist_size(list)) {
        list->_head = new;
        list->_head->_prev = NULL;
        list->_head->_next = NULL;
        list->_tail = new;
    } else {
        new->_prev = elt->_prev;
        new->_next = elt;

        if (!elt->_prev) {
            list->_head = new;
        } else {
            elt->_prev->_next = new;
        }
        elt->_prev = new;
    }
    list->_size++;

    return 0;
}

int dlist_remove(DList* list, DListElt* elt, void** data)
{
    // Deletion is only allowed in a non-empty list.
    if (!elt || !dlist_size(list)) {
        return -1;
    }
    *data = elt->_data;
    
    if (elt == list->_head) {
        // Head deletion.
        list->_head = elt->_next;

        if (!list->_head) {
            list->_tail = NULL;
        } else {
            elt->_next->_prev = NULL;
        }
    } else {
        // Deletion on the rest of the list.
        elt->_prev->_next = elt->_next;

        if (!elt->_next) {
            list->_tail = elt->_prev;
        } else {
            elt->_next->_prev = elt->_prev;
        }
    }
    // Free the memory allocated for the abstract data type.
    free(elt);
    // Adjust list size.
    list->_size--;

    return 0;
}