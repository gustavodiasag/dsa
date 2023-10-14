#ifndef PAGE_H
#define PAGE_H

#include "clist.h"

/** Page information. */
typedef struct _Page {
    int     _number;
    int     _ref;
} Page;

int replace_page(CListElt** current);

#endif