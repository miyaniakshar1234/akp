/**
 * ============================================================================
 *  AKP ENGINE - SEARCH ALGORITHM VISUALIZER (akp/search_anim.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Step-by-step in-terminal visual Binary Search and Linear Search
 * ============================================================================
 */

#ifndef AKP_SEARCH_ANIM_H
#define AKP_SEARCH_ANIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "color.h"
#include "badge.h"

/* Visual Linear Search */
static inline int akp_search_linear(const int* arr, int n, int target) {
    if (!arr || n <= 0) return -1;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_CYAN "🔍 INITIATING LINEAR SEARCH FOR TARGET: [%d]\n" AKP_RESET, target);
    printf(AKP_DIM "--------------------------------------------------------\n" AKP_RESET);

    int comparisons = 0;
    for (int i = 0; i < n; i++) {
        comparisons++;
        int match = (arr[i] == target);

        printf("  Step %2d: [Index %2d] Value = %4d  ", comparisons, i, arr[i]);
        if (match) {
            printf(AKP_BOLD AKP_NEON_GREEN "== TARGET -> MATCH FOUND! ✨\n" AKP_RESET);
            printf(AKP_BOLD AKP_NEON_GREEN "✔ Target [%d] located at Index %d in %d comparisons (Time: O(N))\n\n" AKP_RESET,
                   target, i, comparisons);
            return i;
        } else {
            printf(AKP_DIM "!= TARGET -> Continue Scanning\n" AKP_RESET);
        }
    }

    printf(AKP_BOLD AKP_NEON_RED "✖ Target [%d] not found after %d comparisons.\n\n" AKP_RESET, target, comparisons);
    return -1;
}

/* Visual Binary Search */
static inline int akp_search_binary(const int* arr, int n, int target) {
    if (!arr || n <= 0) return -1;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_PINK "⚡ INITIATING VISUAL BINARY SEARCH FOR TARGET: [%d]\n" AKP_RESET, target);
    printf(AKP_DIM "--------------------------------------------------------------------------------\n" AKP_RESET);

    int low = 0;
    int high = n - 1;
    int step = 0;

    while (low <= high) {
        step++;
        int mid = low + (high - low) / 2;

        /* Visual partition window */
        printf(AKP_BOLD "  [Step %d] Low: %2d (val: %3d) | Mid: %2d (val: " AKP_NEON_GOLD "%3d" AKP_RESET AKP_BOLD ") | High: %2d (val: %3d)\n" AKP_RESET,
               step, low, arr[low], mid, arr[mid], high, arr[high]);

        /* Visual bar display */
        printf("   Window: ");
        for (int i = 0; i < n; i++) {
            if (i == mid) {
                printf(AKP_BOLD AKP_NEON_GOLD "[%3d]* " AKP_RESET, arr[i]);
            } else if (i >= low && i <= high) {
                printf(AKP_BOLD AKP_NEON_CYAN "[%3d]  " AKP_RESET, arr[i]);
            } else {
                printf(AKP_DIM "[ . ]  " AKP_RESET);
            }
        }
        printf("\n");

        if (arr[mid] == target) {
            printf(AKP_BOLD AKP_NEON_GREEN "   ↳ MATCH! Element arr[%d] == %d matches target!\n" AKP_RESET, mid, target);
            printf(AKP_BOLD AKP_NEON_GREEN "✨ TARGET FOUND at Index %d in only %d steps! (Complexity: O(log N))\n\n" AKP_RESET,
                   mid, step);
            return mid;
        } else if (arr[mid] < target) {
            printf(AKP_DIM "   ↳ arr[%d] (%d) < Target (%d) -> Discard Left, Search Right: [%d..%d]\n\n" AKP_RESET,
                   mid, arr[mid], target, mid + 1, high);
            low = mid + 1;
        } else {
            printf(AKP_DIM "   ↳ arr[%d] (%d) > Target (%d) -> Discard Right, Search Left: [%d..%d]\n\n" AKP_RESET,
                   mid, arr[mid], target, low, mid - 1);
            high = mid - 1;
        }
    }

    printf(AKP_BOLD AKP_NEON_RED "✖ Target [%d] not present in array after %d steps.\n\n" AKP_RESET, target, step);
    return -1;
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_SEARCH_ANIM_H */
