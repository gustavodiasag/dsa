#include "page.h"

int replace_page(CListElt** current)
{
    while (((Page*)(*current)->_data)->_ref) {
        ((Page*)(*current)->_data)->_ref = 0;
        *current = clist_next(*current);
    }
    return ((Page*)(*current)->_data)->_number;
}