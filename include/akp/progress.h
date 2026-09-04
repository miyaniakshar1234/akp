/**
 * ============================================================================
 *  AKP ENGINE - PROGRESS BAR & SPINNER MODULE (akp/progress.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_PROGRESS_H
#define AKP_PROGRESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

static inline void akp_progress(int current, int total, const char* prefix) {
    if (total <= 0) total = 1;
    float ratio = (float)current / (float)total;
    if (ratio > 1.0f) ratio = 1.0f;
    int percent = (int)(ratio * 100.0f);
    int bar_width = 30;
    int filled = (int)(ratio * bar_width);

    printf("\r" AKP_BOLD AKP_NEON_CYAN "%-18s " AKP_RESET "[", prefix ? prefix : "Processing");
    for (int i = 0; i < bar_width; i++) {
        if (i < filled) {
            float t = (float)i / (float)bar_width;
            int r = (int)(0   + t * 255);
            int g = (int)(255 - t * 50);
            int b = (int)(234 + t * 20);
            printf("\x1b[38;2;%d;%d;%dm█" AKP_RESET, r, g, b);
        } else {
            printf(AKP_DIM "░" AKP_RESET);
        }
    }
    printf(AKP_BOLD AKP_NEON_YELLOW " %3d%%" AKP_RESET "] " AKP_DIM "(%d/%d)" AKP_RESET, percent, current, total);
    fflush(stdout);
    if (current >= total) printf("\n");
}

static inline void akp_spinner(int step, const char* task_name) {
    const char* frames[] = { "⠋", "⠙", "⠹", "⠸", "⠼", "⠴", "⠦", "⠧", "⠇", "⠏" };
    int num_frames = 10;
    printf("\r" AKP_BOLD AKP_NEON_PINK "%s " AKP_NEON_CYAN "%s..." AKP_RESET "   ", 
           frames[step % num_frames], task_name ? task_name : "Executing");
    fflush(stdout);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_PROGRESS_H */
