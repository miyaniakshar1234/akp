/**
 * ============================================================================
 *  AKP ENGINE - STACK & CIRCULAR QUEUE VISUALIZER (akp/stack_queue.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Visual in-terminal LIFO Stack and FIFO Circular Queue for Lab Flexing
 * ============================================================================
 */

#ifndef AKP_STACK_QUEUE_H
#define AKP_STACK_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "badge.h"

/* ============================================================================
 *  1. VISUAL LIFO STACK
 * ============================================================================
 */

typedef struct {
    int* data;
    int top;
    int capacity;
    char name[32];
} akp_stack_t;

static inline akp_stack_t* akp_stack_create(int capacity, const char* name) {
    akp_init_console();
    if (capacity <= 0) capacity = 8;
    akp_stack_t* s = (akp_stack_t*)malloc(sizeof(akp_stack_t));
    if (!s) return NULL;
    s->data = (int*)malloc(sizeof(int) * capacity);
    s->top = -1;
    s->capacity = capacity;
    strncpy(s->name, name ? name : "Stack", sizeof(s->name) - 1);
    s->name[sizeof(s->name) - 1] = '\0';
    return s;
}

static inline void akp_stack_free(akp_stack_t* s) {
    if (!s) return;
    if (s->data) free(s->data);
    free(s);
}

static inline int akp_stack_is_empty(const akp_stack_t* s) {
    return (s == NULL || s->top < 0);
}

static inline int akp_stack_is_full(const akp_stack_t* s) {
    return (s != NULL && s->top >= s->capacity - 1);
}

static inline int akp_stack_push(akp_stack_t* s, int value) {
    if (!s) return 0;
    if (akp_stack_is_full(s)) {
        akp_log_error("STACK", "Stack Overflow! Cannot push element.");
        return 0;
    }
    s->top++;
    s->data[s->top] = value;
    return 1;
}

static inline int akp_stack_pop(akp_stack_t* s, int* out_value) {
    if (!s || akp_stack_is_empty(s)) {
        akp_log_error("STACK", "Stack Underflow! Stack is currently empty.");
        return 0;
    }
    if (out_value) *out_value = s->data[s->top];
    s->top--;
    return 1;
}

static inline void akp_stack_render(const akp_stack_t* s) {
    if (!s) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_CYAN "┌────────────────────────────────────────────────────────┐\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "│ 📦 VISUAL STACK (LIFO): %-31s│\n" AKP_RESET, s->name);
    printf(AKP_BOLD AKP_NEON_CYAN "├────────────────────────────────────────────────────────┤\n" AKP_RESET);

    if (s->top < 0) {
        printf(AKP_BOLD AKP_DIM "│  [ STACK IS CURRENTLY EMPTY (TOP = -1) ]               │\n" AKP_RESET);
    } else {
        for (int i = s->top; i >= 0; i--) {
            const char* tag = (i == s->top) ? "TOP ->" : (i == 0 ? "BOT ->" : "      ");
            const char* col = (i == s->top) ? AKP_NEON_GOLD : AKP_NEON_CYAN;
            printf(AKP_BOLD "│   %s %s│ %6d │%s  (index: %2d)                     │\n" AKP_RESET,
                   tag, col, s->data[i], AKP_RESET, i);
            if (i > 0) {
                printf(AKP_BOLD AKP_DIM "│          ├──--------──┤                                │\n" AKP_RESET);
            }
        }
    }

    printf(AKP_BOLD AKP_NEON_CYAN "├────────────────────────────────────────────────────────┤\n" AKP_RESET);
    int pct = (s->capacity > 0) ? ((s->top + 1) * 100) / s->capacity : 0;
    int filled_bars = (pct * 20) / 100;
    printf(AKP_BOLD "│  Load: [" AKP_NEON_GREEN);
    for (int b = 0; b < 20; b++) {
        if (b < filled_bars) printf("█");
        else printf(AKP_DIM "░" AKP_RESET AKP_BOLD);
    }
    printf(AKP_RESET AKP_BOLD "] %3d%% (%d/%d elements)       │\n" AKP_RESET, pct, s->top + 1, s->capacity);
    printf(AKP_BOLD AKP_NEON_CYAN "└────────────────────────────────────────────────────────┘\n\n" AKP_RESET);
}

