#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

/** Structure representing an adjacency list. */
typedef struct AdjList AdjList;

/** Graph data structure. */
typedef struct Graph Graph;

/**
 * Evaluates the list of adjacency-list structures of a graph specified by `g`.
 */
#define graph_adjlists(g) ((g)->_adjlists)

/** Evaluates the number of vertices in a graph specified by `g`. */
#define graph_v(g) ((g)->_v)

/** Evaluates the number or edges in a graph specified by `g`. */
#define graph_e(g) ((g)->_e)

/**
 * Initializes a graph specified by `g`. 
 *
 * The `match` function pointer specifies a comparison function for graph
 * elements and `destroy` specifies a way to free allocations when the graph
 * stores heap-allocated data. Otherwise, `destroy` must be set to NULL.
 */
void graph_init(Graph* g, int (*match)(const void*, const void*),
                void (*destroy)(void*));

/** Removes the elements and deallocates a graph specified by `g`. */
void graph_destroy(Graph* g);

/**
 * Inserts a vertex that contains a pointer to `data` into a graph specified by
 * `g`.
 *
 * Returns 0 is inserting the vertex is successfull, 1 if the vertex already
 * exists or -1 otherwise.
 */
int graph_ins_v(Graph* g, const void* data);

/**
 * Inserts an edge from a vertex specified by `v1` to a vertex specified by
 * `v2` into a graph specified by `g`. Both vertices must have been
 * inserted previously using `graph_ins_v`.
 *
 * Returns 0 if inserting the edge is successfull, 1 if the edge already exists
 * or -1 otherwise.
 */
int graph_ins_e(Graph* g, const void* v1, const void* v2);

/**
 * Removes a vertex matching `v` from a graph specified by `g`. Once
 * finished, `data` points to the data stored in the vertex that was removed.
 *
 * Returns 0 if removing the vertex is successfull, or -1 otherwise.
 */
int graph_rm_v(Graph* g, void** v);

/**
 * Removes an edge from `v1` to `v2` from a graph specified by `g`. Once
 * finished, `v2` points to the data stored in the adjacency list of the vertex
 * specified by `v1`.
 *
 * Returns 0 if removing the edge is successfull, or -1 otherwise.
 */
int graph_rm_e(Graph* g, void** v1, void** v2);

/**
 * Retrieves all the vertices that are adjacent to the vertex specified by
 * `data` in a graph specified by `g`. The adjacent vertices are returned
 * in an adjacent list specified by `adj`.
 *
 * Returns 0 if retrieving the adjacent list is successfull, or -1 otherwise.
 */
int graph_adjlist(const Graph* g, const void* data, AdjList** adj);

/**
 * Determines whether a vertex specified by `v2` is adjacent to a vertex
 * specified by `v1` in a graph specified by `g`.
 *
 * Returns 1 if the second vertex is adjacent to the first, or 0 otherwise.
 */
int graph_is_adj(const Graph* g, const void* v1, const void* v2);

#endif