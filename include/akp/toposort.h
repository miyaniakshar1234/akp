/**
 * ============================================================================
 *  AKP ENGINE - TOPOLOGICAL SORT & DAG CYCLE DETECTOR (akp/toposort.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Kahn's BFS Algorithm & Task Dependency Pipeline Visualizer
 * ============================================================================
 */

#ifndef AKP_TOPOSORT_H
#define AKP_TOPOSORT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "badge.h"
#include "graph.h"

typedef struct {
    int order[AKP_GRAPH_MAX_VERTICES];
    int count;
    bool has_cycle;
    int indegree[AKP_GRAPH_MAX_VERTICES];
} akp_toposort_result_t;

/**
 * Executes Kahn's In-Degree BFS Algorithm on Directed Graph
 */
static inline akp_toposort_result_t akp_toposort_solve(const akp_graph_t* g) {
    akp_toposort_result_t res;
    res.count = 0;
    res.has_cycle = false;

    if (!g || g->vertices <= 0) {
        return res;
    }

    int n = g->vertices;
    for (int i = 0; i < n; i++) {
        res.indegree[i] = 0;
        res.order[i] = -1;
    }

    /* Compute initial in-degrees */
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (g->adj[u][v] > 0) {
                res.indegree[v]++;
            }
        }
    }

    /* Queue for zero-indegree vertices */
    int queue[AKP_GRAPH_MAX_VERTICES];
    int front = 0, rear = 0;

    int temp_indegree[AKP_GRAPH_MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        temp_indegree[i] = res.indegree[i];
        if (temp_indegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        res.order[res.count++] = u;

        for (int v = 0; v < n; v++) {
            if (g->adj[u][v] > 0) {
                temp_indegree[v]--;
                if (temp_indegree[v] == 0) {
                    queue[rear++] = v;
                }
            }
        }
    }

    if (res.count < n) {
        res.has_cycle = true;
    }

    return res;
}

/**
 * Terminal Visualizer for Topological Sort & Dependency Resolution
 */
static inline void akp_toposort_render(const akp_graph_t* g, const akp_toposort_result_t* res, const char* title) {
    if (!g || !res) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║  🔄 TOPOLOGICAL SORT & DEPENDENCY PIPELINE: %-33s ║\n" AKP_RESET, title ? title : "Task Dependency DAG");
    printf(AKP_BOLD AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    if (res->has_cycle) {
        printf("  " AKP_BOLD AKP_NEON_RED "⛔ DEADLOCK DETECTED: Graph contains directed cyclic dependencies!\n" AKP_RESET);
        printf("  Resolved Vertices: %d / %d (Cycle Trapped: %d)\n", res->count, g->vertices, g->vertices - res->count);
        printf("  " AKP_DIM "↳ Topological ordering impossible due to circular dependency loops.\n\n" AKP_RESET);
        return;
    }

    printf("  " AKP_BOLD AKP_NEON_GREEN "✔ VALID DIRECTED ACYCLIC GRAPH (DAG) RESOLVED\n" AKP_RESET);
    printf("  Vertices Ordered: %d / %d  |  Algorithm: Kahn's In-Degree BFS (Time: O(V + E))\n\n", res->count, g->vertices);

    printf(AKP_BOLD AKP_NEON_GOLD "  Sequential Execution Pipeline:\n    " AKP_RESET);
    for (int i = 0; i < res->count; i++) {
        printf(AKP_BOLD AKP_NEON_CYAN "[Step %02d: V%d]" AKP_RESET, i + 1, res->order[i]);
        if (i < res->count - 1) {
            printf(AKP_NEON_GREEN " ───> " AKP_RESET);
        }
    }
    printf("\n\n");

    /* In-degree audit table */
    printf("  ┌───────────────┬─────────────────┬───────────────────────┐\n");
    printf("  │  Step Order   │  Vertex Index   │  Original In-Degree   │\n");
    printf("  ├───────────────┼─────────────────┼───────────────────────┤\n");
    for (int i = 0; i < res->count; i++) {
        int v = res->order[i];
        printf("  │    Step %2d    │     Node %2d     │         %3d           │\n",
               i + 1, v, res->indegree[v]);
    }
    printf("  └───────────────┴─────────────────┴───────────────────────┘\n\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_TOPOSORT_H */
