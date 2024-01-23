#include "set.h"

#include <string.h>

void set_init(Set* s, int (*match)(const void*, const void*),
              void (*destroy)(void*))
{
    list_init(s, destroy);
    s->_match = match;
}

int set_insert(Set* s, const void* data)
{
    /* Duplicates are not allowed. */
    if (set_is_member(s, data)) {
        return -1;
    }
    return list_ins_next(s, list_tail(s), data);
}

int set_remove(Set* s, void** data)
{
    ListElt* member;
    ListElt* prev;
    prev = NULL;

    for (member = list_head(s); member; member = list_next(member)) {
        if (s->_match(*data, list_data(member))) {
            break;
        }
        prev = member;
    }
    /* Return if the member wasn't found. */
    if (!member) {
        return -1;
    }
    return list_rm_next(s, prev, data);
}

int set_union(Set* set_u, const Set* s1, const Set* s2)
{
    ListElt* member;
    void* data;
    /* Initialize the set for the union. */
    set_init(set_u, s1->_match, NULL);
    /* Insert the elements of the first set. */
    for (member = list_head(s1); member; member = list_next(member)) {
        data = list_data(member);

        if (list_ins_next(set_u, list_tail(set_u), data)) {
            set_destroy(set_u);
            return -1;
        }
    }
    /* Insert the elements of the second set. */
    for (member = list_head(s2); member; member = list_next(member)) {
        if (set_is_member(s1, list_data(member))) {
            /* Duplicates are not allowed. */
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

int set_intersec(Set* set_i, const Set* s1, const Set* s2)
{
    ListElt* member;
    void* data;
    /* Initialize the set for the intersection. */
    set_init(set_i, s1->_match, NULL);
    /* Insert the members present in both sets. */
    for (member = list_head(s1); member; member = list_next(member)) {
        if (set_is_member(s2, list_data(member))) {
            data = list_data(member);

            if (list_ins_next(set_i, list_tail(set_i), data)) {
                set_destroy(set_i);
                return -1;
            }
        }
    }
    return 0;
}

int set_diff(Set* set_d, const Set* s1, const Set* s2)
{
    ListElt* member;
    void* data;
    /* Initialize the set for the difference. */
    set_init(set_d, s1->_match, NULL);
    /* Insert the members from `s1` not in `s2` */
    for (member = list_head(s1); member; member = list_next(member)) {
        if (!set_is_member(s2, list_data(member))) {
            data = list_data(member);

            if (list_inst_next(set_d, list_tail(set_d), data)) {
                set_destroy(set_d);
                return -1;
            }
        }
    }
    return 0;
}

int set_is_member(const Set* s, const void* data)
{
    ListElt* member;

    for (member = list_head(s); member; member = list_next(member)) {
        if (s->_match(data, list_data(member))) {
            return 1;
        }
    }
    return 0;
}

int set_is_subset(const Set* s1, const Set* s2)
{
    ListElt* member;

    if (set_size(s1) > set_size(s2)) {
        return 0;
    }
    for (member = list_head(s1); member; member = list_next(member)) {
        if (!set_is_member(s2, list_data(member))) {
            return 0;
        }
    }
    return 1;
}

int set_is_equal(const Set* s1, const Set* s2)
{
    if (set_size(s1) != set_size(s2)) {
        return 0;
    }
    /* Sets of the same size are equal if they are subsets. */
    return set_is_subset(s1, s2);
}