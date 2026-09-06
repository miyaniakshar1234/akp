/**
 * ============================================================================
 *  AKP ENGINE - LINEAR MEMORY ARENA ALLOCATOR (akp/arena.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: High-Performance Bump Allocator & Instant O(1) Memory Reset
 * ============================================================================
 */

#ifndef AKP_ARENA_H
#define AKP_ARENA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "color.h"
#include "badge.h"

#define AKP_ARENA_DEFAULT_ALIGNMENT 8

typedef struct {
    uint8_t* buffer;
    size_t capacity;
    size_t offset;
    size_t peak_offset;
    size_t alloc_count;
} akp_arena_t;

static inline size_t akp_arena_align_forward(size_t ptr, size_t align) {
    return (ptr + align - 1) & ~(align - 1);
}

/**
 * Creates a contiguous linear memory arena with fixed capacity
 */
static inline akp_arena_t* akp_arena_create(size_t capacity) {
    akp_init_console();
    if (capacity < 128) capacity = 128;

    akp_arena_t* arena = (akp_arena_t*)malloc(sizeof(akp_arena_t));
    if (!arena) return NULL;

    arena->capacity = capacity;
    arena->offset = 0;
    arena->peak_offset = 0;
    arena->alloc_count = 0;

    arena->buffer = (uint8_t*)malloc(capacity);
    if (!arena->buffer) {
        free(arena);
        return NULL;
    }
    return arena;
}

/**
 * Frees the entire memory arena buffer
 */
static inline void akp_arena_destroy(akp_arena_t* arena) {
    if (arena) {
        if (arena->buffer) free(arena->buffer);
        free(arena);
    }
}

/**
 * Allocates aligned memory block from linear arena (Zero heap fragmentation)
 */
static inline void* akp_arena_alloc_aligned(akp_arena_t* arena, size_t size, size_t alignment) {
    if (!arena || size == 0) return NULL;

    size_t aligned_offset = akp_arena_align_forward(arena->offset, alignment);
    if (aligned_offset + size > arena->capacity) {
        return NULL; /* Out of arena scratch memory */
    }

    void* ptr = (void*)(arena->buffer + aligned_offset);
    arena->offset = aligned_offset + size;
    arena->alloc_count++;

    if (arena->offset > arena->peak_offset) {
        arena->peak_offset = arena->offset;
    }
    return ptr;
}

static inline void* akp_arena_alloc(akp_arena_t* arena, size_t size) {
    return akp_arena_alloc_aligned(arena, size, AKP_ARENA_DEFAULT_ALIGNMENT);
}

static inline void* akp_arena_alloc_zero(akp_arena_t* arena, size_t size) {
    void* ptr = akp_arena_alloc(arena, size);
    if (ptr) {
        memset(ptr, 0, size);
    }
    return ptr;
}

/**
 * Instant O(1) Arena Reset: Reclaims all allocated scratch blocks
 */
static inline void akp_arena_reset(akp_arena_t* arena) {
    if (arena) {
        arena->offset = 0;
        arena->alloc_count = 0;
    }
}

/**
 * Renders Linear Arena Memory Utilization & High-Water Mark Telemetry
 */
static inline void akp_arena_render(const akp_arena_t* arena, const char* title) {
    if (!arena) return;
    akp_init_console();

    double used_pct = (double)arena->offset / (double)arena->capacity * 100.0;
    double peak_pct = (double)arena->peak_offset / (double)arena->capacity * 100.0;

    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║  ⚡ LINEAR MEMORY ARENA TELEMETRY: %-42s ║\n" AKP_RESET, title ? title : "Scratch Buffer Pool");
    printf(AKP_BOLD AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    printf("  Arena Capacity: %llu bytes (%.2f KB)  |  Active Allocations: %llu\n",
           (unsigned long long)arena->capacity, (double)arena->capacity / 1024.0, (unsigned long long)arena->alloc_count);
    printf("  Current Offset: %llu bytes (%.1f%%)  |  Peak High-Water Mark: %llu bytes (%.1f%%)\n",
           (unsigned long long)arena->offset, used_pct, (unsigned long long)arena->peak_offset, peak_pct);

    /* Memory Block Utilization Bar */
    printf("\n  Memory Map: [");
    int bar_width = 36;
    int filled = (int)((used_pct / 100.0) * bar_width);
    int peak_pos = (int)((peak_pct / 100.0) * bar_width);

    for (int i = 0; i < bar_width; i++) {
        if (i < filled) {
            printf(AKP_BOLD AKP_NEON_GREEN "█" AKP_RESET);
        } else if (i == peak_pos && peak_pos > filled) {
            printf(AKP_BOLD AKP_NEON_GOLD "▲" AKP_RESET);
        } else {
            printf(AKP_DIM "░" AKP_RESET);
        }
    }
    printf("] %.1f%% used\n", used_pct);
    printf("  " AKP_DIM "↳ Legend: █ In-Use  ░ Free Scratch  ▲ Peak High-Water Mark\n\n" AKP_RESET);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_ARENA_H */
