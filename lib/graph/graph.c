#include <string.h>

#include "graph.h"

void graph_init(Graph* graph,
                int(*match)(const void*, const void*),
                void(*destroy)(void*))
{
    graph->_v = 0;
    graph->_e = 0;
    graph->_match = match;
    graph->_destroy = destroy;
    // Initialize adjacency list.
    list_init(&graph->_adjlists, NULL);
}

void graph_destroy(Graph* graph)
{
    AdjList* adj;
    // Remove each adjacency list.
    while (list_size(&graph->_adjlists) > 0) {
        if (!list_rm_next(&graph->_adjlists, NULL, (void**)&adj)) {
            set_destroy(&adj->_adj);

            if (graph->_destroy) {
                graph->_destroy(adj->_vertex);
            }
            free(adj);
        }
    }
    // Free adjacent list.
    list_destroy(&graph->_adjlists);
    // Clear structure;
    memset(graph, 0, sizeof(Graph));
}

int graph_ins_v(Graph* graph, const void* data)
{
    ListElt* elt;
    // Insertion of duplicate vertices is not allowed.
    for (elt = list_head(&graph->_adjlists); elt; elt = list_next(elt)) {
        if (!(graph->_match(data, ((AdjList*)list_data(elt))->_vertex))) {
            return 1;
        }
    }
    // Insert vertex.
    AdjList* adj;

    if (!(adj = (AdjList*)malloc(sizeof(AdjList)))) {
        return -1;
    }
    adj->_vertex = (void*)data;
    set_init(&adj->_adj, graph->_match, NULL);

    int retval;

    if ((retval = list_ins_next(&graph->_adjlists,
                                list_tail(&graph->_adjlists),
                                adj))) {
        return retval;
    }
    // Adjust vertex count.
    graph->_v++;

    return 0;
}

int graph_ins_e(Graph* graph, const void* data1, const void* data2)
{
    ListElt* elt;
    // Insertion is not allowed without both vertices in the graph.
    for (elt = list_head(&graph->_adjlists); elt; elt = list_next(elt)) {
        if (!(graph->_match(data2, ((AdjList*)list_data(elt))->_vertex))) {
            break;
        }
    }
    if (!elt) {
        return -1;
    }
    for (elt = list_head(&graph->_adjlists); elt; elt = list_next(elt)) {
        if (!(graph->_match(data1, ((AdjList*)list_data(elt))->_vertex))) {
            break;
        }
    }
    if (!elt) {
        return -1;
    }
    // Insert second vertex into the adjacency list of the first one.
    int retval;
    if (retval = set_insert(&((AdjList*)list_data(elt))->_adj, data2)) {
        return retval;
    }
    // Adjust edge count.
    graph->_e++;

    return 0;
}

int graph_rm_v(Graph* graph, void** data)
{
    ListElt* elt;
    ListElt* prev;
    ListElt* tmp;
    int found;
    // Traverse each adjacent list.
    prev = NULL;
    found = 0;

    for (elt = list_head(&graph->_adjlists); elt; elt = list_next(elt)) {
        // Deletion is not allowed if the vertex is in an adjacency list.
        if (set_is_member(&((AdjList*)list_data(elt))->_adj, *data)) {
            return -1;
        }
        // Keep a pointer to the vertex to be removed.
        if (graph->_match(*data, ((AdjList*)list_data(elt))->_vertex)) {
            tmp = elt;
            found = 1;
        }
        // Keep a pointer to the vertex before the one to be removed.
        if (!found) {
            prev = elt;
        }
    }
    // Return if the vertex was not found.
    if (!found) {
        return -1;
    }
    // Deletion is not allowed if the vertex's adjacency list is not empty.
    if (set_size(&((AdjList*)list_data(tmp))->_adj)) {
        return -1;
    }
    // Remove the vertex.
    AdjList* adj;
    if (list_rm_next(&graph->_adjlists, prev, (void**)&adj)) {
        return -1;
    }
    // Free the memory allocated for the abstract datatype.
    *data = adj->_vertex;
    free(adj);
    // Adjust vertex count.
    graph->_v--;

    return 0;
}

int graph_rm_edge(Graph* graph, const void* data1, const void* data2)
{
    ListElt* elt;
    // Locate the adjacency list for the first vertex;
    for (elt = list_head(&graph->_adjlists); elt; elt = list_next(elt)) {
        if (!(graph->_match(data1, ((AdjList*)list_data(elt))->_vertex))) {
            break;
        }
    }
    if (!elt) {
        return -1;
    }
    // Remove the second vertex from the adjacency list of the first one.
    if (set_remove(&((AdjList*)list_data(elt))->_adj, data2)) {
        return -1;
    }
    // Adjust edge count.
    graph->_e--;

    return 0;
}

int graph_adjlist(const Graph* graph, const void* data, AdjList** adj)
{
    ListElt* elt;
    ListElt* prev;
    // Locate the adjacency list for the vertex.
    prev = NULL;

    for (elt = list_head(&graph->_adjlists); elt ; elt = list_next(elt)) {
        if (!graph->_match(data, ((AdjList*)list_data(elt))->_vertex)) {
            break;
        }
        prev = elt;
    }
    // Return if the vertex was not found.
    if (!elt) {
        return -1;
    }
    // Pass the vertex's adjacency list.
    *adj = list_data(elt);

    return 0;
}

int graph_is_adj(const Graph* graph, const void* data1, const void* data2)
{
    ListElt* elt;
    ListElt* prev;
    // Locate the adjacency list for the vertex.
    prev = NULL;

    for (elt = list_head(&graph->_adjlists); elt; elt = list_next(elt)) {
        if (!graph->_match(data1, ((AdjList*)list_data(elt))->_vertex)) {
            break;
        }
        prev = elt;
    }
    // Return if the vertex was not found.
    if (!elt) {
        return -1;
    }
    // Return whether the second vertex is in the adjacency list of the first.
    return set_is_member(&((AdjList*)list_data(elt))->_adj, data2);
}