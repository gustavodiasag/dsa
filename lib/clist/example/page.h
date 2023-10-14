#ifndef PAGE_H
#define PAGE_H

#include "clist.h"

/** Page information. */
typedef struct _Page {
    int     _number;
    int     _ref;
} Page;

/**
 * Finds the page to be replace given an element of a circular list containing
 * the page at which to begin searching.
 * 
 * Returns the number of the page to be replaced.
 */
int replace_page(CListElt** current);

#endif