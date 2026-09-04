/**
 * ============================================================================
 *  AKP ENGINE - TERMINAL TABLE VISUALIZER (akp/table.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_TABLE_H
#define AKP_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"
#include <stdarg.h>

#define AKP_TABLE_MAX_COLS 16
#define AKP_TABLE_MAX_ROWS 128
#define AKP_TABLE_MAX_CELL 128

typedef struct {
    int cols;
    int rows;
    char headers[AKP_TABLE_MAX_COLS][AKP_TABLE_MAX_CELL];
    char cells[AKP_TABLE_MAX_ROWS][AKP_TABLE_MAX_COLS][AKP_TABLE_MAX_CELL];
    int col_widths[AKP_TABLE_MAX_COLS];
    const char* title;
} akp_table_t;

static inline akp_table_t* akp_table_create(int cols, const char* title) {
    if (cols <= 0 || cols > AKP_TABLE_MAX_COLS) cols = 4;
    akp_table_t* t = (akp_table_t*)calloc(1, sizeof(akp_table_t));
    if (!t) return NULL;
    t->cols = cols;
    t->rows = 0;
    t->title = title;
    for (int i = 0; i < cols; i++) t->col_widths[i] = 4;
    return t;
}

static inline void akp_table_set_headers(akp_table_t* t, ...) {
    if (!t) return;
    va_list args;
    va_start(args, t);
    for (int i = 0; i < t->cols; i++) {
        const char* h = va_arg(args, const char*);
        if (h) {
            strncpy(t->headers[i], h, AKP_TABLE_MAX_CELL - 1);
            int len = (int)strlen(h);
            if (len > t->col_widths[i]) t->col_widths[i] = len;
        }
    }
    va_end(args);
}

static inline void akp_table_add_row(akp_table_t* t, ...) {
    if (!t || t->rows >= AKP_TABLE_MAX_ROWS) return;
    va_list args;
    va_start(args, t);
    for (int i = 0; i < t->cols; i++) {
        const char* val = va_arg(args, const char*);
        if (val) {
            strncpy(t->cells[t->rows][i], val, AKP_TABLE_MAX_CELL - 1);
            int len = (int)strlen(val);
            if (len > t->col_widths[i]) t->col_widths[i] = len;
        } else {
            t->cells[t->rows][i][0] = '\0';
        }
    }
    va_end(args);
    t->rows++;
}

static inline void akp_table_print_line(akp_table_t* t, const char* left, const char* mid, const char* cross, const char* right) {
    printf(AKP_NEON_CYAN "%s", left);
    for (int c = 0; c < t->cols; c++) {
        int w = t->col_widths[c] + 2;
        for (int i = 0; i < w; i++) printf("%s", mid);
        if (c < t->cols - 1) printf("%s", cross);
    }
    printf("%s\n" AKP_RESET, right);
}

static inline void akp_table_render(akp_table_t* t) {
    if (!t) return;
    akp_init_console();
    
    if (t->title) {
        printf("\n" AKP_BOLD AKP_NEON_YELLOW "📋 [ %s ]" AKP_RESET "\n", t->title);
    } else {
        printf("\n");
    }

    /* Top border: ╭───┬───╮ */
    akp_table_print_line(t, "╭", "─", "┬", "╮");

    /* Header row: │ Col1 │ Col2 │ */
    printf(AKP_NEON_CYAN "│" AKP_RESET);
    for (int c = 0; c < t->cols; c++) {
        printf(AKP_BOLD AKP_NEON_PINK " %-*s " AKP_RESET AKP_NEON_CYAN "│" AKP_RESET, 
               t->col_widths[c], t->headers[c]);
    }
    printf("\n");

    /* Header separator: ├───┼───┤ */
    akp_table_print_line(t, "├", "─", "┼", "┤");

    /* Body rows */
    for (int r = 0; r < t->rows; r++) {
        printf(AKP_NEON_CYAN "│" AKP_RESET);
        for (int c = 0; c < t->cols; c++) {
            if (r % 2 == 0) {
                printf(AKP_BOLD AKP_FG_WHITE " %-*s " AKP_RESET AKP_NEON_CYAN "│" AKP_RESET, 
                       t->col_widths[c], t->cells[r][c]);
            } else {
                printf(AKP_DIM AKP_NEON_CYAN " %-*s " AKP_RESET AKP_NEON_CYAN "│" AKP_RESET, 
                       t->col_widths[c], t->cells[r][c]);
            }
        }
        printf("\n");
    }

    /* Bottom border: ╰───┴───╯ */
    akp_table_print_line(t, "╰", "─", "┴", "╯");
    printf("\n");
}

static inline void akp_table_free(akp_table_t* t) {
    if (t) free(t);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_TABLE_H */

/* Verified: 2026-09-04 23:29:06 */