/* ============================================================================
 *  2. VISUAL CIRCULAR QUEUE
 * ============================================================================
 */

typedef struct {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
    char name[32];
} akp_queue_t;

static inline akp_queue_t* akp_queue_create(int capacity, const char* name) {
    akp_init_console();
    if (capacity <= 0) capacity = 6;
    akp_queue_t* q = (akp_queue_t*)malloc(sizeof(akp_queue_t));
    if (!q) return NULL;
    q->data = (int*)malloc(sizeof(int) * capacity);
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
    strncpy(q->name, name ? name : "CircularQueue", sizeof(q->name) - 1);
    q->name[sizeof(q->name) - 1] = '\0';
    return q;
}

static inline void akp_queue_free(akp_queue_t* q) {
    if (!q) return;
    if (q->data) free(q->data);
    free(q);
}

static inline int akp_queue_is_empty(const akp_queue_t* q) {
    return (q == NULL || q->size == 0);
}

static inline int akp_queue_is_full(const akp_queue_t* q) {
    return (q != NULL && q->size >= q->capacity);
}

static inline int akp_queue_enqueue(akp_queue_t* q, int value) {
    if (!q) return 0;
    if (akp_queue_is_full(q)) {
        akp_log_error("QUEUE", "Queue Overflow! Queue is full.");
        return 0;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
    return 1;
}

static inline int akp_queue_dequeue(akp_queue_t* q, int* out_value) {
    if (!q || akp_queue_is_empty(q)) {
        akp_log_error("QUEUE", "Queue Underflow! Queue is currently empty.");
        return 0;
    }
    if (out_value) *out_value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return 1;
}

static inline void akp_queue_render(const akp_queue_t* q) {
    if (!q) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_PINK "┌────────────────────────────────────────────────────────┐\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_PINK "│ 🔄 CIRCULAR QUEUE (FIFO): %-29s│\n" AKP_RESET, q->name);
    printf(AKP_BOLD AKP_NEON_PINK "├────────────────────────────────────────────────────────┤\n" AKP_RESET);

    /* Render array cells */
    printf("│  Slots: ");
    for (int i = 0; i < q->capacity; i++) {
        int occupied = 0;
        if (q->size > 0) {
            if (q->front <= q->rear) {
                occupied = (i >= q->front && i <= q->rear);
            } else {
                occupied = (i >= q->front || i <= q->rear);
            }
        }
        if (occupied) {
            printf(AKP_BOLD AKP_NEON_CYAN "[%4d] " AKP_RESET, q->data[i]);
        } else {
            printf(AKP_DIM "[  -- ] " AKP_RESET);
        }
    }
    printf("│\n");

    /* Render pointer markers */
    printf("│         ");
    for (int i = 0; i < q->capacity; i++) {
        int is_front = (q->size > 0 && i == q->front);
        int is_rear  = (q->size > 0 && i == q->rear);

        if (is_front && is_rear) {
            printf(AKP_BOLD AKP_NEON_GOLD " F,R   " AKP_RESET);
        } else if (is_front) {
            printf(AKP_BOLD AKP_NEON_GREEN "  F    " AKP_RESET);
        } else if (is_rear) {
            printf(AKP_BOLD AKP_NEON_PINK "  R    " AKP_RESET);
        } else {
            printf("       ");
        }
    }
    printf("│\n");

    printf(AKP_BOLD AKP_NEON_PINK "├────────────────────────────────────────────────────────┤\n" AKP_RESET);
    printf(AKP_BOLD "│  Front: %2d  |  Rear: %2d  |  Size: %2d / %2d (Capacity)     │\n" AKP_RESET,
           q->front, q->rear, q->size, q->capacity);
    printf(AKP_BOLD AKP_NEON_PINK "└────────────────────────────────────────────────────────┘\n\n" AKP_RESET);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_STACK_QUEUE_H */
