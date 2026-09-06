/**
 * ============================================================================
 *  AKP ENGINE - HASH TABLE VISUALIZER (akp/hash_table.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Visual in-terminal Hash Table with Collision Handling & Load Factor
 * ============================================================================
 */

#ifndef AKP_HASH_TABLE_H
#define AKP_HASH_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "badge.h"

typedef struct akp_ht_node {
    int key;
    int value;
    struct akp_ht_node* next;
} akp_ht_node_t;

typedef struct {
    akp_ht_node_t** buckets;
    int num_buckets;
    int num_elements;
    int collisions;
    char name[32];
} akp_ht_t;

static inline int akp_ht_hash(int key, int num_buckets) {
    int h = key % num_buckets;
    return (h < 0) ? (h + num_buckets) : h;
}

static inline akp_ht_t* akp_ht_create(int num_buckets, const char* name) {
    akp_init_console();
    if (num_buckets <= 0) num_buckets = 8;
    akp_ht_t* ht = (akp_ht_t*)malloc(sizeof(akp_ht_t));
    if (!ht) return NULL;

    ht->num_buckets = num_buckets;
    ht->num_elements = 0;
    ht->collisions = 0;
    strncpy(ht->name, name ? name : "HashTable", sizeof(ht->name) - 1);
    ht->name[sizeof(ht->name) - 1] = '\0';

    ht->buckets = (akp_ht_node_t**)calloc((size_t)num_buckets, sizeof(akp_ht_node_t*));
    return ht;
}

static inline void akp_ht_insert(akp_ht_t* ht, int key, int value) {
    if (!ht) return;
    int idx = akp_ht_hash(key, ht->num_buckets);

    /* Check if key exists */
    akp_ht_node_t* cur = ht->buckets[idx];
    while (cur) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }

    /* If bucket already had nodes, it's a collision */
    if (ht->buckets[idx] != NULL) {
        ht->collisions++;
    }

    akp_ht_node_t* new_node = (akp_ht_node_t*)malloc(sizeof(akp_ht_node_t));
    new_node->key = key;
    new_node->value = value;
    new_node->next = ht->buckets[idx];
    ht->buckets[idx] = new_node;
    ht->num_elements++;
}

static inline int akp_ht_search(const akp_ht_t* ht, int key, int* out_value) {
    if (!ht) return 0;
    int idx = akp_ht_hash(key, ht->num_buckets);
    akp_ht_node_t* cur = ht->buckets[idx];
    while (cur) {
        if (cur->key == key) {
            if (out_value) *out_value = cur->value;
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

static inline void akp_ht_render(const akp_ht_t* ht) {
    if (!ht) return;
    akp_init_console();

    float load_factor = (ht->num_buckets > 0) ? ((float)ht->num_elements / (float)ht->num_buckets) : 0.0f;

    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║ 🗄️  HASH TABLE VISUALIZER (CHAINING): %-33s ║\n" AKP_RESET, ht->name);
    printf(AKP_BOLD AKP_NEON_CYAN "╠═════════════════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║ Buckets: %2d | Elements: %2d | Collisions: %2d | Load Factor: %4.2f      ║\n",
           ht->num_buckets, ht->num_elements, ht->collisions, load_factor);
    printf(AKP_BOLD AKP_NEON_CYAN "╚═════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    for (int i = 0; i < ht->num_buckets; i++) {
        printf(AKP_BOLD AKP_NEON_GOLD " [Bucket %2d] " AKP_RESET, i);
        akp_ht_node_t* cur = ht->buckets[i];
        if (!cur) {
            printf(AKP_DIM "--> (empty)\n" AKP_RESET);
        } else {
            while (cur) {
                printf("--> " AKP_BOLD AKP_NEON_CYAN "[Key: %3d | Val: %4d]" AKP_RESET " ", cur->key, cur->value);
                cur = cur->next;
            }
            printf("--> " AKP_DIM "NULL\n" AKP_RESET);
        }
    }
    printf("\n");
}

static inline void akp_ht_free(akp_ht_t* ht) {
    if (!ht) return;
    for (int i = 0; i < ht->num_buckets; i++) {
        akp_ht_node_t* cur = ht->buckets[i];
        while (cur) {
            akp_ht_node_t* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(ht->buckets);
    free(ht);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_HASH_TABLE_H */
