/**
 * ============================================================================
 *  AKP ENGINE - PROBABILISTIC BLOOM FILTER (akp/bloom_filter.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Multi-Hash Probabilistic Set Membership & Saturation Telemetry
 * ============================================================================
 */

#ifndef AKP_BLOOM_FILTER_H
#define AKP_BLOOM_FILTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "color.h"
#include "badge.h"

typedef struct {
    uint8_t* bits;
    size_t bit_capacity;
    size_t byte_count;
    int num_hashes;
    size_t items_added;
} akp_bloom_t;

/* FNV-1a 32-bit Hash */
static inline uint32_t akp_bloom_hash_fnv1a(const char* str) {
    uint32_t hash = 2166136261u;
    while (*str) {
        hash ^= (uint8_t)(*str++);
        hash *= 16777619u;
    }
    return hash;
}

/* DJB2 32-bit Hash */
static inline uint32_t akp_bloom_hash_djb2(const char* str) {
    uint32_t hash = 5381;
    while (*str) {
        hash = ((hash << 5) + hash) + (uint8_t)(*str++);
    }
    return hash;
}

/**
 * Allocates and initializes a Bloom Filter with bit_capacity and k hash functions
 */
static inline akp_bloom_t* akp_bloom_create(size_t bit_capacity, int num_hashes) {
    akp_init_console();
    if (bit_capacity < 64) bit_capacity = 64;
    if (num_hashes < 1) num_hashes = 1;
    if (num_hashes > 8) num_hashes = 8;

    akp_bloom_t* bf = (akp_bloom_t*)malloc(sizeof(akp_bloom_t));
    if (!bf) return NULL;

    bf->bit_capacity = bit_capacity;
    bf->byte_count = (bit_capacity + 7) / 8;
    bf->num_hashes = num_hashes;
    bf->items_added = 0;

    bf->bits = (uint8_t*)calloc(bf->byte_count, sizeof(uint8_t));
    if (!bf->bits) {
        free(bf);
        return NULL;
    }
    return bf;
}

static inline void akp_bloom_destroy(akp_bloom_t* bf) {
    if (bf) {
        if (bf->bits) free(bf->bits);
        free(bf);
    }
}

/**
 * Adds an arbitrary string key to the Bloom Filter
 */
static inline void akp_bloom_add(akp_bloom_t* bf, const char* key) {
    if (!bf || !key) return;

    uint32_t h1 = akp_bloom_hash_fnv1a(key);
    uint32_t h2 = akp_bloom_hash_djb2(key);

    for (int i = 0; i < bf->num_hashes; i++) {
        uint32_t combined = h1 + (uint32_t)i * h2;
        size_t bit_idx = combined % bf->bit_capacity;
        bf->bits[bit_idx / 8] |= (1 << (bit_idx % 8));
    }
    bf->items_added++;
}

/**
 * Checks whether key is present in Bloom Filter
 * Returns false: DEFINITELY NOT IN SET (0% false negative rate)
 * Returns true: POSSIBLY IN SET (subject to false positive probability)
 */
static inline bool akp_bloom_check(const akp_bloom_t* bf, const char* key) {
    if (!bf || !key) return false;

    uint32_t h1 = akp_bloom_hash_fnv1a(key);
    uint32_t h2 = akp_bloom_hash_djb2(key);

    for (int i = 0; i < bf->num_hashes; i++) {
        uint32_t combined = h1 + (uint32_t)i * h2;
        size_t bit_idx = combined % bf->bit_capacity;
        if (!(bf->bits[bit_idx / 8] & (1 << (bit_idx % 8)))) {
            return false; /* If ANY bit is 0, element is definitely NOT present */
        }
    }
    return true;
}

/**
 * Counts the total number of bits currently set to 1
 */
static inline size_t akp_bloom_bits_set(const akp_bloom_t* bf) {
    if (!bf) return 0;
    size_t count = 0;
    for (size_t i = 0; i < bf->byte_count; i++) {
        uint8_t byte = bf->bits[i];
        while (byte) {
            count += (byte & 1);
            byte >>= 1;
        }
    }
    return count;
}

/**
 * Estimates mathematical false positive probability: (1 - e^(-kn/m))^k
 */
static inline double akp_bloom_est_false_positive(const akp_bloom_t* bf) {
    if (!bf || bf->bit_capacity == 0) return 0.0;
    double m = (double)bf->bit_capacity;
    double k = (double)bf->num_hashes;
    double n = (double)bf->items_added;
    double exponent = -k * n / m;
    double p = pow(1.0 - exp(exponent), k);
    if (p < 0.0) p = 0.0;
    if (p > 1.0) p = 1.0;
    return p;
}

/**
 * Renders Bloom Filter Status, Bit Array Sample, and Saturation Gauge
 */
static inline void akp_bloom_render(const akp_bloom_t* bf, const char* title) {
    if (!bf) return;
    akp_init_console();

    size_t set_bits = akp_bloom_bits_set(bf);
    double fill_pct = (double)set_bits / (double)bf->bit_capacity * 100.0;
    double fp_rate = akp_bloom_est_false_positive(bf) * 100.0;

    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║  🔮 PROBABILISTIC BLOOM FILTER TELEMETRY: %-35s ║\n" AKP_RESET, title ? title : "Set Membership");
    printf(AKP_BOLD AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    printf("  Bit Capacity: %llu bits (%llu bytes)  |  Hash Functions (k): %d\n",
           (unsigned long long)bf->bit_capacity, (unsigned long long)bf->byte_count, bf->num_hashes);
    printf("  Items Ingested: %llu  |  Bits Set: %llu / %llu (%.1f%%)\n",
           (unsigned long long)bf->items_added, (unsigned long long)set_bits, (unsigned long long)bf->bit_capacity, fill_pct);
    printf("  Theoretical False-Positive Rate: " AKP_BOLD AKP_NEON_GOLD "%.3f%%\n\n" AKP_RESET, fp_rate);

    /* Fill Bar Gauge */
    printf("  Saturation Gauge: [");
    int bar_width = 32;
    int filled = (int)((fill_pct / 100.0) * bar_width);
    for (int i = 0; i < bar_width; i++) {
        if (i < filled) printf(AKP_BOLD AKP_NEON_GREEN "█" AKP_RESET);
        else printf(AKP_DIM "░" AKP_RESET);
    }
    printf("] %.1f%%\n\n", fill_pct);

    /* First 64 bits visual dump */
    printf(AKP_BOLD AKP_NEON_PINK "  Bit Array Inspection (First 64 Bits):\n  " AKP_RESET);
    size_t preview_bits = bf->bit_capacity < 64 ? bf->bit_capacity : 64;
    for (size_t i = 0; i < preview_bits; i++) {
        bool bit = (bf->bits[i / 8] & (1 << (i % 8))) != 0;
        if (bit) {
            printf(AKP_BOLD AKP_NEON_CYAN "1" AKP_RESET);
        } else {
            printf(AKP_DIM "·" AKP_RESET);
        }
        if ((i + 1) % 8 == 0) printf(" ");
        if ((i + 1) % 32 == 0 && i + 1 < preview_bits) printf("\n  ");
    }
    printf("\n\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_BLOOM_FILTER_H */
