#ifndef SET_H
#define SET_H

#include "list/list.h"

/** Set data structure implemented as linked-list. */
typedef List Set;

/** Evaluates the number of elements in a set specified by `set`. */
#define set_size list_size

/**
 * Destroys a set. Since a set is a linked-list and requires being destroyed
 * in the same way, `set_destroy` is defined to `list_destroy`.
 */
#define set_destroy list_destroy

/**
 * Initializes the set specified by `set`. The `match` parameter is a function
 * used by various set operations to determine if two members match. It must
 * return 1 if `key1` is equal to `key2` or 0 otherwise. 
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the set stores heap-allocated data. If the set elements do
 * not contain data that must be freed, `destroy` must be set to NULL.
 */
void set_init(Set* set,
              int(*match)(const void*, const void*),
              void(*destroy)(void*));

/**
 * Inserts a member into the set specified by `set`. The new member contains a
 * pointer to `data`, so the memory referenced by `data` must remain valid as
 * long as the element remains in the set.
 * 
 * Returns 0 if inserting the member is successfull, or -1 otherwise.
 */
int set_insert(Set* set, const void* data);

/**
 * Removes the member matching `data` from the set specified by `set`. Once
 * finished, `data` points to the data stored in the member that was removed.
 * 
 * Returns 0 if removing the member is successfull, or -1 otherwise.
*/
int set_remove(Set* set, void** data);

/**
 * Builds a set that is the union of `set1` and `set2`. Once finished, `set_u`
 * contains the union. Given that `set_u` points to data in `set1` and `set2`,
 * the memory referenced by them must remain valid until `set_u` is freed. 
 * 
 * Returns 0 if computing the union is successfull, or -1 otherwise.
 */
int set_union(Set* set_u, const Set* set1, const Set* set2);

/**
 * Builds a set that is the intersection of `set1` and `set2`. Once finished,
 * `set_i` contains the intersection. Given that `set_i` points to data in 
 * `set1` and `set2`, the memory referenced by them must remain valid until
 * `set_i` is freed.
 * 
 * Returns 0 if computing the intersection is successfull, or -1 otherwise. 
 */
int set_intersec(Set* set_i, const Set* set1, const Set* set2);

/**
 * Builds a set that is the difference of `set1` and `set2`. Once finished,
 * `set_d` contains the difference. Given that `set_d` points to data in 
 * `set1` and `set2`, the memory referenced by them must remain valid until
 * `set_d` is freed.
 * 
 * Returns 0 if computing the difference is successfull, or -1 otherwise. 
 */
int set_diff(Set* set_d, const Set* set1, const Set* set2);

/**
 * Determines whether the data specified by `data` matches that of a member in
 * the set specified by `set`.
 * 
 * Returns 1 if the member is found, or 0 otherwise. 
 */
int set_is_member(const Set* set, const void* data);

/**
 * Determines whether the set specified by `set1` is a subset of the set
 * specified by `set2`.
 * 
 * Returns 1 if the set is a subset, or 0 otherwise.
*/
int set_is_subset(const Set* set1, const Set* set2);

/**
 * Determines whether the set specified by `set1` is equal to the set specified
 * by `set2`.
 * 
 * Returns 1 if the set is equal, or 0 otherwise.
 */
int set_is_equal(const Set* set1, const Set* set2);

#endif