/**
 * ============================================================================
 *  AKP ENGINE - TERMINAL GRAPH & SPARKLINE PLOTTER (akp/plot.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_PLOT_H
#define AKP_PLOT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"
#include <math.h>

/* Unicode sparkline block levels from lowest to highest */
static const char* AKP_SPARK_BLOCKS[] = { " ", "▂", "▃", "▄", "▅", "▆", "▇", "█" };

static inline void akp_sparkline(const double* values, int count, const char* label) {
    if (!values || count <= 0) return;
    akp_init_console();

    double min_val = values[0];
    double max_val = values[0];
    for (int i = 1; i < count; i++) {
        if (values[i] < min_val) min_val = values[i];
        if (values[i] > max_val) max_val = values[i];
    }
    double range = max_val - min_val;
    if (range < 0.00001) range = 1.0;

    printf(AKP_BOLD AKP_NEON_YELLOW "📈 %-20s " AKP_RESET "[ ", label ? label : "Sparkline");

    for (int i = 0; i < count; i++) {
        double norm = (values[i] - min_val) / range;
        int level = (int)(norm * 7.99);
        if (level < 0) level = 0;
        if (level > 7) level = 7;

        /* Dynamic color based on value intensity */
        if (level >= 6) printf(AKP_NEON_PINK "%s" AKP_RESET, AKP_SPARK_BLOCKS[level]);
        else if (level >= 3) printf(AKP_NEON_CYAN "%s" AKP_RESET, AKP_SPARK_BLOCKS[level]);
        else printf(AKP_NEON_GREEN "%s" AKP_RESET, AKP_SPARK_BLOCKS[level]);
    }

    printf(" ] " AKP_DIM "(min: %.2f, max: %.2f)" AKP_RESET "\n", min_val, max_val);
}

static inline void akp_plot_curve(double (*func)(double), double x_min, double x_max, int width, int height, const char* title) {
    if (!func || width <= 10 || height <= 5) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_CYAN "📐 [ Function Plot: %s ]" AKP_RESET "\n", title ? title : "f(x)");

    double* y_vals = (double*)malloc(width * sizeof(double));
    if (!y_vals) return;

    double y_min = 1e9, y_max = -1e9;
    for (int col = 0; col < width; col++) {
        double x = x_min + ((double)col / (width - 1)) * (x_max - x_min);
        y_vals[col] = func(x);
        if (y_vals[col] < y_min) y_min = y_vals[col];
        if (y_vals[col] > y_max) y_max = y_vals[col];
    }
    double y_range = y_max - y_min;
    if (y_range < 0.00001) y_range = 1.0;

    for (int row = height - 1; row >= 0; row--) {
        double cur_y = y_min + ((double)row / (height - 1)) * y_range;
        printf(AKP_DIM "%7.2f │ " AKP_RESET, cur_y);

        for (int col = 0; col < width; col++) {
            int target_row = (int)(((y_vals[col] - y_min) / y_range) * (height - 1) + 0.5);
            if (target_row == row) {
                printf(AKP_BOLD AKP_NEON_PINK "●" AKP_RESET);
            } else if (row == (int)((-y_min / y_range) * (height - 1) + 0.5)) {
                printf(AKP_DIM "─" AKP_RESET);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    /* X axis */
    printf("        └");
    for (int col = 0; col < width; col++) printf("─");
    printf("► (x)\n");
    printf("         %-8.2f%*s%8.2f\n\n", x_min, width - 16, "", x_max);

    free(y_vals);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_PLOT_H */
