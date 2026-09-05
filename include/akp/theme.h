/**
 * ============================================================================
 *  AKP ENGINE - TERMINAL COLOR THEMES (akp/theme.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Cyberpunk, Matrix, Synthwave, Dracula, and Monokai color presets
 * ============================================================================
 */

#ifndef AKP_THEME_H
#define AKP_THEME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "color.h"

typedef enum {
    AKP_THEME_CYBERPUNK = 0,
    AKP_THEME_MATRIX,
    AKP_THEME_SYNTHWAVE,
    AKP_THEME_DRACULA,
    AKP_THEME_MONOKAI
} akp_theme_id_t;

typedef struct {
    const char* name;
    akp_rgb_t primary;
    akp_rgb_t secondary;
    akp_rgb_t accent;
} akp_theme_t;

static inline akp_theme_t akp_theme_get(akp_theme_id_t id) {
    akp_theme_t t;
    switch (id) {
        case AKP_THEME_MATRIX:
            t.name = "Matrix Terminal";
            t.primary = akp_rgb(0, 255, 65);     /* Hacker Green */
            t.secondary = akp_rgb(0, 143, 17);   /* Dark Green */
            t.accent = akp_rgb(200, 255, 200);   /* Phosphor White */
            break;
        case AKP_THEME_SYNTHWAVE:
            t.name = "Synthwave 84";
            t.primary = akp_rgb(255, 0, 128);    /* Hot Magenta */
            t.secondary = akp_rgb(0, 240, 255);  /* Electric Cyan */
            t.accent = akp_rgb(255, 180, 0);     /* Sunset Gold */
            break;
        case AKP_THEME_DRACULA:
            t.name = "Dracula Pro";
            t.primary = akp_rgb(189, 147, 249);  /* Purple */
            t.secondary = akp_rgb(255, 121, 198);/* Pink */
            t.accent = akp_rgb(80, 250, 123);    /* Green */
            break;
        case AKP_THEME_MONOKAI:
            t.name = "Monokai Sublime";
            t.primary = akp_rgb(230, 219, 116);  /* Yellow */
            t.secondary = akp_rgb(253, 151, 31); /* Orange */
            t.accent = akp_rgb(102, 217, 239);   /* Cyan */
            break;
        case AKP_THEME_CYBERPUNK:
        default:
            t.name = "Cyberpunk 2077";
            t.primary = akp_rgb(0, 243, 255);    /* Neon Cyan */
            t.secondary = akp_rgb(255, 0, 85);   /* Neon Pink */
            t.accent = akp_rgb(255, 230, 0);     /* Neon Yellow */
            break;
    }
    return t;
}

static inline void akp_theme_preview(akp_theme_id_t id) {
    akp_init_console();
    akp_theme_t t = akp_theme_get(id);

    printf(AKP_BOLD "🎨 THEME PREVIEW: " AKP_RESET);
    akp_set_fg_rgb(t.primary.r, t.primary.g, t.primary.b);
    printf("[%s] ", t.name);
    akp_reset_color();

    printf("Primary: ");
    akp_set_fg_rgb(t.primary.r, t.primary.g, t.primary.b);
    printf("████ ");
    akp_reset_color();

    printf("Secondary: ");
    akp_set_fg_rgb(t.secondary.r, t.secondary.g, t.secondary.b);
    printf("████ ");
    akp_reset_color();

    printf("Accent: ");
    akp_set_fg_rgb(t.accent.r, t.accent.g, t.accent.b);
    printf("████\n");
    akp_reset_color();
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_THEME_H */
