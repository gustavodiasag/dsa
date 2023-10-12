#include <string.h>

#include "set.h"

void set_init(Set* set, int(*match)(const void*, const void*),
                        void(*destroy)(void* data))
{
    list_init(set, destroy);
    set->_match = match;
}

int set_insert(Set* set, const void* data)
{
    // Duplicates are not allowed.
    if (set_is_member(set, data)) {
        return -1;
    }
    return list_ins_next(set, list_tail(set), data);
}

int set_remove(Set*set, void** data)
{
    ListElt* member, *prev;
    prev = NULL;

    for (member = list_head(set); member; member = list_next(member)) {
        if (set->_match(*data, list_data(member))) {
            break;
        }
        prev = member;
    }
    // Return if the member wasn't found.
    if (!member) {
        return -1;
    }
    return list_rm_next(set, prev, data);
}

int set_union(Set* set_u, const Set* set1, const Set* set2)
{
    ListElt*    member;
    void*       data;
    // Initialize the set for the union.
    set_init(set_u, set1->_match, NULL);
    // Insert the elements of the first set.
    for (member = list_head(set1); member; member = list_next(member)) {
        data = list_data(member);

        if (list_ins_next(set_u, list_tail(set_u), data)) {
            set_destroy(set_u);
            return -1;
        }
    }
    // Insert the elements of the second set.
    for (member = list_head(set2); member; member = list_next(member)) {
        if (set_is_member(set1, list_data(member))) {
            // Duplicates are not allowed.
            continue;
        } else {
            data = list_data(member);
            
            if (list_ins_next(set_u, list_tail(set_u), data)) {
                set_destroy(set_u);
                return -1;
            }
        }
    }
    return 0;
}

int set_intersec(Set* set_i, const Set* set1, const Set* set2)
{
    ListElt*    member;
    void*       data;
    // Initialize the set for the intersection.
    set_init(set_i, set1->_match, NULL);
    // Insert the members present in both sets.
    for (member = list_head(set1); member; member = list_next(member)) {
        if (set_is_member(set2, list_data(member))) {
            data = list_data(member);

            if (list_ins_next(set_i, list_tail(set_i), data)) {
                set_destroy(set_i);
                return -1;
            }
        }
    }
    return 0;
}

int set_diff(Set* set_d, const Set* set1, const Set* set2)
{
    ListElt*    member;
    void*       data;
    // Initialize the set for the difference.
    set_init(set_d, set1->_match, NULL);
    // Insert the members from `set1` not in `set2`
    for (member = list_head(set1); member; member = list_next(member)) {
        if (!set_is_member(set2, list_data(member))) {
            data = list_data(member);

            if (list_inst_next(set_d, list_tail(set_d), data)) {
                set_destroy(set_d);
                return -1;
            }
        }
    }
    return 0;
}

int set_is_member(const Set* set, const void* data)
{
    ListElt* member;

    for (member = list_head(set); member; member = list_next(member)) {
        if (set->_match(data, list_data(member))) {
            return 1;
        }
    }
    return 0;
}

int set_is_subset(const Set* set1, const Set* set2)
{
    ListElt* member;

    if (set_size(set1) > set_size(set2)) {
        return 0;
    }

    for (member = list_head(set1); member; member = list_next(member)) {
        if (!set_is_member(set2, list_data(member))) {
            return 0;
        }
    }
    return 1;
}

int set_is_equal(const Set* set1, const Set* set2)
{
    if (set_size(set1) != set_size(set2)) {
        return 0;
    }
    // Sets of the same size are equal if they are subsets.
    return set_is_subset(set1, set2);
}