/**
 * ============================================================================
 *  AKP ENGINE - DSA & ALGORITHM VISUALIZER (akp/dsa.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_DSA_H
#define AKP_DSA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

static inline void akp_visualize_array(const int* arr, int n, int highlight_idx, const char* title) {
    if (!arr || n <= 0) return;
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_CYAN "\n📊 Visual Array: %s (N = %d)\n" AKP_RESET, title ? title : "Dataset", n);
    
    int max_val = 1;
    for (int i = 0; i < n; i++) {
        if (arr[i] > max_val) max_val = arr[i];
    }

    for (int i = 0; i < n; i++) {
        int bar_len = (arr[i] * 25) / max_val;
        if (bar_len < 1) bar_len = 1;

        if (i == highlight_idx) {
            printf(AKP_BOLD AKP_NEON_PINK " [%02d] %5d | " AKP_RESET, i, arr[i]);
            for (int b = 0; b < bar_len; b++) printf(AKP_BOLD AKP_NEON_PINK "█" AKP_RESET);
            printf(AKP_BOLD AKP_NEON_PINK " ◄ SELECTED\n" AKP_RESET);
        } else {
            printf(AKP_DIM " [%02d] %5d | " AKP_RESET, i, arr[i]);
            for (int b = 0; b < bar_len; b++) printf(AKP_NEON_CYAN "█" AKP_RESET);
            printf("\n");
        }
    }
    printf("\n");
}

static inline void akp_print_matrix(const int* mat, int rows, int cols, const char* title) {
    if (!mat || rows <= 0 || cols <= 0) return;
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_YELLOW "\n🔢 Matrix: %s [%dx%d]\n" AKP_RESET, title ? title : "Grid", rows, cols);

    for (int r = 0; r < rows; r++) {
        printf(AKP_NEON_CYAN " │ " AKP_RESET);
        for (int c = 0; c < cols; c++) {
            int val = mat[r * cols + c];
            if (val == 0) {
                printf(AKP_DIM "%4d " AKP_RESET, val);
            } else if (val > 0) {
                printf(AKP_NEON_GREEN "%4d " AKP_RESET, val);
            } else {
                printf(AKP_NEON_PINK "%4d " AKP_RESET, val);
            }
        }
        printf(AKP_NEON_CYAN "│\n" AKP_RESET);
    }
    printf("\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_DSA_H */
