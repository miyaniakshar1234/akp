/**
 * ============================================================================
 *  AKP ENGINE - STRING PATTERN MATCHING VISUALIZER (akp/pattern_match.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Visual in-terminal Naive & Knuth-Morris-Pratt (KMP) string matching
 * ============================================================================
 */

#ifndef AKP_PATTERN_MATCH_H
#define AKP_PATTERN_MATCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "badge.h"

/* Naive String Matching with Step-by-Step Window */
static inline int akp_search_naive_pattern(const char* text, const char* pattern) {
    if (!text || !pattern) return -1;
    akp_init_console();

    size_t n = strlen(text);
    size_t m = strlen(pattern);
    if (m == 0 || m > n) return -1;

    printf("\n" AKP_BOLD AKP_NEON_CYAN "🔤 NAIVE PATTERN SEARCH: \"%s\" in \"%s\"\n" AKP_RESET, pattern, text);
    printf(AKP_DIM "----------------------------------------------------------------------\n" AKP_RESET);

    int comparisons = 0;
    for (size_t i = 0; i <= n - m; i++) {
        size_t j;
        for (j = 0; j < m; j++) {
            comparisons++;
            if (text[i + j] != pattern[j]) break;
        }

        if (j == m) {
            printf(AKP_BOLD AKP_NEON_GREEN "✔ Match found at index %zu after %d comparisons! ✨\n\n" AKP_RESET, i, comparisons);
            return (int)i;
        }
    }

    printf(AKP_BOLD AKP_NEON_RED "✖ Pattern not found after %d comparisons.\n\n" AKP_RESET, comparisons);
    return -1;
}

/* KMP Prefix Function Table */
static inline void akp_kmp_compute_lps(const char* pattern, int* lps, size_t m) {
    size_t len = 0;
    lps[0] = 0;
    size_t i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = (int)len;
            i++;
        } else {
            if (len != 0) {
                len = (size_t)lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/* KMP Visual Search */
static inline int akp_search_kmp(const char* text, const char* pattern) {
    if (!text || !pattern) return -1;
    akp_init_console();

    size_t n = strlen(text);
    size_t m = strlen(pattern);
    if (m == 0 || m > n) return -1;

    int* lps = (int*)malloc(sizeof(int) * m);
    if (!lps) return -1;
    akp_kmp_compute_lps(pattern, lps, m);

    printf("\n" AKP_BOLD AKP_NEON_PINK "⚡ KMP ALGORITHM SEARCH: \"%s\" (Length: %zu)\n" AKP_RESET, pattern, m);
    printf("   Computed LPS Table: ");
    for (size_t k = 0; k < m; k++) {
        printf("[%c: %d] ", pattern[k], lps[k]);
    }
    printf("\n");

    size_t i = 0; /* text index */
    size_t j = 0; /* pattern index */
    int comparisons = 0;

    while (i < n) {
        comparisons++;
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            int match_idx = (int)(i - j);
            printf(AKP_BOLD AKP_NEON_GREEN "✨ KMP MATCH LOCATED at index %d in %d comparisons (Time: O(N))!\n\n" AKP_RESET,
                   match_idx, comparisons);
            free(lps);
            return match_idx;
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = (size_t)lps[j - 1];
            } else {
                i++;
            }
        }
    }

    printf(AKP_BOLD AKP_NEON_RED "✖ KMP search: Pattern not found in text.\n\n" AKP_RESET);
    free(lps);
    return -1;
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_PATTERN_MATCH_H */
