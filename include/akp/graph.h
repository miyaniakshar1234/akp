/**
 * ============================================================================
 *  AKP ENGINE - GRAPH TOPOLOGY & ADJACENCY MATRIX (akp/graph.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Visual in-terminal Graph representations, Adjacency Matrix & Traversals
 * ============================================================================
 */

#ifndef AKP_GRAPH_H
#define AKP_GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "color.h"
#include "badge.h"

#define AKP_GRAPH_MAX_VERTICES 32

typedef struct {
    int vertices;
    int is_directed;
    int adj[AKP_GRAPH_MAX_VERTICES][AKP_GRAPH_MAX_VERTICES];
} akp_graph_t;

static inline akp_graph_t* akp_graph_create(int vertices, int is_directed) {
    akp_init_console();
    if (vertices > AKP_GRAPH_MAX_VERTICES) vertices = AKP_GRAPH_MAX_VERTICES;
    if (vertices <= 0) vertices = 4;

    akp_graph_t* g = (akp_graph_t*)malloc(sizeof(akp_graph_t));
    if (!g) return NULL;
    g->vertices = vertices;
    g->is_directed = is_directed;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adj[i][j] = 0;
        }
    }
    return g;
}

static inline void akp_graph_free(akp_graph_t* g) {
    if (g) free(g);
}

static inline void akp_graph_add_edge(akp_graph_t* g, int u, int v, int weight) {
    if (!g || u < 0 || u >= g->vertices || v < 0 || v >= g->vertices) return;
    if (weight == 0) weight = 1;
    g->adj[u][v] = weight;
    if (!g->is_directed) {
        g->adj[v][u] = weight;
    }
}

static inline void akp_graph_render_adj_matrix(const akp_graph_t* g, const char* title) {
    if (!g) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║ 🌐 GRAPH ADJACENCY MATRIX: %-26s ║\n" AKP_RESET, title ? title : "Network Graph");
    printf(AKP_BOLD AKP_NEON_CYAN "╠═══════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║ Type: %s | Vertices: %2d                   ║\n",
           g->is_directed ? "Directed  " : "Undirected", g->vertices);
    printf(AKP_BOLD AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════╝\n" AKP_RESET);

    printf("     ");
    for (int j = 0; j < g->vertices; j++) {
        printf(AKP_BOLD AKP_NEON_GOLD " V%d  " AKP_RESET, j);
    }
    printf("\n");

    for (int i = 0; i < g->vertices; i++) {
        printf(AKP_BOLD AKP_NEON_GOLD " V%d " AKP_RESET AKP_BOLD "│" AKP_RESET, i);
        for (int j = 0; j < g->vertices; j++) {
            if (g->adj[i][j] > 0) {
                printf(AKP_BOLD AKP_NEON_GREEN " %2d  " AKP_RESET, g->adj[i][j]);
            } else {
                printf(AKP_DIM "  .  " AKP_RESET);
            }
        }
        printf(AKP_BOLD "│\n" AKP_RESET);
    }
    printf("\n");
}

static inline void akp_graph_render_adj_list(const akp_graph_t* g, const char* title) {
    if (!g) return;
    akp_init_console();

    printf(AKP_BOLD AKP_NEON_PINK "📌 Graph Adjacency List: %s\n" AKP_RESET, title ? title : "Graph");
    for (int i = 0; i < g->vertices; i++) {
        printf(AKP_BOLD AKP_NEON_CYAN "  [Vertex %d] " AKP_RESET, i);
        int edges = 0;
        for (int j = 0; j < g->vertices; j++) {
            if (g->adj[i][j] > 0) {
                printf("-> " AKP_BOLD AKP_NEON_GREEN "(%d [w:%d]) " AKP_RESET, j, g->adj[i][j]);
                edges++;
            }
        }
        if (edges == 0) printf(AKP_DIM "-> (No outgoing edges)" AKP_RESET);
        printf("\n");
    }
    printf("\n");
}

/* Breadth-First Search (BFS) */
static inline void akp_graph_bfs(const akp_graph_t* g, int start_vertex) {
    if (!g || start_vertex < 0 || start_vertex >= g->vertices) return;
    akp_init_console();

    int visited[AKP_GRAPH_MAX_VERTICES] = {0};
    int queue[AKP_GRAPH_MAX_VERTICES];
    int front = 0, rear = 0;

    printf(AKP_BOLD AKP_NEON_GREEN "🌊 BREADTH-FIRST SEARCH (BFS) STARTING AT V%d:\n" AKP_RESET, start_vertex);
    printf("   Traversal Order: ");

    visited[start_vertex] = 1;
    queue[rear++] = start_vertex;

    int first = 1;
    while (front < rear) {
        int u = queue[front++];
        if (!first) printf(" -> ");
        printf(AKP_BOLD AKP_NEON_GOLD "[V%d]" AKP_RESET, u);
        first = 0;

        for (int v = 0; v < g->vertices; v++) {
            if (g->adj[u][v] > 0 && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }
    printf("\n\n");
}

/* Depth-First Search (DFS) Internal */
static inline void akp_graph_dfs_util(const akp_graph_t* g, int u, int* visited, int* first) {
    visited[u] = 1;
    if (!(*first)) printf(" -> ");
    printf(AKP_BOLD AKP_NEON_PINK "[V%d]" AKP_RESET, u);
    *first = 0;

    for (int v = 0; v < g->vertices; v++) {
        if (g->adj[u][v] > 0 && !visited[v]) {
            akp_graph_dfs_util(g, v, visited, first);
        }
    }
}

/* Depth-First Search (DFS) */
static inline void akp_graph_dfs(const akp_graph_t* g, int start_vertex) {
    if (!g || start_vertex < 0 || start_vertex >= g->vertices) return;
    akp_init_console();

    int visited[AKP_GRAPH_MAX_VERTICES] = {0};
    int first = 1;

    printf(AKP_BOLD AKP_NEON_PINK "🌲 DEPTH-FIRST SEARCH (DFS) STARTING AT V%d:\n" AKP_RESET, start_vertex);
    printf("   Traversal Order: ");
    akp_graph_dfs_util(g, start_vertex, visited, &first);
    printf("\n\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_GRAPH_H */
