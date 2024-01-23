#ifndef COVER_H
#define COVER_H

#include "set.h"

/**
 * Determines a nearly optimal covering of a set specified by `s`, given an
 * amount of subsets specified by `subsets`, storing the result in `covering`.
 *
 * Returns 0 if a covering is found, 1 if a covering is not possible, or -1
 * otherwise.
 */
int cover(Set* s, Set* subsets, Set* covering);

#endif