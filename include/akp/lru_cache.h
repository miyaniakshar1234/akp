/**
 * ============================================================================
 * AKP ENGINE - HIGH PERFORMANCE C/C++ FLASHY TOOLKIT
 * SUBSYSTEM: lru_cache.h (Visual LRU Cache Simulator & Buffer Management)
 * 
 * Engineered & Authored by: Akshar Miyani
 * AKP Studio Systems Architecture | Release v1.6.0
 * ============================================================================
 */

#ifndef AKP_LRU_CACHE_H
#define AKP_LRU_CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "color.h"
#include "badge.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct akp_lru_node {
    int key;
    int value;
    struct akp_lru_node* prev;
    struct akp_lru_node* next;
} akp_lru_node_t;

typedef struct {
    int capacity;
    int count;
    int hits;
    int misses;
    akp_lru_node_t* head; // MRU (Most Recently Used)
    akp_lru_node_t* tail; // LRU (Least Recently Used)
} akp_lru_cache_t;

static inline akp_lru_cache_t* akp_lru_create(int capacity) {
    if (capacity <= 0) capacity = 4;
    akp_lru_cache_t* cache = (akp_lru_cache_t*)malloc(sizeof(akp_lru_cache_t));
    if (!cache) return NULL;
    cache->capacity = capacity;
    cache->count = 0;
    cache->hits = 0;
    cache->misses = 0;
    cache->head = NULL;
    cache->tail = NULL;
    return cache;
}

static inline void akp_lru_destroy(akp_lru_cache_t* cache) {
    if (!cache) return;
    akp_lru_node_t* curr = cache->head;
    while (curr) {
        akp_lru_node_t* nxt = curr->next;
        free(curr);
        curr = nxt;
    }
    free(cache);
}

static inline void akp_lru_move_to_head(akp_lru_cache_t* cache, akp_lru_node_t* node) {
    if (!cache || !node || cache->head == node) return;

    // Detach node from current position
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (cache->tail == node) {
        cache->tail = node->prev;
    }

    // Attach to head
    node->prev = NULL;
    node->next = cache->head;
    if (cache->head) {
        cache->head->prev = node;
    }
    cache->head = node;

    if (!cache->tail) {
        cache->tail = node;
    }
}

static inline int akp_lru_get(akp_lru_cache_t* cache, int key) {
    if (!cache) return -1;
    akp_lru_node_t* curr = cache->head;
    while (curr) {
        if (curr->key == key) {
            cache->hits++;
            akp_lru_move_to_head(cache, curr);
            return curr->value;
        }
        curr = curr->next;
    }
    cache->misses++;
    return -1;
}

static inline void akp_lru_put(akp_lru_cache_t* cache, int key, int value) {
    if (!cache) return;

    // Check if key already exists
    akp_lru_node_t* curr = cache->head;
    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            akp_lru_move_to_head(cache, curr);
            return;
        }
        curr = curr->next;
    }

    // Allocate new node
    akp_lru_node_t* new_node = (akp_lru_node_t*)malloc(sizeof(akp_lru_node_t));
    if (!new_node) return;
    new_node->key = key;
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = cache->head;

    if (cache->head) {
        cache->head->prev = new_node;
    }
    cache->head = new_node;
    if (!cache->tail) {
        cache->tail = new_node;
    }
    cache->count++;

    // Evict if over capacity
    if (cache->count > cache->capacity) {
        akp_lru_node_t* lru = cache->tail;
        if (lru) {
            if (lru->prev) {
                lru->prev->next = NULL;
            }
            cache->tail = lru->prev;
            free(lru);
            cache->count--;
        }
    }
}

static inline void akp_lru_render(const akp_lru_cache_t* cache, const char* title) {
    akp_init_console();
    printf("\n");
    akp_set_fg_rgb(0, 255, 230);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  💾 LRU (LEAST RECENTLY USED) CACHE & BUFFER POOL TELEMETRY                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    akp_reset_color();

    if (title) {
        akp_set_fg_rgb(255, 215, 0);
        printf("  ⚡ Cache Domain: %s\n", title);
        akp_reset_color();
    }

    if (!cache) {
        akp_set_fg_rgb(255, 70, 85);
        printf("  [ Cache is NULL ]\n\n");
        akp_reset_color();
        return;
    }

    int total_queries = cache->hits + cache->misses;
    double hit_ratio = total_queries > 0 ? ((double)cache->hits / (double)total_queries) * 100.0 : 0.0;

    akp_set_fg_rgb(0, 255, 170);
    printf("  Capacity: %d | Occupancy: %d / %d | Hits: %d | Misses: %d | Hit Ratio: %.1f%%\n\n",
           cache->capacity, cache->count, cache->capacity, cache->hits, cache->misses, hit_ratio);
    akp_reset_color();

    printf("  Cache Line Order (MRU to LRU):\n  ");
    akp_set_fg_rgb(255, 215, 0);
    printf("[MRU / HEAD] -> ");
    akp_reset_color();

    akp_lru_node_t* curr = cache->head;
    while (curr) {
        akp_set_fg_rgb(0, 200, 255);
        printf("[K:%d | V:%d]", curr->key, curr->value);
        akp_reset_color();

        if (curr->next) {
            akp_set_fg_rgb(255, 0, 128);
            printf(" <-> ");
            akp_reset_color();
        }
        curr = curr->next;
    }

    akp_set_fg_rgb(255, 70, 85);
    printf(" -> [LRU / TAIL]\n\n");
    akp_reset_color();
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_LRU_CACHE_H */
