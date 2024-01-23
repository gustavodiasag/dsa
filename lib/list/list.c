#include <string.h>

#include "list.h"

void list_init(List* list, void(destroy)(void*))
{
    list->_size = 0;
    list->_head = NULL;
    list->_tail = NULL;
    list->_destroy = destroy;
}

void list_destroy(List* list)
{
    void* data;
    // Remove each element.
    while (list_size(list) > 0) {   
        if (!list_rm_next(list, NULL, (void**)&data) && list->_destroy) {
            // Call the user-defined function for dynamic allocated data.
            list->_destroy(data);
        }
    }
    // Clear structure.
    memset(list, 0, sizeof(list));
}

int list_ins_next(List* list, ListElt* elt, const void* data)
{
    ListElt* new;
    // Allocate memory for the new element.
    if (!(new = (ListElt*)malloc(sizeof(ListElt)))) {
        return -1;
    }
    new->_data = (void*)data;

    if (!elt) {
        // Head insertion.
        if (!list_size(list)) {
            list->_tail = new;
        }
        new->_next = list->_head;
        list->_head = new;
    } else {
        // Insertion on the rest of the list.
        if (!elt->_next) {
            list->_tail = new;
        }
        new->_next = elt->_next;
        elt->_next = new;
    }
    // Adjust list size.
    list->_size++;

    return 0;
}

int list_rm_next(List* list, ListElt* elt, void** data)
{
    ListElt* old;
    // Deletion is only allowed in a non-empty list.
    if (!list_size(list)) {
        return -1;
    }
    if (!elt) {
        // Head deletion.
        *data = list->_head->_data;
        old = list->_head;
        list->_head = list->_head->_next;

        if (!list_size(list)) {
            list->_tail = NULL;
        }
    } else {
        // Deletion on the rest of the list.
        if (!elt->_next) {
            return -1;
        }
        *data = elt->_next->_data;
        old = elt->_next;
        elt->_next = elt->_next->_next;

        if (!elt->_next) {
            list->_tail = elt;
        }
    }
    // Free the memory allocated for the abstract datatype.
    free(old);
    // Adjust list size;
    list->_size--;

    return 0;
}