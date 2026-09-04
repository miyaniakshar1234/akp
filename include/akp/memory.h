/**
 * ============================================================================
 *  AKP ENGINE - MEMORY AUDIT & HEX-DUMP MODULE (akp/memory.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_MEMORY_H
#define AKP_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"
#include <stdint.h>

static inline void akp_hexdump(const void* ptr, size_t size, const char* label) {
    const uint8_t* byte_ptr = (const uint8_t*)ptr;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_YELLOW "─── [ HEX-DUMP: %s (Address: %p, Size: %zu bytes) ] ───" AKP_RESET "\n", 
           label ? label : "Memory Block", ptr, size);
    
    printf(AKP_DIM " Offset     00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  | ASCII          |\n" AKP_RESET);
    printf(AKP_DIM " ─────────  ───────────────────────────────────────────────  | ────────────── |\n" AKP_RESET);

    for (size_t i = 0; i < size; i += 16) {
        printf(AKP_NEON_CYAN " %08zx  " AKP_RESET, i);
        for (size_t j = 0; j < 16; j++) {
            if (i + j < size) {
                uint8_t b = byte_ptr[i + j];
                if (b == 0x00) printf(AKP_DIM "%02x " AKP_RESET, b);
                else if (b >= 32 && b <= 126) printf(AKP_NEON_GREEN "%02x " AKP_RESET, b);
                else printf(AKP_NEON_PINK "%02x " AKP_RESET, b);
            } else {
                printf("   ");
            }
            if (j == 7) printf(" ");
        }
        printf(" | ");
        for (size_t j = 0; j < 16; j++) {
            if (i + j < size) {
                uint8_t b = byte_ptr[i + j];
                if (b >= 32 && b <= 126) printf(AKP_BOLD AKP_FG_WHITE "%c" AKP_RESET, b);
                else printf(AKP_DIM "." AKP_RESET);
            } else {
                printf(" ");
            }
        }
        printf(" |\n");
    }
    printf(AKP_DIM " ─────────  ───────────────────────────────────────────────  | ────────────── |\n\n" AKP_RESET);
}

/* Heap Tracking System */
static size_t g_akp_allocated_bytes = 0;
static size_t g_akp_peak_bytes = 0;
static size_t g_akp_alloc_count = 0;
static size_t g_akp_free_count = 0;

static inline void* akp_malloc_tracked(size_t sz, const char* file, int line) {
    (void)file; (void)line;
    size_t total_sz = sz + sizeof(size_t);
    size_t* p = (size_t*)malloc(total_sz);
    if (!p) return NULL;
    *p = sz;
    g_akp_allocated_bytes += sz;
    if (g_akp_allocated_bytes > g_akp_peak_bytes) g_akp_peak_bytes = g_akp_allocated_bytes;
    g_akp_alloc_count++;
    return (void*)(p + 1);
}

static inline void akp_free_tracked(void* ptr) {
    if (!ptr) return;
    size_t* p = ((size_t*)ptr) - 1;
    size_t sz = *p;
    g_akp_allocated_bytes -= sz;
    g_akp_free_count++;
    free(p);
}

#define AKP_MALLOC(sz) akp_malloc_tracked((sz), __FILE__, __LINE__)
#define AKP_FREE(p)    akp_free_tracked(p)

static inline void akp_mem_report(void) {
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_PURPLE "╔═══════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_PURPLE "║               🔍 AKP HEAP ALLOCATION AUDIT                    ║\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_PURPLE "╠═══════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║  Total Allocations:   " AKP_BOLD AKP_NEON_CYAN "%-10zu" AKP_RESET "                              ║\n", g_akp_alloc_count);
    printf("║  Total Deallocations: " AKP_BOLD AKP_NEON_CYAN "%-10zu" AKP_RESET "                              ║\n", g_akp_free_count);
    printf("║  Peak Memory Used:    " AKP_BOLD AKP_GOLD "%-10zu bytes" AKP_RESET "                        ║\n", g_akp_peak_bytes);
    if (g_akp_allocated_bytes > 0) {
        printf("║  Status:              " AKP_BOLD AKP_FG_RED "⚠ MEMORY LEAK (%zu bytes active)" AKP_RESET "      ║\n", g_akp_allocated_bytes);
    } else {
        printf("║  Status:              " AKP_BOLD AKP_NEON_GREEN "✔ ZERO LEAKS (Clean Memory)" AKP_RESET "               ║\n");
    }
    printf(AKP_BOLD AKP_NEON_PURPLE "╚═══════════════════════════════════════════════════════════════╝\n\n" AKP_RESET);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_MEMORY_H */

/* Verified: 2026-09-04 23:29:24 */
