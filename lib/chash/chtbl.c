#include <string.h>

#include "chtbl.h"

int chtbl_init(CHTbl* htbl, size_t buckets, int(*h)(const void*),
               int(*match)(const void*, const void*),
               void(*destroy)(void*))
{   
    if (!(htbl->_table = (List*)malloc(sizeof(List)))) {
        return -1;
    }
    htbl->_buckets = buckets;

    for (size_t i = 0; i < htbl->_buckets; i++) {
        list_init(&htbl->_table[i], destroy);
    }
    htbl->_h = h;
    htbl->_match = match;
    htbl->_destroy = destroy;
    htbl->_size = 0;
}

void chtbl_destroy(CHTbl* htbl)
{
    // Remove each element.
    for (size_t i = 0; i < htbl->_buckets; i++) {
        list_destroy(&htbl->_table[i]);
    }
    free(htbl->_table);
    // Free table.
    memset(htbl, 0, sizeof(CHTbl));
}

int chtbl_insert(CHTbl* htbl, const void* data)
{
    void* temp;
    size_t bucket;
    size_t retval;

    temp = (void*)data;
    // If the data is already in the table, nothing is done.
    if (!chtbl_lookup(htbl, &temp)) {
        return 1;
    }
    // Hash the key.
    bucket = htbl->_h(data) % htbl->_buckets;
    // Insert data into the bucket.
    if (!(retval = list_ins_next(&htbl->_table[bucket], NULL, data))) {
        htbl->_size++;
    }
    return retval;
}

int chtbl_remove(CHTbl* htbl, void** data)
{
    ListElt* elt;
    ListElt* prev;
    size_t bucket;
    // Hash the key.
    bucket = htbl->_h(data) % htbl->_buckets;
    // Search for the data in the bucket.
    prev = NULL;
    for (elt = list_head(&htbl->_table[bucket]); elt; elt = list_next(elt)) {
        if (htbl->_match(*data, list_data(elt))) {
            // Remove data from the bucket.
            if (!list_rm_next(&htbl->_table[bucket], prev, data)) {
                htbl->_size--;
                return 0;
            } else {
                return -1;
            }
        }
        prev = elt;
    }
    // Data not found.
    return -1;
}

int chtbl_lookup(const CHTbl* htbl, void** data)
{
    ListElt* elt;
    size_t bucket;
    // Hash the key.
    bucket = htbl->_h(data) % htbl->_buckets;
    // Search for the data in the bucket.
    for (elt = list_head(&htbl->_table[bucket]); elt; elt = list_next(elt)) {
        if (htbl->_match(*data, list_data(elt))) {
            // Pass back data from the table.
            *data = list_data(elt);
            return 0;
        }
    }
    // Data not found.
    return -1;
}