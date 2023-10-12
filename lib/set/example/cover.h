#ifndef COVER_H
#define COVER_H

#include "set.h"

/**
 * Determines a nearly optimal covering of the set specified by `members`,
 * given an amount of subsets specified by `subsets`, storing the result in
 * `covering`.
 * 
 * Returns 0 if a covering is found, 1 if a covering is not possible, or -1
 * otherwise.
 */
int cover(Set* members, Set* subsets, Set* covering);

#endif