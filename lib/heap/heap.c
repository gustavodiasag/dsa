#include "heap.h"

#define heap_paren(npos) ((int)(((npos) -1) / 2))

#define heap_left(pos) (((pos) * 2) + 1)

#define heap_right(pos) (((pos) * 2) + 2)

void heap_init(Heap* heap,
               int(*compare)(const void*, const void*),
               void(*destroy)(void*))
{
    heap->_size = 0;
    heap->_tree = NULL;
    heap->_compare = compare;
    heap->_destroy = destroy;
}

void heap_destroy(Heap* heap)
{
    if (heap->_destroy) {
        // Remove each element.
        for (int i = 0; i < heap_size(heap); i++) {
            heap->_destroy(heap->_tree[i]);
        }
    }
    // Free heap.
    free(heap->_tree);
    // Clear structure.
    memset(heap, 0, sizeof(Heap));
}

int heap_insert(Heap* heap, const void* data)
{
    void *tmp;

    if (!(tmp = (void**)realloc(heap->_tree,
                                (heap_size(heap) + 1) * sizeof(void*)))) {
        return -1;
    } else {
        heap->_tree = tmp;
    }
    // Insert node at the last position.
    heap->_tree[heap_size(heap)] = (void*)data;
    // Heapify the tree;
    int ipos = heap_size(heap);
    int ppos = heap_paren(ipos);

    while (ipos > 0 &&
           heap->_compare(heap->_tree[ppos], heap->_tree[ipos]) < 0) {

        tmp = heap->_tree[ppos];
        heap->_tree[ppos] = heap->_tree[ipos];
        heap->_tree[ipos] = tmp;
        // Move up one level.
        ipos = ppos;
        ppos = heap_paren(ipos);
    }
    // Adjust heap size.
    heap->_size++;

    return 0;
}

int heap_extract(Heap* heap, void** data)
{
    void* tmp;
    // Extraction only allowed in a non-empty heap.
    if (!heap_size(heap)) {
        return -1;
    }
    // Extract node at the top of the heap.
    *data = heap->_tree[0];
    // Adjust heap allocation.
    void* save = heap->_tree[heap_size(heap) - 1];

    if (heap_size(heap) - 1 > 0) {
        if (!(tmp = (void**)realloc(heap->_tree,
                                    (heap_size(heap) - 1) * sizeof(void*)))) {
            return -1;
        } else {
            heap->_tree = tmp;
        }
        // Adjust heap size.
        heap->_size--;
    } else {
        // Manage heap when extracting the last node.
        free(heap->_tree);
        init_heap(heap, heap->_compare, heap->_destroy);

        return 0;
    }
    // Copy last node to the top.
    heap->_tree[0] = save;
    // Heapify.
    int ipos, lpos, rpos, mpos;

    while (1) {
        // Select child.
        lpos = heap_left(ipos);
        rpos = heap_right(ipos);

        if (lpos < heap_size(heap) &&
            heap->_compare(heap->_tree[lpos], heap->_tree[ipos]) > 0) {
            
            mpos = lpos;
        } else {
            mpos = ipos;
        }
        if (rpos < heap_size(heap) &&
            heap->_compare(heap->_tree[rpos], heap->_tree[ipos]) > 0) {

            mpos = rpos;
        }
        // When `mpos` is `ipos`, the heap property has been restored.
        if (mpos == ipos) {
            break;
        } else {
            // Swap current node and selected child.
            tmp = heap->_tree[mpos];
            heap->_tree[mpos] = heap->_tree[ipos];
            heap->_tree[ipos] = tmp;
            // Move down one level.
            ipos = mpos;
        }
    }
    return 0;
}