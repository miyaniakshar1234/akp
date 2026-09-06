/**
 * ============================================================================
 * AKP ENGINE - HIGH PERFORMANCE C/C++ FLASHY TOOLKIT
 * SUBSYSTEM: min_heap.h (Visual Binary Min-Heap & Priority Queue)
 * 
 * Engineered & Authored by: Akshar Miyani
 * AKP Studio Systems Architecture | Release v1.6.0
 * ============================================================================
 */

#ifndef AKP_MIN_HEAP_H
#define AKP_MIN_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "color.h"
#include "badge.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int* data;
    int size;
    int capacity;
    char name[32];
} akp_min_heap_t;

static inline akp_min_heap_t* akp_min_heap_create(int capacity, const char* name) {
    akp_min_heap_t* heap = (akp_min_heap_t*)malloc(sizeof(akp_min_heap_t));
    if (!heap) return NULL;
    heap->capacity = capacity > 0 ? capacity : 16;
    heap->data = (int*)malloc((size_t)heap->capacity * sizeof(int));
    heap->size = 0;
    if (name) {
        strncpy(heap->name, name, sizeof(heap->name) - 1);
        heap->name[sizeof(heap->name) - 1] = '\0';
    } else {
        strcpy(heap->name, "MinHeap");
    }
    return heap;
}

static inline void akp_min_heap_destroy(akp_min_heap_t* heap) {
    if (!heap) return;
    if (heap->data) free(heap->data);
    free(heap);
}

static inline void akp_min_heap_swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline bool akp_min_heap_insert(akp_min_heap_t* heap, int val) {
    if (!heap) return false;
    if (heap->size >= heap->capacity) {
        int new_cap = heap->capacity * 2;
        int* new_data = (int*)realloc(heap->data, (size_t)new_cap * sizeof(int));
        if (!new_data) return false;
        heap->data = new_data;
        heap->capacity = new_cap;
    }
    
    int i = heap->size++;
    heap->data[i] = val;

    // Heapify Up
    while (i != 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent] > heap->data[i]) {
            akp_min_heap_swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        } else {
            break;
        }
    }
    return true;
}

static inline bool akp_min_heap_extract_min(akp_min_heap_t* heap, int* out_val) {
    if (!heap || heap->size <= 0) return false;
    if (out_val) *out_val = heap->data[0];

    if (heap->size == 1) {
        heap->size--;
        return true;
    }

    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    // Heapify Down
    int i = 0;
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest != i) {
            akp_min_heap_swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return true;
}

static inline int akp_min_heap_peek(const akp_min_heap_t* heap) {
    if (!heap || heap->size <= 0) return -1;
    return heap->data[0];
}

static inline void akp_min_heap_render(const akp_min_heap_t* heap, const char* title) {
    akp_init_console();
    printf("\n");
    akp_set_fg_rgb(0, 255, 230);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  🔷 BINARY MIN-HEAP & PRIORITY QUEUE TELEMETRY                                ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    akp_reset_color();

    if (title) {
        akp_set_fg_rgb(255, 215, 0);
        printf("  ⚡ Heap Name: %s (%s)\n", heap ? heap->name : "N/A", title);
        akp_reset_color();
    }

    if (!heap || heap->size == 0) {
        akp_set_fg_rgb(255, 70, 85);
        printf("  [ Heap is currently EMPTY ]\n\n");
        akp_reset_color();
        return;
    }

    akp_set_fg_rgb(0, 255, 170);
    printf("  Elements: %d / %d  |  Min Value (Root): %d\n\n", heap->size, heap->capacity, heap->data[0]);
    akp_reset_color();

    // 1. Array representation
    printf("  Linear Memory Layout (Array Storage):\n  ");
    for (int i = 0; i < heap->size; i++) {
        if (i == 0) {
            akp_set_fg_rgb(255, 215, 0);
            printf("[%d: ROOT(%d)] ", i, heap->data[i]);
        } else {
            int p = (i - 1) / 2;
            akp_set_fg_rgb(0, 200, 255);
            printf("[%d: %d (P:%d)] ", i, heap->data[i], p);
        }
        akp_reset_color();
    }
    printf("\n\n");

    // 2. Hierarchical Tree Level Print
    printf("  Binary Tree Level Breakdown:\n");
    int level = 0;
    int count = 1;
    int idx = 0;
    while (idx < heap->size) {
        akp_set_fg_rgb(255, 0, 128);
        printf("    Level %d: ", level);
        akp_reset_color();

        for (int c = 0; c < count && idx < heap->size; c++, idx++) {
            akp_set_fg_rgb(255, 255, 255);
            printf("(%d) ", heap->data[idx]);
            akp_reset_color();
        }
        printf("\n");
        level++;
        count *= 2;
    }
    printf("\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_MIN_HEAP_H */
