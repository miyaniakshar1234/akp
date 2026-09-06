/**
 * ============================================================================
 * AKP ENGINE - HIGH PERFORMANCE C/C++ FLASHY TOOLKIT
 * SUBSYSTEM: kruskal.h (Visual Kruskal's Minimum Spanning Tree Visualizer)
 * 
 * Engineered & Authored by: Akshar Miyani
 * AKP Studio Systems Architecture | Release v1.7.0
 * ============================================================================
 */

#ifndef AKP_KRUSKAL_H
#define AKP_KRUSKAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "badge.h"
#include "graph.h"
#include "disjoint_set.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int u;
    int v;
    int weight;
    bool accepted;
} akp_kruskal_edge_t;

typedef struct {
    akp_kruskal_edge_t mst_edges[128];
    int mst_edge_count;
    int total_mst_weight;
    int total_inspected;
    int cycles_rejected;
} akp_kruskal_result_t;

static inline int akp_kruskal_edge_cmp(const void* a, const void* b) {
    const akp_kruskal_edge_t* ea = (const akp_kruskal_edge_t*)a;
    const akp_kruskal_edge_t* eb = (const akp_kruskal_edge_t*)b;
    return ea->weight - eb->weight;
}

static inline bool akp_kruskal_solve(const akp_graph_t* g, akp_kruskal_result_t* out_res) {
    if (!g || !out_res) return false;
    memset(out_res, 0, sizeof(akp_kruskal_result_t));

    // 1. Extract all unique undirected edges
    akp_kruskal_edge_t all_edges[256];
    int edge_count = 0;

    for (int i = 0; i < g->vertices; i++) {
        for (int j = i + 1; j < g->vertices; j++) {
            if (g->adj[i][j] > 0) {
                if (edge_count < 256) {
                    all_edges[edge_count].u = i;
                    all_edges[edge_count].v = j;
                    all_edges[edge_count].weight = g->adj[i][j];
                    all_edges[edge_count].accepted = false;
                    edge_count++;
                }
            }
        }
    }

    if (edge_count == 0) return false;

    // 2. Sort edges in ascending order of weight
    qsort(all_edges, (size_t)edge_count, sizeof(akp_kruskal_edge_t), akp_kruskal_edge_cmp);

    // 3. Greedy MST Construction with Disjoint Set
    akp_dsu_t* dsu = akp_dsu_create(g->vertices);
    if (!dsu) return false;

    for (int i = 0; i < edge_count; i++) {
        out_res->total_inspected++;
        int u = all_edges[i].u;
        int v = all_edges[i].v;
        int w = all_edges[i].weight;

        if (akp_dsu_find(dsu, u) != akp_dsu_find(dsu, v)) {
            akp_dsu_union(dsu, u, v);
            all_edges[i].accepted = true;
            if (out_res->mst_edge_count < 128) {
                out_res->mst_edges[out_res->mst_edge_count++] = all_edges[i];
                out_res->total_mst_weight += w;
            }
        } else {
            out_res->cycles_rejected++;
        }
    }

    akp_dsu_destroy(dsu);
    return true;
}

static inline void akp_kruskal_render(const akp_graph_t* g, const akp_kruskal_result_t* res, const char* title) {
    akp_init_console();
    printf("\n");
    akp_set_fg_rgb(0, 255, 230);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  🌲 KRUSKAL'S MINIMUM SPANNING TREE (MST) VISUALIZER                          ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    akp_reset_color();

    if (title) {
        akp_set_fg_rgb(255, 215, 0);
        printf("  ⚡ Topology: %s\n", title);
        akp_reset_color();
    }

    if (!res || res->mst_edge_count == 0) {
        akp_set_fg_rgb(255, 70, 85);
        printf("  [ No MST available for this graph ]\n\n");
        akp_reset_color();
        return;
    }

    akp_set_fg_rgb(0, 255, 170);
    printf("  Graph Vertices: %d  |  MST Edges: %d  |  Total Minimal Weight: %d\n", 
           g ? g->vertices : 0, res->mst_edge_count, res->total_mst_weight);
    printf("  Edges Evaluated: %d  |  Cycles Avoided: %d\n\n", res->total_inspected, res->cycles_rejected);
    akp_reset_color();

    akp_set_fg_rgb(255, 0, 128);
    printf("  ┌───────────┬──────────────┬──────────────┬──────────────────┐\n");
    printf("  │  Edge #   │ Source Vertex│ Target Vertex│ Edge Cost Weight │\n");
    printf("  ├───────────┼──────────────┼──────────────┼──────────────────┤\n");
    akp_reset_color();

    for (int i = 0; i < res->mst_edge_count; i++) {
        akp_set_fg_rgb(255, 255, 255);
        printf("  │  MST-%02d   │    Node %2d   │    Node %2d   │      ", 
               i + 1, res->mst_edges[i].u, res->mst_edges[i].v);
        akp_set_fg_rgb(0, 255, 200);
        printf("%6d      ", res->mst_edges[i].weight);
        akp_reset_color();
        printf("│\n");
    }

    akp_set_fg_rgb(255, 0, 128);
    printf("  └───────────┴──────────────┴──────────────┴──────────────────┘\n\n");
    akp_reset_color();
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_KRUSKAL_H */
