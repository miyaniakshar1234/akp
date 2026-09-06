/**
 * ============================================================================
 * AKP ENGINE - HIGH PERFORMANCE C/C++ FLASHY TOOLKIT
 * SUBSYSTEM: bitset.h (Visual Bitset & Low-Level Binary Telemetry Engine)
 * 
 * Engineered & Authored by: Akshar Miyani
 * AKP Studio Systems Architecture | Release v1.7.0
 * ============================================================================
 */

#ifndef AKP_BITSET_H
#define AKP_BITSET_H

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
    uint64_t* words;
    size_t num_bits;
    size_t num_words;
} akp_bitset_t;

static inline akp_bitset_t* akp_bitset_create(size_t num_bits) {
    if (num_bits == 0) num_bits = 64;
    akp_bitset_t* bs = (akp_bitset_t*)malloc(sizeof(akp_bitset_t));
    if (!bs) return NULL;

    bs->num_bits = num_bits;
    bs->num_words = (num_bits + 63) / 64;
    bs->words = (uint64_t*)calloc(bs->num_words, sizeof(uint64_t));
    if (!bs->words) {
        free(bs);
        return NULL;
    }
    return bs;
}

static inline void akp_bitset_destroy(akp_bitset_t* bs) {
    if (!bs) return;
    if (bs->words) free(bs->words);
    free(bs);
}

static inline void akp_bitset_set(akp_bitset_t* bs, size_t bit_idx) {
    if (!bs || bit_idx >= bs->num_bits) return;
    bs->words[bit_idx / 64] |= ((uint64_t)1 << (bit_idx % 64));
}

static inline void akp_bitset_clear(akp_bitset_t* bs, size_t bit_idx) {
    if (!bs || bit_idx >= bs->num_bits) return;
    bs->words[bit_idx / 64] &= ~((uint64_t)1 << (bit_idx % 64));
}

static inline void akp_bitset_flip(akp_bitset_t* bs, size_t bit_idx) {
    if (!bs || bit_idx >= bs->num_bits) return;
    bs->words[bit_idx / 64] ^= ((uint64_t)1 << (bit_idx % 64));
}

static inline bool akp_bitset_test(const akp_bitset_t* bs, size_t bit_idx) {
    if (!bs || bit_idx >= bs->num_bits) return false;
    return (bs->words[bit_idx / 64] & ((uint64_t)1 << (bit_idx % 64))) != 0;
}

static inline void akp_bitset_set_all(akp_bitset_t* bs) {
    if (!bs) return;
    memset(bs->words, 0xFF, bs->num_words * sizeof(uint64_t));
    // Mask extra bits in last word
    size_t rem = bs->num_bits % 64;
    if (rem != 0) {
        bs->words[bs->num_words - 1] &= (((uint64_t)1 << rem) - 1);
    }
}

static inline void akp_bitset_clear_all(akp_bitset_t* bs) {
    if (!bs) return;
    memset(bs->words, 0, bs->num_words * sizeof(uint64_t));
}

static inline size_t akp_bitset_count(const akp_bitset_t* bs) {
    if (!bs) return 0;
    size_t count = 0;
    for (size_t i = 0; i < bs->num_words; i++) {
        uint64_t w = bs->words[i];
        // Brian Kernighan's algorithm for popcount
        while (w) {
            w &= (w - 1);
            count++;
        }
    }
    return count;
}

static inline void akp_bitset_render(const akp_bitset_t* bs, const char* title) {
    akp_init_console();
    printf("\n");
    akp_set_fg_rgb(0, 255, 230);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  🔢 BINARY BITSET & HARDWARE REGISTER TELEMETRY ENGINE                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    akp_reset_color();

    if (title) {
        akp_set_fg_rgb(255, 215, 0);
        printf("  ⚡ Register / Bitmask: %s\n", title);
        akp_reset_color();
    }

    if (!bs) {
        akp_set_fg_rgb(255, 70, 85);
        printf("  [ Bitset is NULL ]\n\n");
        akp_reset_color();
        return;
    }

    size_t set_bits = akp_bitset_count(bs);
    size_t clear_bits = bs->num_bits - set_bits;
    double density = (double)set_bits / (double)bs->num_bits * 100.0;

    akp_set_fg_rgb(0, 255, 170);
    printf("  Total Bits: %zu  |  Set (Hamming Weight): %zu  |  Clear: %zu  |  Density: %.1f%%\n\n",
           bs->num_bits, set_bits, clear_bits, density);
    akp_reset_color();

    // Render bit groups
    printf("  Bit Vector Map:\n  ");
    for (size_t i = 0; i < bs->num_bits; i++) {
        if (i > 0 && i % 8 == 0) {
            akp_set_fg_rgb(100, 100, 120);
            printf("| ");
            akp_reset_color();
        }
        if (i > 0 && i % 32 == 0) {
            printf("\n  ");
        }

        if (akp_bitset_test(bs, i)) {
            akp_set_fg_rgb(57, 255, 20); // Neon Green for '1'
            printf("1 ");
        } else {
            akp_set_fg_rgb(100, 100, 120); // Dim for '0'
            printf("· ");
        }
        akp_reset_color();
    }
    printf("\n\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_BITSET_H */
