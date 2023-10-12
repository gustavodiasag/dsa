#include "cover.h"

/** Structure for subsets identified by a key. */
typedef struct _KSet {
    Set     set; 
    void*   key;
} KSet;

int cover(Set* members, Set* subsets, Set* covering)
{
    Set intersec;
    KSet* subset;
    ListElt* mem;
    ListElt* max_mem;
    void* data;
    size_t max_size;
    // Initialize covering.
    set_init(covering, subsets->_match, NULL);

    while (set_size(members) > 0 && set_size(subsets) > 0) {
        // Find the subset that covers most members.
        max_size = 0;

        for (mem = list_head(subsets); mem; mem = list_next(mem)) {
            if (set_intersec(
                    &intersec, &((KSet*)list_data(mem))->set, members)) {
                return -1;
            }
            if (set_size(&intersec) > max_size) {
                max_mem = mem;
                max_size = set_size(&intersec);
            }
            set_destroy(&intersec);
        }
        // A covering is not possible if there was no intersection.
        if (!max_size) {
            return 1;
        }
        // Insert the selected subset into the covering.
        subset = (KSet*)list_data(max_mem);

        if (set_insert(covering, subset)) {
            return -1;
        }
        // Remove each covered member from the set of noncovered members.
        mem = list_head(&((KSet*)list_data(max_mem))->set);
        for (; mem; mem = list_next(mem)) {
            data = list_data(mem);
            if (!set_remove(members, (void**)data) && members->_destroy) {
                members->_destroy(data);
            }
        }
        // Remove the subset from the set of candidate subsets.
        if (set_remove(subsets, (void**)&subset)) {
            return -1;
        }
    }
    // No covering is possible if there are still noncovered members.
    if (set_size(members) > 0) {
        return -1;
    }
    return 0;
}