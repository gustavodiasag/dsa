#include "graph.h"
#include "list/list.h"
#include "set/set.h"

#include <string.h>

typedef struct {
    void*   _vertex;
    Set     _adj;
} AdjList;

typedef struct {
    List    _adjlists;
    size_t  _v;
    size_t  _e;

    int     (*_match)(const void*, const void*);
    void    (*_destroy)(void*);
} Graph;

void graph_init(Graph* g, int (*match)(const void*, const void*),
                void (*destroy)(void*))
{
    g->_v = 0;
    g->_e = 0;
    g->_match = match;
    g->_destroy = destroy;
    /* Initialize adjacency list. */
    list_init(&g->_adjlists, NULL);
}

void graph_destroy(Graph* g)
{
    AdjList* adj;
    /* Remove each adjacency list. */
    while (list_size(&g->_adjlists) > 0) {
        if (!list_rm_next(&g->_adjlists, NULL, (void**)&adj)) {
            set_destroy(&adj->_adj);

            if (g->_destroy) {
                g->_destroy(adj->_vertex);
            }
            free(adj);
        }
    }
    /* Free adjacent list. */
    list_destroy(&g->_adjlists);
    /* Clear structure. */
    memset(g, 0, sizeof(Graph));
}

int graph_ins_v(Graph* g, const void* data)
{
    ListElt* elt;
    /* Insertion of duplicate vertices is not allowed. */
    for (elt = list_head(&g->_adjlists); elt; elt = list_next(elt)) {
        if (!(g->_match(data, ((AdjList*)list_data(elt))->_vertex))) {
            return 1;
        }
    }
    /* Insert vertex. */
    AdjList* adj;

    if (!(adj = (AdjList*)malloc(sizeof(AdjList)))) {
        return -1;
    }
    adj->_vertex = (void*)data;
    set_init(&adj->_adj, g->_match, NULL);

    int retval;

    if ((retval = list_ins_next(&g->_adjlists, list_tail(&g->_adjlists),
                                adj))) {
        return retval;
    }
    /* Adjust vertex count. */
    g->_v++;

    return 0;
}

int graph_ins_e(Graph* g, const void* v1, const void* v2)
{
    ListElt* elt;
    /* Insertion is not allowed without both vertices in the graph. */
    for (elt = list_head(&g->_adjlists); elt; elt = list_next(elt)) {
        if (!(g->_match(v2, ((AdjList*)list_data(elt))->_vertex))) {
            break;
        }
    }
    if (!elt) {
        return -1;
    }
    for (elt = list_head(&g->_adjlists); elt; elt = list_next(elt)) {
        if (!(g->_match(v1, ((AdjList*)list_data(elt))->_vertex))) {
            break;
        }
    }
    if (!elt) {
        return -1;
    }
    /* Insert second vertex into the adjacency list of the first one. */
    int retval;
    if (retval = set_insert(&((AdjList*)list_data(elt))->_adj, v2)) {
        return retval;
    }
    /* Adjust edge count. */
    g->_e++;

    return 0;
}

int graph_rm_v(Graph* g, void** data)
{
    ListElt* elt;
    ListElt* prev;
    ListElt* tmp;
    int found;
    /* Traverse each adjacent list. */
    prev = NULL;
    found = 0;

    for (elt = list_head(&g->_adjlists); elt; elt = list_next(elt)) {
        /* Deletion is not allowed if the vertex is in an adjacency list. */
        if (set_is_member(&((AdjList*)list_data(elt))->_adj, *data)) {
            return -1;
        }
        /* Keep a pointer to the vertex to be removed. */
        if (g->_match(*data, ((AdjList*)list_data(elt))->_vertex)) {
            tmp = elt;
            found = 1;
        }
        /* Keep a pointer to the vertex before the one to be removed. */
        if (!found) {
            prev = elt;
        }
    }
    /* Return if the vertex was not found. */
    if (!found) {
        return -1;
    }
    /* Deletion is not allowed if the vertex's adjacency list is not empty. */
    if (set_size(&((AdjList*)list_data(tmp))->_adj)) {
        return -1;
    }
    /* Remove the vertex. */
    AdjList* adj;
    if (list_rm_next(&g->_adjlists, prev, (void**)&adj)) {
        return -1;
    }
    /* Free the memory allocated for the abstract datatype. */
    *data = adj->_vertex;
    free(adj);
    /* Adjust vertex count. */
    g->_v--;

    return 0;
}

int graph_rm_e(Graph* g, const void* v1, const void* v2)
{
    ListElt* elt;
    /* Locate the adjacency list for the first vertex. */
    for (elt = list_head(&g->_adjlists); elt; elt = list_next(elt)) {
        if (!(g->_match(v1, ((AdjList*)list_data(elt))->_vertex))) {
            break;
        }
    }
    if (!elt) {
        return -1;
    }
    /* Remove the second vertex from the adjacency list of the first one. */
    if (set_remove(&((AdjList*)list_data(elt))->_adj, v2)) {
        return -1;
    }
    /* Adjust edge count. */
    g->_e--;

    return 0;
}

int graph_adjlist(const Graph* g, const void* data, AdjList** adj)
{
    ListElt* elt;
    ListElt* prev;
    /* Locate the adjacency list for the vertex. */
    prev = NULL;

    for (elt = list_head(&g->_adjlists); elt; elt = list_next(elt)) {
        if (!g->_match(data, ((AdjList*)list_data(elt))->_vertex)) {
            break;
        }
        prev = elt;
    }
    /* Return if the vertex was not found. */
    if (!elt) {
        return -1;
    }
    /* Pass the vertex's adjacency list. */
    *adj = list_data(elt);

    return 0;
}

int graph_is_adj(const Graph* g, const void* data1, const void* data2)
{
    ListElt* elt;
    ListElt* prev;
    /* Locate the adjacency list for the vertex. */
    prev = NULL;

    for (elt = list_head(&g->_adjlists); elt; elt = list_next(elt)) {
        if (!g->_match(data1, ((AdjList*)list_data(elt))->_vertex)) {
            break;
        }
        prev = elt;
    }
    /* Return if the vertex was not found. */
    if (!elt) {
        return -1;
    }
    /* Whether the second vertex is in the adjacency list of the first. */
    return set_is_member(&((AdjList*)list_data(elt))->_adj, data2);
}