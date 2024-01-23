#include "heap.h"

#define heap_paren(npos) ((int)(((npos)-1) / 2))

#define heap_left(pos) (((pos)*2) + 1)

#define heap_right(pos) (((pos)*2) + 2)

typedef struct
{
    size_t  _size;
    void**  _tree;

    int     (*_compare)(const void*, const void*);
    void    (*_destroy)(void*);
} Heap;

void heap_init(Heap* h, int (*compare)(const void*, const void*),
               void (*destroy)(void*))
{
    h->_size = 0;
    h->_tree = NULL;
    h->_compare = compare;
    h->_destroy = destroy;
}

void heap_destroy(Heap* h)
{
    if (h->_destroy) {
        /* Remove each element. */
        for (int i = 0; i < heap_size(h); i++) {
            h->_destroy(h->_tree[i]);
        }
    }
    /* Free heap. */
    free(h->_tree);
    /* Clear structure. */
    memset(h, 0, sizeof(Heap));
}

int heap_insert(Heap* h, const void* data)
{
    void* tmp;

    if (!(tmp = (void**)realloc(h->_tree,
                                (heap_size(h) + 1) * sizeof(void*)))) {
        return -1;
    } else {
        h->_tree = tmp;
    }
    /* Insert node at the last position. */
    h->_tree[heap_size(h)] = (void*)data;
    /* Heapify the tree; */
    int ipos = heap_size(h);
    int ppos = heap_paren(ipos);

    while (ipos > 0 &&
           h->_compare(h->_tree[ppos], h->_tree[ipos]) < 0) {
        tmp = h->_tree[ppos];
        h->_tree[ppos] = h->_tree[ipos];
        h->_tree[ipos] = tmp;
        /* Move up one level. */
        ipos = ppos;
        ppos = heap_paren(ipos);
    }
    /* Adjust heap size. */
    h->_size++;

    return 0;
}

int heap_extract(Heap* h, void** data)
{
    void* tmp;
    /* Extraction only allowed in a non-empty heap. */
    if (!heap_size(h)) {
        return -1;
    }
    /* Extract node at the top of the heap. */
    *data = h->_tree[0];
    /* Adjust heap allocation. */
    void* save = h->_tree[heap_size(h) - 1];

    if (heap_size(h) - 1 > 0) {
        if (!(tmp = (void**)realloc(h->_tree,
                                    (heap_size(h) - 1) * sizeof(void*)))) {
            return -1;
        } else {
            h->_tree = tmp;
        }
        /* Adjust heap size. */
        h->_size--;
    } else {
        /* Manage heap when extracting the last node. */
        free(h->_tree);
        init_heap(h, h->_compare, h->_destroy);

        return 0;
    }
    /* Copy last node to the top. */
    h->_tree[0] = save;
    /* Heapify. */
    int ipos, lpos, rpos, mpos;

    while (1) {
        /* Select child. */
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);

        if (lpos < heap_size(h) &&
            h->_compare(h->_tree[lpos], h->_tree[ipos]) > 0) {
            mpos = lpos;
        } else {
            mpos = ipos;
        }
        if (rpos < heap_size(h) &&
            h->_compare(h->_tree[rpos], h->_tree[ipos]) > 0) {
            mpos = rpos;
        }
        /* When `mpos` is `ipos`, the heap property has been restored. */
        if (mpos == ipos) {
            break;
        } else {
            /* Swap current node and selected child. */
            tmp = h->_tree[mpos];
            h->_tree[mpos] = h->_tree[ipos];
            h->_tree[ipos] = tmp;
            /* Move down one level. */
            ipos = mpos;
        }
    }
    return 0;
}