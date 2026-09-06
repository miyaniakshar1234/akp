/**
 * ============================================================================
 *  AKP ENGINE - FLOYD-WARSHALL ALL-PAIRS SHORTEST PATH (akp/floyd_warshall.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Dynamic Programming All-Pairs Matrix & Path Reconstruction
 * ============================================================================
 */

#ifndef AKP_FLOYD_WARSHALL_H
#define AKP_FLOYD_WARSHALL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "badge.h"
#include "graph.h"

#define AKP_FLOYD_INF 999999

typedef struct {
    int vertices;
    int dist[AKP_GRAPH_MAX_VERTICES][AKP_GRAPH_MAX_VERTICES];
    int next[AKP_GRAPH_MAX_VERTICES][AKP_GRAPH_MAX_VERTICES];
    bool has_negative_cycle;
} akp_floyd_result_t;

/**
 * Executes Floyd-Warshall O(V^3) Dynamic Programming Algorithm
 */
static inline akp_floyd_result_t akp_floyd_solve(const akp_graph_t* g) {
    akp_floyd_result_t res;
    res.vertices = g ? g->vertices : 0;
    res.has_negative_cycle = false;

    if (!g || g->vertices <= 0) return res;

    int n = g->vertices;

    /* Initialize base distance and next hop routing matrices */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                res.dist[i][j] = 0;
                res.next[i][j] = j;
            } else if (g->adj[i][j] > 0) {
                res.dist[i][j] = g->adj[i][j];
                res.next[i][j] = j;
            } else {
                res.dist[i][j] = AKP_FLOYD_INF;
                res.next[i][j] = -1;
            }
        }
    }

    /* Dynamic programming relaxation over all intermediate vertices k */
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (res.dist[i][k] != AKP_FLOYD_INF && res.dist[k][j] != AKP_FLOYD_INF) {
                    if (res.dist[i][k] + res.dist[k][j] < res.dist[i][j]) {
                        res.dist[i][j] = res.dist[i][k] + res.dist[k][j];
                        res.next[i][j] = res.next[i][k];
                    }
                }
            }
        }
    }

    /* Negative cycle detection */
    for (int i = 0; i < n; i++) {
        if (res.dist[i][i] < 0) {
            res.has_negative_cycle = true;
            break;
        }
    }

    return res;
}

/**
 * Reconstructs the exact sequence of vertices from u to v
 * Returns path length (number of vertices), or 0 if unreachable
 */
static inline int akp_floyd_get_path(const akp_floyd_result_t* res, int u, int v, int* path_out) {
    if (!res || !path_out || u < 0 || u >= res->vertices || v < 0 || v >= res->vertices) {
        return 0;
    }
    if (res->dist[u][v] == AKP_FLOYD_INF) return 0;

    int count = 0;
    int curr = u;
    path_out[count++] = curr;

    while (curr != v) {
        curr = res->next[curr][v];
        if (curr == -1 || count >= AKP_GRAPH_MAX_VERTICES) return 0;
        path_out[count++] = curr;
    }
    return count;
}

/**
 * Renders the All-Pairs Shortest Distance Matrix
 */
static inline void akp_floyd_render(const akp_graph_t* g, const akp_floyd_result_t* res, const char* title) {
    if (!g || !res) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║  🌐 FLOYD-WARSHALL ALL-PAIRS SHORTEST PATH MATRIX: %-25s ║\n" AKP_RESET, title ? title : "Network Routing Grid");
    printf(AKP_BOLD AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    if (res->has_negative_cycle) {
        printf("  " AKP_BOLD AKP_NEON_RED "⛔ NEGATIVE CYCLE DETECTED: Path weights diverge to -infinity!\n\n" AKP_RESET);
        return;
    }

    printf("  Vertices: %d | Time: O(V^3) | Space: O(V^2)\n\n", res->vertices);

    /* Matrix Column Header */
    printf("        ");
    for (int j = 0; j < res->vertices; j++) {
        printf(AKP_BOLD AKP_NEON_GOLD "  V%-2d  " AKP_RESET, j);
    }
    printf("\n");

    for (int i = 0; i < res->vertices; i++) {
        printf(AKP_BOLD AKP_NEON_GOLD "  V%-2d  " AKP_RESET AKP_BOLD "│" AKP_RESET, i);
        for (int j = 0; j < res->vertices; j++) {
            if (i == j) {
                printf(AKP_DIM "    0  " AKP_RESET);
            } else if (res->dist[i][j] == AKP_FLOYD_INF) {
                printf(AKP_NEON_RED "   ∞   " AKP_RESET);
            } else {
                printf(AKP_BOLD AKP_NEON_GREEN "  %3d  " AKP_RESET, res->dist[i][j]);
            }
        }
        printf(AKP_BOLD "│\n" AKP_RESET);
    }
    printf("\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_FLOYD_WARSHALL_H */
