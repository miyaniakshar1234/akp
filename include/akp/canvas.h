/**
 * ============================================================================
 *  AKP ENGINE - 2D TERMINAL GEOMETRIC CANVAS (akp/canvas.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_CANVAS_H
#define AKP_CANVAS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

typedef struct {
    char ch;
    akp_rgb_t color;
    bool has_color;
} akp_pixel_t;

typedef struct {
    int width;
    int height;
    akp_pixel_t* buffer;
} akp_canvas_t;

static inline akp_canvas_t* akp_canvas_create(int width, int height) {
    if (width <= 0 || height <= 0) return NULL;
    akp_canvas_t* c = (akp_canvas_t*)malloc(sizeof(akp_canvas_t));
    if (!c) return NULL;
    c->width = width;
    c->height = height;
    c->buffer = (akp_pixel_t*)calloc(width * height, sizeof(akp_pixel_t));
    if (!c->buffer) { free(c); return NULL; }
    for (int i = 0; i < width * height; i++) {
        c->buffer[i].ch = ' ';
        c->buffer[i].has_color = false;
    }
    return c;
}

static inline void akp_canvas_clear(akp_canvas_t* c, char fill_char) {
    if (!c || !c->buffer) return;
    for (int i = 0; i < c->width * c->height; i++) {
        c->buffer[i].ch = fill_char;
        c->buffer[i].has_color = false;
    }
}

static inline void akp_canvas_draw_point(akp_canvas_t* c, int x, int y, char ch, akp_rgb_t color) {
    if (!c || x < 0 || x >= c->width || y < 0 || y >= c->height) return;
    int idx = y * c->width + x;
    c->buffer[idx].ch = ch;
    c->buffer[idx].color = color;
    c->buffer[idx].has_color = true;
}

/* Bresenham's Line Drawing Algorithm */
static inline void akp_canvas_draw_line(akp_canvas_t* c, int x0, int y0, int x1, int y1, char ch, akp_rgb_t color) {
    if (!c) return;
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        akp_canvas_draw_point(c, x0, y0, ch, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

static inline void akp_canvas_draw_rect(akp_canvas_t* c, int x, int y, int w, int h, char ch, akp_rgb_t color) {
    if (!c) return;
    akp_canvas_draw_line(c, x, y, x + w - 1, y, ch, color);
    akp_canvas_draw_line(c, x, y + h - 1, x + w - 1, y + h - 1, ch, color);
    akp_canvas_draw_line(c, x, y, x, y + h - 1, ch, color);
    akp_canvas_draw_line(c, x + w - 1, y, x + w - 1, y + h - 1, ch, color);
}

/* Midpoint Circle Drawing Algorithm */
static inline void akp_canvas_draw_circle(akp_canvas_t* c, int xc, int yc, int r, char ch, akp_rgb_t color) {
    if (!c || r <= 0) return;
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x) {
        akp_canvas_draw_point(c, xc + x, yc + y, ch, color);
        akp_canvas_draw_point(c, xc - x, yc + y, ch, color);
        akp_canvas_draw_point(c, xc + x, yc - y, ch, color);
        akp_canvas_draw_point(c, xc - x, yc - y, ch, color);
        akp_canvas_draw_point(c, xc + y, yc + x, ch, color);
        akp_canvas_draw_point(c, xc - y, yc + x, ch, color);
        akp_canvas_draw_point(c, xc + y, yc - x, ch, color);
        akp_canvas_draw_point(c, xc - y, yc - x, ch, color);
        x++;
        if (d > 0) { y--; d = d + 4 * (x - y) + 10; }
        else { d = d + 4 * x + 6; }
    }
}

static inline void akp_canvas_draw_text(akp_canvas_t* c, int x, int y, const char* text, akp_rgb_t color) {
    if (!c || !text || y < 0 || y >= c->height) return;
    int len = (int)strlen(text);
    for (int i = 0; i < len; i++) {
        if (x + i >= 0 && x + i < c->width) {
            akp_canvas_draw_point(c, x + i, y, text[i], color);
        }
    }
}

static inline void akp_canvas_render(akp_canvas_t* c, const char* title) {
    if (!c) return;
    akp_init_console();
    if (title) printf("\n" AKP_BOLD AKP_NEON_CYAN "🎨 [ Canvas: %s (%dx%d) ]" AKP_RESET "\n", title, c->width, c->height);

    /* Canvas border top */
    printf(AKP_DIM "┌");
    for (int x = 0; x < c->width; x++) printf("─");
    printf("┐\n" AKP_RESET);

    for (int y = 0; y < c->height; y++) {
        printf(AKP_DIM "│" AKP_RESET);
        for (int x = 0; x < c->width; x++) {
            akp_pixel_t* p = &c->buffer[y * c->width + x];
            if (p->has_color) {
                akp_set_fg_rgb(p->color.r, p->color.g, p->color.b);
                putchar(p->ch);
                printf(AKP_RESET);
            } else {
                putchar(p->ch);
            }
        }
        printf(AKP_DIM "│\n" AKP_RESET);
    }

    /* Canvas border bottom */
    printf(AKP_DIM "└");
    for (int x = 0; x < c->width; x++) printf("─");
    printf("┘\n\n" AKP_RESET);
}

static inline void akp_canvas_free(akp_canvas_t* c) {
    if (c) {
        if (c->buffer) free(c->buffer);
        free(c);
    }
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_CANVAS_H */
