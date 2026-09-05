/**
 * ============================================================================
 *  AKP ENGINE - REAL-TIME TERMINAL SORTING ANIMATOR (akp/sort_anim.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_SORT_ANIM_H
#define AKP_SORT_ANIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"
#include "sound.h"

typedef enum {
    AKP_ANIM_BUBBLE,
    AKP_ANIM_SELECTION,
    AKP_ANIM_INSERTION
} akp_sort_type_t;

static inline void akp_sort_render_frame(const int* arr, int n, int idx_a, int idx_b, int step, const char* name) {
    int max_val = 1;
    for (int i = 0; i < n; i++) if (arr[i] > max_val) max_val = arr[i];

    printf(AKP_BOLD AKP_NEON_YELLOW "⚡ %-16s | Step: %-4d (Comparing: [%02d] vs [%02d])\n" AKP_RESET, 
           name, step, idx_a, idx_b);

    for (int i = 0; i < n; i++) {
        int bar_len = (arr[i] * 24) / max_val;
        if (bar_len < 1) bar_len = 1;

        if (i == idx_a) {
            printf(AKP_BOLD AKP_NEON_PINK " [%02d] %4d | " AKP_RESET, i, arr[i]);
            for (int b = 0; b < bar_len; b++) printf(AKP_BOLD AKP_NEON_PINK "█" AKP_RESET);
            printf(AKP_BOLD AKP_NEON_PINK " ◄ A\n" AKP_RESET);
        } else if (i == idx_b) {
            printf(AKP_BOLD AKP_NEON_GREEN " [%02d] %4d | " AKP_RESET, i, arr[i]);
            for (int b = 0; b < bar_len; b++) printf(AKP_BOLD AKP_NEON_GREEN "█" AKP_RESET);
            printf(AKP_BOLD AKP_NEON_GREEN " ◄ B\n" AKP_RESET);
        } else {
            printf(AKP_DIM " [%02d] %4d | " AKP_RESET, i, arr[i]);
            for (int b = 0; b < bar_len; b++) printf(AKP_NEON_CYAN "█" AKP_RESET);
            printf("\n");
        }
    }
}

static inline void akp_animate_sort(int* arr, int n, akp_sort_type_t type, int delay_ms) {
    if (!arr || n <= 1) return;
    akp_init_console();
    if (delay_ms < 5) delay_ms = 25;

    const char* sort_name = (type == AKP_ANIM_BUBBLE) ? "Bubble Sort" :
                            (type == AKP_ANIM_SELECTION) ? "Selection Sort" : "Insertion Sort";

    printf("\n" AKP_BOLD AKP_NEON_CYAN "🎬 Starting Live Terminal Sort Animation: %s (N = %d)...\n\n" AKP_RESET, sort_name, n);
    int step = 0;
    int comparisons = 0, swaps = 0;

    if (type == AKP_ANIM_BUBBLE) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                comparisons++;
                step++;
                akp_sort_render_frame(arr, n, j, j + 1, step, sort_name);
#if AKP_OS_WIN
                Sleep(delay_ms);
#else
                usleep(delay_ms * 1000);
#endif
                if (arr[j] > arr[j + 1]) {
                    int tmp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tmp;
                    swaps++;
                }
                /* Move cursor up by n + 1 lines to redraw next frame */
                printf("\x1b[%dA", n + 1);
            }
        }
    } else if (type == AKP_ANIM_SELECTION) {
        for (int i = 0; i < n - 1; i++) {
            int min_idx = i;
            for (int j = i + 1; j < n; j++) {
                comparisons++;
                step++;
                akp_sort_render_frame(arr, n, min_idx, j, step, sort_name);
#if AKP_OS_WIN
                Sleep(delay_ms);
#else
                usleep(delay_ms * 1000);
#endif
                if (arr[j] < arr[min_idx]) min_idx = j;
                printf("\x1b[%dA", n + 1);
            }
            if (min_idx != i) {
                int tmp = arr[i];
                arr[i] = arr[min_idx];
                arr[min_idx] = tmp;
                swaps++;
            }
        }
    } else { /* INSERTION */
        for (int i = 1; i < n; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                comparisons++;
                step++;
                akp_sort_render_frame(arr, n, j, j + 1, step, sort_name);
#if AKP_OS_WIN
                Sleep(delay_ms);
#else
                usleep(delay_ms * 1000);
#endif
                arr[j + 1] = arr[j];
                j = j - 1;
                swaps++;
                printf("\x1b[%dA", n + 1);
            }
            arr[j + 1] = key;
        }
    }

    /* Final frame */
    akp_sort_render_frame(arr, n, -1, -1, step, sort_name);
    printf(AKP_BOLD AKP_NEON_GREEN "✨ SORT COMPLETED! Total Comparisons: %d | Swaps: %d\n\n" AKP_RESET, comparisons, swaps);
    akp_sound_coin();
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_SORT_ANIM_H */
