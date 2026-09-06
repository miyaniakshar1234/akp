/**
 * ============================================================================
 *  AKP ENGINE - DIJKSTRA SHORTEST PATH VISUALIZER (akp/dijkstra.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Visual in-terminal single-source shortest path execution and path tables
 * ============================================================================
 */

#ifndef AKP_DIJKSTRA_H
#define AKP_DIJKSTRA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "color.h"
#include "badge.h"

#define AKP_INF 999999

typedef struct {
    int dist[AKP_GRAPH_MAX_VERTICES];
    int parent[AKP_GRAPH_MAX_VERTICES];
    int visited[AKP_GRAPH_MAX_VERTICES];
    int vertices;
    int source;
} akp_dijkstra_t;

static inline akp_dijkstra_t akp_dijkstra_solve(const akp_graph_t* g, int source) {
    akp_dijkstra_t res;
    res.vertices = g ? g->vertices : 0;
    res.source = source;

    if (!g || source < 0 || source >= g->vertices) return res;

    for (int i = 0; i < g->vertices; i++) {
        res.dist[i] = AKP_INF;
        res.visited[i] = 0;
        res.parent[i] = -1;
    }
    res.dist[source] = 0;

    for (int count = 0; count < g->vertices - 1; count++) {
        int min_dist = AKP_INF;
        int u = -1;

        for (int v = 0; v < g->vertices; v++) {
            if (!res.visited[v] && res.dist[v] <= min_dist) {
                min_dist = res.dist[v];
                u = v;
            }
        }

        if (u == -1 || min_dist == AKP_INF) break;
        res.visited[u] = 1;

        for (int v = 0; v < g->vertices; v++) {
            if (!res.visited[v] && g->adj[u][v] > 0 && res.dist[u] != AKP_INF
                && res.dist[u] + g->adj[u][v] < res.dist[v]) {
                res.dist[v] = res.dist[u] + g->adj[u][v];
                res.parent[v] = u;
            }
        }
    }

    return res;
}

static inline void akp_dijkstra_print_path(const akp_dijkstra_t* res, int j) {
    if (res->parent[j] == -1) {
        printf("V%d", j);
        return;
    }
    akp_dijkstra_print_path(res, res->parent[j]);
    printf(" -> V%d", j);
}

static inline void akp_dijkstra_render(const akp_dijkstra_t* res) {
    if (!res) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_GREEN "╔═════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_GREEN "║ 🛣️  DIJKSTRA SHORTEST PATH ANALYSIS (Source: V%-2d)                      ║\n" AKP_RESET, res->source);
    printf(AKP_BOLD AKP_NEON_GREEN "╠═════════════════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║ Destination │ Shortest Cost │ Full Route Sequence                     ║\n");
    printf(AKP_BOLD AKP_NEON_GREEN "╠═════════════╪═══════════════╪═════════════════════════════════════════╣\n" AKP_RESET);

    for (int i = 0; i < res->vertices; i++) {
        if (res->dist[i] == AKP_INF) {
            printf("║ V%-10d │ " AKP_DIM "UNREACHABLE " AKP_RESET "│ (No directed path)                    ║\n", i);
        } else {
            printf("║ V%-10d │ " AKP_BOLD AKP_NEON_GOLD "%13d" AKP_RESET " │ ", i, res->dist[i]);
            akp_dijkstra_print_path(res, i);
            printf("\n");
        }
    }
    printf(AKP_BOLD AKP_NEON_GREEN "╚═════════════╧═══════════════╧═════════════════════════════════════════╝\n\n" AKP_RESET);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_DIJKSTRA_H */
