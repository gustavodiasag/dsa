#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#include "list/list.h"
#include "set/set.h"

/** Structure representing an adjacency list. */
typedef struct _AdjList {
    void*   _vertex;
    Set     _adj;
} AdjList;

/** Graph data structure. */
typedef struct _Graph {
    List    _adjlists;
    size_t  _v;
    size_t  _e;

    int     (*_match)(const void* key1, const void* key2);
    void    (*_destroy)(void* data);
} Graph;

/** 
 * Evaluates the list of adjacency-list structures of a graph specified by
 * `graph`.
 */
#define graph_adjlists(graph) ((graph)->_adjlists)

/** Evaluates the number of vertices in a graph specified by `graph`. */
#define graph_v(graph) ((graph)->_v)

/** Evaluates the number or edges in a graph specified by `graph`. */
#define graph_e(graph) ((graph)->_e)

/**
 * Initializes a graph specified by `graph`. This operation must be called for
 * a graph in order for it to be used in any context.
 * 
 * The `compare` parameter is a function used by graph operations to compare
 * if to vertices match. This function should return 1 if `key1 > key2`, 0 if
 * `key1 == key2` or -1 if `key1 < key2`.
 * 
 * The `destroy` parameter must provide a way to free dynamic allocations in
 * the case where the graph's vertices store heap-allocated data. If the graph
 * elements do not contain data that must be freed, `destroy` must be set to
 * NULL.
 */
void graph_init(Graph* graph,
                int(*match)(const void*, const void*),
                void(*destroy)(void*));

/**
 * Destroys a graph specified by `graph`. No operation is allowed to happen in
 * the graph after a call to it.
 */
void graph_destroy(Graph* graph);

/**
 * Inserts a vertex that contains a pointer to `data` into a graph specified by
 * `graph`.
 * 
 * Returns 0 is inserting the vertex is successfull, 1 if the vertex already
 * exists or -1 otherwise.
 */
int graph_ins_v(Graph* graph, const void* data);

/**
 * Inserts an edge from a vertex specified by `data1` to a vertex specified by
 * `data2` into a graph specified by `graph`. Both vertices must have been
 * inserted previously using `graph_ins_v`.
 * 
 * Returns 0 if inserting the edge is successfull, 1 if the edge already exists
 * or -1 otherwise.
 */
int graph_ins_e(Graph* graph, const void* data1, const void* data2);

/**
 * Removes a vertex matching `data` from a graph specified by `graph`. Once
 * finished, `data` points to the data stored in the vertex that was removed.
 * 
 * Returns 0 if removing the vertex is successfull, or -1 otherwise.
 */
int graph_rm_v(Graph* graph, void** data);

/**
 * Removes an edge from `data1` to `data2` from a graph specified by `graph`.
 * Once finished, `data2` points to the data stored in the adjacency list of
 * the vertex specified by `data1`.
 * 
 * Returns 0 if removing the edge is successfull, or -1 otherwise.
 */
int graph_rm_e(Graph* graph, void** data1, void** data2);

/**
 * Retrieves all the vertices that are adjacent to the vertex specified by
 * `data` in a graph specified by `graph`. The adjacent vertices are returned
 * in an adjacent list specified by `adjlist`.
 * 
 * Returns 0 if retrieving the adjacent list is successfull, or -1 otherwise.
 */
int graph_adjlist(const Graph* graph, const void* data, AdjList** adj);

/**
 * Determines whether a vertex specified by `data2` is adjacent to a vertex
 * specified by `data1` in a graph specified by `graph`.
 * 
 * Returns 1 if the second vertex is adjacent to the first, or 0 otherwise.
 */
int graph_is_adj(const Graph* graph, const void* data1, const void* data2);

#endif