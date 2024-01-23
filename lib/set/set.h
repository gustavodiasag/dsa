#ifndef SET_H
#define SET_H

#include "list/list.h"

/** Set data structure implemented as linked-list. */
typedef List Set;

/** Evaluates the element count of a set specified by `s`. */
#define set_size list_size

/**
 * Destroys a set.
 * 
 * Since sets are linked-lists, `set_destroy` is defined as `list_destroy`.
 */
#define set_destroy list_destroy

/**
 * Initializes a set specified by `s`.
 * 
 * The `match` function pointer specifies a comparison function for set
 * elements and `destroy` specifies a way to free allocations when the set
 * stores heap-allocated data. Otherwise, `destroy` must be set to NULL.
 */
void set_init(Set* s, int (*match)(const void*, const void*),
              void (*destroy)(void*));

/**
 * Inserts an element containing `data` into a set specified by `s`.
 *
 * Returns 0 if inserting the member is successfull, or -1 otherwise.
 */
int set_insert(Set* s, const void* data);

/**
 * Removes the element matching `data` from a set specified by `s`. Once
 * finished, `data` points to the data stored in the member that was removed.
 *
 * Returns 0 if removing the member is successfull, or -1 otherwise.
 */
int set_remove(Set* s, void** data);

/**
 * Builds the union of `s1` and `s2`. Once finished, `set_u` contains the
 * union.
 *
 * Returns 0 if computing the union is successfull, or -1 otherwise.
 */
int set_union(Set* set_u, const Set* s1, const Set* s2);

/**
 * Builds the intersection of `s1` and `s2`. Once finished, `set_i` contains
 * the intersection.
 *
 * Returns 0 if computing the intersection is successfull, or -1 otherwise.
 */
int set_intersec(Set* set_i, const Set* s1, const Set* s2);

/**
 * Builds the difference of `s1` and `s2`. Once finished, `set_d` contains the
 * difference.
 *
 * Returns 0 if computing the difference is successfull, or -1 otherwise.
 */
int set_diff(Set* set_d, const Set* s1, const Set* s2);

/**
 * Determines whether the data specified by `data` matches a member in a set
 * specified by `s`.
 *
 * Returns 1 if the member is found, or 0 otherwise.
 */
int set_is_member(const Set* s, const void* data);

/**
 * Determines whether the set specified by `s1` is a subset of `s2`.
 *
 * Returns 1 if the set is a subset, or 0 otherwise.
 */
int set_is_subset(const Set* s1, const Set* s2);

/**
 * Determines whether the set specified by `s1` is equal to `s2`.
 *
 * Returns 1 if the set is equal, or 0 otherwise.
 */
int set_is_equal(const Set* s1, const Set* s2);

#endif