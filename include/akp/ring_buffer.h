/**
 * ============================================================================
 * AKP ENGINE - HIGH PERFORMANCE C/C++ FLASHY TOOLKIT
 * SUBSYSTEM: ring_buffer.h (High-Throughput Lockless Visual Ring Buffer)
 * 
 * Engineered & Authored by: Akshar Miyani
 * AKP Studio Systems Architecture | Release v1.7.0
 * ============================================================================
 */

#ifndef AKP_RING_BUFFER_H
#define AKP_RING_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "color.h"
#include "badge.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint8_t* buffer;
    size_t capacity;
    size_t mask;
    size_t head; // write index
    size_t tail; // read index
    size_t total_written;
    size_t total_read;
} akp_ring_buf_t;

static inline size_t akp_next_pow2(size_t v) {
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
#if UINTPTR_MAX > 0xFFFFFFFF
    v |= v >> 32;
#endif
    v++;
    return v == 0 ? 1 : v;
}

static inline akp_ring_buf_t* akp_ring_create(size_t capacity) {
    if (capacity < 4) capacity = 4;
    size_t cap = akp_next_pow2(capacity);

    akp_ring_buf_t* rb = (akp_ring_buf_t*)malloc(sizeof(akp_ring_buf_t));
    if (!rb) return NULL;

    rb->capacity = cap;
    rb->mask = cap - 1;
    rb->buffer = (uint8_t*)malloc(cap);
    if (!rb->buffer) {
        free(rb);
        return NULL;
    }
    rb->head = 0;
    rb->tail = 0;
    rb->total_written = 0;
    rb->total_read = 0;
    return rb;
}

static inline void akp_ring_destroy(akp_ring_buf_t* rb) {
    if (!rb) return;
    if (rb->buffer) free(rb->buffer);
    free(rb);
}

static inline size_t akp_ring_available(const akp_ring_buf_t* rb) {
    if (!rb) return 0;
    return rb->head - rb->tail;
}

static inline size_t akp_ring_free_space(const akp_ring_buf_t* rb) {
    if (!rb) return 0;
    return rb->capacity - (rb->head - rb->tail);
}

static inline bool akp_ring_write(akp_ring_buf_t* rb, uint8_t byte) {
    if (!rb || akp_ring_free_space(rb) == 0) return false;
    rb->buffer[rb->head & rb->mask] = byte;
    rb->head++;
    rb->total_written++;
    return true;
}

static inline bool akp_ring_read(akp_ring_buf_t* rb, uint8_t* out_byte) {
    if (!rb || akp_ring_available(rb) == 0) return false;
    if (out_byte) *out_byte = rb->buffer[rb->tail & rb->mask];
    rb->tail++;
    rb->total_read++;
    return true;
}

static inline void akp_ring_render(const akp_ring_buf_t* rb, const char* title) {
    akp_init_console();
    printf("\n");
    akp_set_fg_rgb(0, 255, 230);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  🔄 LOCKLESS SPSC CIRCULAR RING BUFFER TELEMETRY                              ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    akp_reset_color();

    if (title) {
        akp_set_fg_rgb(255, 215, 0);
        printf("  ⚡ Channel: %s\n", title);
        akp_reset_color();
    }

    if (!rb) {
        akp_set_fg_rgb(255, 70, 85);
        printf("  [ Ring Buffer is NULL ]\n\n");
        akp_reset_color();
        return;
    }

    size_t occupied = akp_ring_available(rb);
    double fill_pct = (double)occupied / (double)rb->capacity * 100.0;

    akp_set_fg_rgb(0, 255, 170);
    printf("  Capacity: %zu bytes  |  Occupancy: %zu / %zu (%.1f%%)\n",
           rb->capacity, occupied, rb->capacity, fill_pct);
    printf("  Total Written: %zu bytes  |  Total Read: %zu bytes\n\n",
           rb->total_written, rb->total_read);
    akp_reset_color();

    // Fill Gauge Bar
    printf("  Fill Gauge: [");
    int bar_width = 30;
    int filled = (int)((fill_pct / 100.0) * bar_width);
    for (int i = 0; i < bar_width; i++) {
        if (i < filled) {
            akp_set_fg_rgb(0, 255, 200);
            printf("█");
        } else {
            akp_set_fg_rgb(80, 80, 100);
            printf("░");
        }
    }
    akp_reset_color();
    printf("] %.1f%%\n\n", fill_pct);

    // Slot array visualization
    printf("  Slot State (W: Write Head, R: Read Tail):\n  ");
    for (size_t i = 0; i < rb->capacity; i++) {
        size_t h_idx = rb->head & rb->mask;
        size_t t_idx = rb->tail & rb->mask;
        bool is_head = (i == h_idx);
        bool is_tail = (i == t_idx);

        if (is_head && is_tail) {
            akp_set_fg_rgb(255, 215, 0);
            printf("[%02zu: W/R] ", i);
        } else if (is_head) {
            akp_set_fg_rgb(0, 255, 100);
            printf("[%02zu: W->] ", i);
        } else if (is_tail) {
            akp_set_fg_rgb(255, 0, 128);
            printf("[%02zu: <-R] ", i);
        } else {
            akp_set_fg_rgb(100, 120, 150);
            printf("[%02zu: 0x%02X] ", i, rb->buffer[i]);
        }
        akp_reset_color();
    }
    printf("\n\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_RING_BUFFER_H */
