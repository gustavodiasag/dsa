#include "chtbl.h"

#include <string.h>

typedef struct
{
    List* _table;
    size_t _buckets;
    size_t _size;

    int (*_hash)(const void*);
    int (*_match)(const void*, const void*);
    void (*_destroy)(void*);
} CHTbl;

int chtbl_init(CHTbl* h, size_t buckets, int (*hash)(const void*),
               int (*match)(const void*, const void*), void (*destroy)(void*))
{
    if (!(h->_table = (List*)malloc(sizeof(List)))) {
        return -1;
    }
    h->_buckets = buckets;

    for (size_t i = 0; i < h->_buckets; i++) {
        list_init(&h->_table[i], destroy);
    }
    h->_hash = hash;
    h->_match = match;
    h->_destroy = destroy;
    h->_size = 0;
}

void chtbl_destroy(CHTbl* h)
{
    /* Remove each element. */
    for (size_t i = 0; i < h->_buckets; i++) {
        list_destroy(&h->_table[i]);
    }
    /* Free table. */
    free(h->_table);
    /* Clear structure. */
    memset(h, 0, sizeof(CHTbl));
}

int chtbl_insert(CHTbl* h, const void* data)
{
    void* temp;
    size_t bucket;
    size_t retval;

    temp = (void*)data;
    /* If the data is already in the table, nothing is done. */
    if (!chtbl_lookup(h, &temp)) {
        return 1;
    }
    /* Hash the key. */
    bucket = h->_hash(data) % h->_buckets;
    /* Insert data into the bucket. */
    if (!(retval = list_ins_next(&h->_table[bucket], NULL, data))) {
        h->_size++;
    }
    return retval;
}

int chtbl_remove(CHTbl* h, void** data)
{
    ListElt* elt;
    ListElt* prev;
    size_t bucket;
    /* Hash the key. */
    bucket = h->_hash(data) % h->_buckets;
    /* Search for the data in the bucket. */
    prev = NULL;
    for (elt = list_head(&h->_table[bucket]); elt; elt = list_next(elt)) {
        if (h->_match(*data, list_data(elt))) {
            /* Remove data from the bucket. */
            if (!list_rm_next(&h->_table[bucket], prev, data)) {
                h->_size--;
                return 0;
            } else {
                return -1;
            }
        }
        prev = elt;
    }
    /* Data not found. */
    return -1;
}

int chtbl_lookup(const CHTbl* h, void** data)
{
    ListElt* elt;
    size_t bucket;
    /* Hash the key. */
    bucket = h->_hash(data) % h->_buckets;
    /* Search for the data in the bucket. */
    for (elt = list_head(&h->_table[bucket]); elt; elt = list_next(elt)) {
        if (h->_match(*data, list_data(elt))) {
            /* Pass back data from the table. */
            *data = list_data(elt);
            return 0;
        }
    }
    /* Data not found. */
    return -1;
}