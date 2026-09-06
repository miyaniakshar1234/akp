/**
 * ============================================================================
 * AKP ENGINE - HIGH PERFORMANCE C/C++ FLASHY TOOLKIT
 * SUBSYSTEM: disjoint_set.h (Visual Disjoint-Set Union-Find / DSU)
 * 
 * Engineered & Authored by: Akshar Miyani
 * AKP Studio Systems Architecture | Release v1.7.0
 * ============================================================================
 */

#ifndef AKP_DISJOINT_SET_H
#define AKP_DISJOINT_SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "badge.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int* parent;
    int* rank;
    int n;
    int num_sets;
} akp_dsu_t;

static inline akp_dsu_t* akp_dsu_create(int n) {
    if (n <= 0) n = 16;
    akp_dsu_t* dsu = (akp_dsu_t*)malloc(sizeof(akp_dsu_t));
    if (!dsu) return NULL;
    dsu->n = n;
    dsu->num_sets = n;
    dsu->parent = (int*)malloc((size_t)n * sizeof(int));
    dsu->rank = (int*)malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}

static inline void akp_dsu_destroy(akp_dsu_t* dsu) {
    if (!dsu) return;
    if (dsu->parent) free(dsu->parent);
    if (dsu->rank) free(dsu->rank);
    free(dsu);
}

static inline int akp_dsu_find(akp_dsu_t* dsu, int i) {
    if (!dsu || i < 0 || i >= dsu->n) return -1;
    if (dsu->parent[i] == i) return i;
    // Path compression
    return dsu->parent[i] = akp_dsu_find(dsu, dsu->parent[i]);
}

static inline bool akp_dsu_union(akp_dsu_t* dsu, int i, int j) {
    if (!dsu) return false;
    int root_i = akp_dsu_find(dsu, i);
    int root_j = akp_dsu_find(dsu, j);
    if (root_i == root_j) return false; // Already in the same set

    // Union by rank
    if (dsu->rank[root_i] < dsu->rank[root_j]) {
        dsu->parent[root_i] = root_j;
    } else if (dsu->rank[root_i] > dsu->rank[root_j]) {
        dsu->parent[root_j] = root_i;
    } else {
        dsu->parent[root_j] = root_i;
        dsu->rank[root_i]++;
    }
    dsu->num_sets--;
    return true;
}

static inline bool akp_dsu_connected(akp_dsu_t* dsu, int i, int j) {
    if (!dsu) return false;
    return akp_dsu_find(dsu, i) == akp_dsu_find(dsu, j);
}

static inline void akp_dsu_render(akp_dsu_t* dsu, const char* title) {
    akp_init_console();
    printf("\n");
    akp_set_fg_rgb(0, 255, 230);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  🌐 DISJOINT-SET UNION (DSU / UNION-FIND) PARTITION VISUALIZER                ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    akp_reset_color();

    if (title) {
        akp_set_fg_rgb(255, 215, 0);
        printf("  ⚡ State: %s\n", title);
        akp_reset_color();
    }

    if (!dsu) {
        akp_set_fg_rgb(255, 70, 85);
        printf("  [ DSU is NULL ]\n\n");
        akp_reset_color();
        return;
    }

    akp_set_fg_rgb(0, 255, 170);
    printf("  Total Elements: %d  |  Disjoint Components: %d\n\n", dsu->n, dsu->num_sets);
    akp_reset_color();

    // Node pointer table
    printf("  Direct Parent & Rank Pointers:\n  ");
    for (int i = 0; i < dsu->n; i++) {
        int root = akp_dsu_find(dsu, i);
        if (root == i) {
            akp_set_fg_rgb(255, 215, 0);
            printf("[%d: ROOT(R:%d)] ", i, dsu->rank[i]);
        } else {
            akp_set_fg_rgb(0, 200, 255);
            printf("[%d -> %d] ", i, dsu->parent[i]);
        }
        akp_reset_color();
    }
    printf("\n\n");

    // Connected Components Grouping
    printf("  Connected Component Sets:\n");
    bool* visited = (bool*)calloc((size_t)dsu->n, sizeof(bool));
    if (visited) {
        int group_num = 1;
        for (int i = 0; i < dsu->n; i++) {
            int root_i = akp_dsu_find(dsu, i);
            if (!visited[root_i]) {
                visited[root_i] = true;
                akp_set_fg_rgb(255, 0, 128);
                printf("    Component %2d (Root %d): { ", group_num++, root_i);
                akp_reset_color();

                for (int j = 0; j < dsu->n; j++) {
                    if (akp_dsu_find(dsu, j) == root_i) {
                        akp_set_fg_rgb(255, 255, 255);
                        printf("%d ", j);
                        akp_reset_color();
                    }
                }
                akp_set_fg_rgb(255, 0, 128);
                printf("}\n");
                akp_reset_color();
            }
        }
        free(visited);
    }
    printf("\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_DISJOINT_SET_H */
