/**
 * ============================================================================
 *  AKP ENGINE - LINEAR ALGEBRA & MATRIX OPERATIONS (akp/matrix.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_MATRIX_H
#define AKP_MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

typedef struct {
    int rows;
    int cols;
    double* data;
} akp_mat_t;

static inline akp_mat_t* akp_mat_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    akp_mat_t* m = (akp_mat_t*)malloc(sizeof(akp_mat_t));
    if (!m) return NULL;
    m->rows = rows;
    m->cols = cols;
    m->data = (double*)calloc(rows * cols, sizeof(double));
    if (!m->data) { free(m); return NULL; }
    return m;
}

static inline void akp_mat_set(akp_mat_t* m, int r, int c, double val) {
    if (m && r >= 0 && r < m->rows && c >= 0 && c < m->cols) {
        m->data[r * m->cols + c] = val;
    }
}

static inline double akp_mat_get(const akp_mat_t* m, int r, int c) {
    if (m && r >= 0 && r < m->rows && c >= 0 && c < m->cols) {
        return m->data[r * m->cols + c];
    }
    return 0.0;
}

static inline akp_mat_t* akp_mat_multiply(const akp_mat_t* A, const akp_mat_t* B) {
    if (!A || !B || A->cols != B->rows) return NULL;
    akp_mat_t* C = akp_mat_create(A->rows, B->cols);
    if (!C) return NULL;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < A->cols; k++) {
                sum += akp_mat_get(A, i, k) * akp_mat_get(B, k, j);
            }
            akp_mat_set(C, i, j, sum);
        }
    }
    return C;
}

static inline akp_mat_t* akp_mat_transpose(const akp_mat_t* A) {
    if (!A) return NULL;
    akp_mat_t* T = akp_mat_create(A->cols, A->rows);
    if (!T) return NULL;

    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            akp_mat_set(T, j, i, akp_mat_get(A, i, j));
        }
    }
    return T;
}

static inline double akp_mat_det3x3(const akp_mat_t* m) {
    if (!m || m->rows != 3 || m->cols != 3) return 0.0;
    double a = akp_mat_get(m, 0, 0), b = akp_mat_get(m, 0, 1), c = akp_mat_get(m, 0, 2);
    double d = akp_mat_get(m, 1, 0), e = akp_mat_get(m, 1, 1), f = akp_mat_get(m, 1, 2);
    double g = akp_mat_get(m, 2, 0), h = akp_mat_get(m, 2, 1), k = akp_mat_get(m, 2, 2);
    return a*(e*k - f*h) - b*(d*k - f*g) + c*(d*h - e*g);
}

static inline void akp_mat_render(const akp_mat_t* m, const char* title) {
    if (!m) return;
    akp_init_console();
    if (title) printf("\n" AKP_BOLD AKP_NEON_YELLOW "🔢 [ Matrix: %s (%dx%d) ]" AKP_RESET "\n", title, m->rows, m->cols);

    for (int r = 0; r < m->rows; r++) {
        printf(AKP_NEON_CYAN " │ " AKP_RESET);
        for (int c = 0; c < m->cols; c++) {
            double val = akp_mat_get(m, r, c);
            if (fabs(val) < 0.00001) {
                printf(AKP_DIM " %7.2f " AKP_RESET, 0.0);
            } else if (val > 0) {
                printf(AKP_NEON_GREEN " %7.2f " AKP_RESET, val);
            } else {
                printf(AKP_NEON_PINK " %7.2f " AKP_RESET, val);
            }
        }
        printf(AKP_NEON_CYAN " │\n" AKP_RESET);
    }
    printf("\n");
}

static inline void akp_mat_free(akp_mat_t* m) {
    if (m) {
        if (m->data) free(m->data);
        free(m);
    }
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_MATRIX_H */
