/**
 * ============================================================================
 *  AKP ENGINE - COLOR & TRUECOLOR MODULE (akp/color.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_COLOR_H
#define AKP_COLOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define AKP_OS_WIN 1
#else
    #define AKP_OS_WIN 0
#endif

/* Text Styles */
#define AKP_RESET       "\x1b[0m"
#define AKP_BOLD        "\x1b[1m"
#define AKP_DIM         "\x1b[2m"
#define AKP_ITALIC      "\x1b[3m"
#define AKP_UNDERLINE   "\x1b[4m"
#define AKP_BLINK       "\x1b[5m"
#define AKP_INVERT      "\x1b[7m"
#define AKP_STRIKE      "\x1b[9m"

/* Standard ANSI Foreground */
#define AKP_FG_BLACK    "\x1b[30m"
#define AKP_FG_RED      "\x1b[31m"
#define AKP_FG_GREEN    "\x1b[32m"
#define AKP_FG_YELLOW   "\x1b[33m"
#define AKP_FG_BLUE     "\x1b[34m"
#define AKP_FG_MAGENTA  "\x1b[35m"
#define AKP_FG_CYAN     "\x1b[36m"
#define AKP_FG_WHITE    "\x1b[37m"

/* Standard ANSI Background */
#define AKP_BG_BLACK    "\x1b[40m"
#define AKP_BG_RED      "\x1b[41m"
#define AKP_BG_GREEN    "\x1b[42m"
#define AKP_BG_YELLOW   "\x1b[43m"
#define AKP_BG_BLUE     "\x1b[44m"
#define AKP_BG_MAGENTA  "\x1b[45m"
#define AKP_BG_CYAN     "\x1b[46m"
#define AKP_BG_WHITE    "\x1b[47m"

/* Cyberpunk Neon 24-Bit TrueColor Palette */
#define AKP_NEON_CYAN    "\x1b[38;2;0;255;234m"
#define AKP_NEON_PINK    "\x1b[38;2;255;0;127m"
#define AKP_NEON_PURPLE  "\x1b[38;2;179;0;255m"
#define AKP_NEON_GREEN   "\x1b[38;2;57;255;20m"
#define AKP_NEON_YELLOW  "\x1b[38;2;255;231;0m"
#define AKP_GOLD         "\x1b[38;2;255;184;0m"
#define AKP_FIRE_ORANGE  "\x1b[38;2;255;94;0m"
#define AKP_DEEP_BLUE    "\x1b[38;2;0;102;255m"
#define AKP_MINT         "\x1b[38;2;0;255;157m"
#define AKP_ELECTRIC_VIOLET "\x1b[38;2;143;0;255m"

/* Background Neons */
#define AKP_BG_NEON_CYAN   "\x1b[48;2;0;255;234m"
#define AKP_BG_NEON_PINK   "\x1b[48;2;255;0;127m"
#define AKP_BG_DARK_SLATE  "\x1b[48;2;24;24;37m"

/* RGB Color Struct */
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} akp_rgb_t;

static inline akp_rgb_t akp_rgb(uint8_t r, uint8_t g, uint8_t b) {
    akp_rgb_t c = { r, g, b };
    return c;
}

static inline akp_rgb_t akp_hex(uint32_t hex) {
    akp_rgb_t c;
    c.r = (uint8_t)((hex >> 16) & 0xFF);
    c.g = (uint8_t)((hex >> 8) & 0xFF);
    c.b = (uint8_t)(hex & 0xFF);
    return c;
}

static inline void akp_init_console(void) {
#if AKP_OS_WIN
    static bool initialized = false;
    if (!initialized) {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= 0x0004; /* ENABLE_VIRTUAL_TERMINAL_PROCESSING */
                SetConsoleMode(hOut, dwMode);
            }
        }
        SetConsoleOutputCP(CP_UTF8);
        initialized = true;
    }
#endif
}

static inline void akp_set_fg_rgb(uint8_t r, uint8_t g, uint8_t b) {
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

static inline void akp_set_bg_rgb(uint8_t r, uint8_t g, uint8_t b) {
    printf("\x1b[48;2;%d;%d;%dm", r, g, b);
}

static inline void akp_print_gradient(const char* text, akp_rgb_t start, akp_rgb_t end) {
    if (!text) return;
    size_t len = strlen(text);
    if (len == 0) return;
    for (size_t i = 0; i < len; i++) {
        float t = (len > 1) ? ((float)i / (float)(len - 1)) : 0.0f;
        uint8_t r = (uint8_t)(start.r + t * (end.r - start.r));
        uint8_t g = (uint8_t)(start.g + t * (end.g - start.g));
        uint8_t b = (uint8_t)(start.b + t * (end.b - start.b));
        akp_set_fg_rgb(r, g, b);
        putchar(text[i]);
    }
    printf(AKP_RESET);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_COLOR_H */

/* Verified: 2026-09-04 23:28:49 */
