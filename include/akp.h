/**
 * ============================================================================
 *   █████╗ ██╗  ██╗██████╗      ███████╗███╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗
 *  ██╔══██╗██║ ██╔╝██╔══██╗     ██╔════╝████╗  ██║██╔════╝ ██║████╗  ██║██╔════╝
 *  ███████║█████═╝ ██████╔╝     █████╗  ██╔██╗ ██║██║  ███╗██║██╔██╗ ██║█████╗  
 *  ██╔══██║██╔═██╗ ██╔═══╝      ██╔══╝  ██║╚██╗██║██║   ██║██║██║╚██╗██║██╔══╝  
 *  ██║  ██║██║ ╚██╗██║          ███████╗██║ ╚████║╚██████╔╝██║██║ ╚████║███████╗
 *  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝          ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝
 * ============================================================================
 *  🚀 AKP CORE ENGINE v1.6.0 (Silent Audio Default)
 *  Author: Akshar Miyani
 *  Identity: AKP Studio / Advanced C & C++ Flashy Development Toolkit
 *  Zero-Dependency | Pure C99/C11 & C++11/14/17/20 Compatible | Cross-Platform
 * ============================================================================
 */

#ifndef AKP_H
#define AKP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <conio.h>
    #define AKP_PLATFORM_WINDOWS 1
    #define AKP_OS_WIN 1
#else
    #include <unistd.h>
    #include <termios.h>
    #include <sys/time.h>
    #define AKP_PLATFORM_WINDOWS 0
    #define AKP_OS_WIN 0
#endif

/* ============================================================================
 * [1] TERMINAL ANSI & 24-BIT TRUECOLOR PALETTE
 * ============================================================================ */

#define AKP_RESET       "\x1b[0m"
#define AKP_BOLD        "\x1b[1m"
#define AKP_DIM         "\x1b[2m"
#define AKP_ITALIC      "\x1b[3m"
#define AKP_UNDERLINE   "\x1b[4m"
#define AKP_BLINK       "\x1b[5m"
#define AKP_INVERT      "\x1b[7m"

#define AKP_FG_BLACK    "\x1b[30m"
#define AKP_FG_RED      "\x1b[31m"
#define AKP_FG_GREEN    "\x1b[32m"
#define AKP_FG_YELLOW   "\x1b[33m"
#define AKP_FG_BLUE     "\x1b[34m"
#define AKP_FG_MAGENTA  "\x1b[35m"
#define AKP_FG_CYAN     "\x1b[36m"
#define AKP_FG_WHITE    "\x1b[37m"

#define AKP_BG_BLACK    "\x1b[40m"
#define AKP_BG_RED      "\x1b[41m"
#define AKP_BG_GREEN    "\x1b[42m"
#define AKP_BG_YELLOW   "\x1b[43m"
#define AKP_BG_BLUE     "\x1b[44m"
#define AKP_BG_MAGENTA  "\x1b[45m"
#define AKP_BG_CYAN     "\x1b[46m"
#define AKP_BG_WHITE    "\x1b[47m"

#define AKP_NEON_CYAN    "\x1b[38;2;0;255;234m"
#define AKP_NEON_PINK    "\x1b[38;2;255;0;127m"
#define AKP_NEON_PURPLE  "\x1b[38;2;179;0;255m"
#define AKP_NEON_GREEN   "\x1b[38;2;57;255;20m"
#define AKP_NEON_YELLOW  "\x1b[38;2;255;231;0m"
#define AKP_GOLD         "\x1b[38;2;255;184;0m"
#define AKP_NEON_GOLD    AKP_GOLD
#define AKP_NEON_RED     "\x1b[38;2;255;50;50m"
#define AKP_FIRE_ORANGE  "\x1b[38;2;255;94;0m"
#define AKP_DEEP_BLUE    "\x1b[38;2;0;102;255m"
#define AKP_NEON_BLUE    AKP_DEEP_BLUE

static inline void akp_reset_color(void) {
    printf(AKP_RESET);
}

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
#if AKP_PLATFORM_WINDOWS
    static bool initialized = false;
    if (!initialized) {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= 0x0004;
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

/* ============================================================================
 * [2] AUTHOR IDENTITY SPLASH BANNER
 * ============================================================================ */

static inline void akp_banner(void) {
    akp_init_console();
    printf("\n");
    printf(AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_NEON_CYAN "║" AKP_NEON_PURPLE "   █████╗ ██╗  ██╗██████╗     ███████╗███╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗ " AKP_NEON_CYAN "║\n" AKP_RESET);
    printf(AKP_NEON_CYAN "║" AKP_NEON_PURPLE "  ██╔══██╗██║ ██╔╝██╔══██╗    ██╔════╝████╗  ██║██╔════╝ ██║████╗  ██║██╔════╝ " AKP_NEON_CYAN "║\n" AKP_RESET);
    printf(AKP_NEON_CYAN "║" AKP_NEON_PINK   "  ███████║█████═╝ ██████╔╝    █████╗  ██╔██╗ ██║██║  ███╗██║██╔██╗ ██║█████╗   " AKP_NEON_CYAN "║\n" AKP_RESET);
    printf(AKP_NEON_CYAN "║" AKP_NEON_PINK   "  ██╔══██║██╔═██╗ ██╔═══╝     ██╔══╝  ██║╚██╗██║██║   ██║██║██║╚██╗██║██╔══╝   " AKP_NEON_CYAN "║\n" AKP_RESET);
    printf(AKP_NEON_CYAN "║" AKP_GOLD        "  ██║  ██║██║ ╚██╗██║         ███████╗██║ ╚████║╚██████╔╝██║██║ ╚████║███████╗ " AKP_NEON_CYAN "║\n" AKP_RESET);
    printf(AKP_NEON_CYAN "║" AKP_GOLD        "  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝         ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝ " AKP_NEON_CYAN "║\n" AKP_RESET);
    printf(AKP_NEON_CYAN "╠═══════════════════════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf(AKP_NEON_CYAN "║" AKP_BOLD AKP_NEON_YELLOW "        🚀 AKP CORE ENGINE v1.5.0  |  ENGINEERED BY: AKSHAR MIYANI              " AKP_NEON_CYAN "║\n" AKP_RESET);
    printf(AKP_NEON_CYAN "║" AKP_DIM AKP_NEON_CYAN       "        ⚡ Ultra-Flashy Terminal Output & High-Performance C/C++ Toolkit        " AKP_NEON_CYAN "║\n" AKP_RESET);
    printf(AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);
    printf("\n");
}

static inline void akp_stamp(const char* assignment_name) {
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_CYAN "┌────────────────────────────────────────────────────────────────────────┐\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "│ " AKP_NEON_PINK "⚡ AKP LAB SUITE " AKP_RESET AKP_DIM ":: " AKP_BOLD AKP_NEON_YELLOW "%-30s" AKP_RESET AKP_NEON_CYAN "        │\n" AKP_RESET, assignment_name ? assignment_name : "Lab Execution");
    printf(AKP_BOLD AKP_NEON_CYAN "│ " AKP_DIM "Developed & Engineered by: " AKP_BOLD AKP_NEON_GREEN "Akshar Miyani" AKP_RESET AKP_DIM " (MCA)" AKP_RESET AKP_NEON_CYAN "                     │\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "└────────────────────────────────────────────────────────────────────────┘\n" AKP_RESET);
}

/* ============================================================================
 * [3] LOGGING BADGES & STATUS OUTPUTS
 * ============================================================================ */

static inline void akp_timestamp(char* buffer, size_t max_len) {
    time_t rawtime; struct tm* timeinfo;
    time(&rawtime); timeinfo = localtime(&rawtime);
    strftime(buffer, max_len, "%H:%M:%S", timeinfo);
}

static inline void akp_log_success(const char* fmt, ...) {
    char t[16]; akp_timestamp(t, sizeof(t));
    printf(AKP_DIM "[%s] " AKP_RESET AKP_BOLD AKP_NEON_GREEN "[ ✔ SUCCESS ] " AKP_RESET, t);
    va_list args; va_start(args, fmt); vprintf(fmt, args); va_end(args);
    printf("\n");
}

static inline void akp_log_info(const char* fmt, ...) {
    char t[16]; akp_timestamp(t, sizeof(t));
    printf(AKP_DIM "[%s] " AKP_RESET AKP_BOLD AKP_NEON_CYAN "[ ℹ INFO    ] " AKP_RESET, t);
    va_list args; va_start(args, fmt); vprintf(fmt, args); va_end(args);
    printf("\n");
}

static inline void akp_log_warn(const char* fmt, ...) {
    char t[16]; akp_timestamp(t, sizeof(t));
    printf(AKP_DIM "[%s] " AKP_RESET AKP_BOLD AKP_GOLD "[ ⚠ WARNING ] " AKP_RESET, t);
    va_list args; va_start(args, fmt); vprintf(fmt, args); va_end(args);
    printf("\n");
}

static inline void akp_log_error(const char* fmt, ...) {
    char t[16]; akp_timestamp(t, sizeof(t));
    printf(AKP_DIM "[%s] " AKP_RESET AKP_BOLD AKP_FG_RED "[ ✖ ERROR   ] " AKP_RESET, t);
    va_list args; va_start(args, fmt); vprintf(fmt, args); va_end(args);
    printf("\n");
}

static inline void akp_log_akp(const char* tag, const char* fmt, ...) {
    char t[16]; akp_timestamp(t, sizeof(t));
    printf(AKP_DIM "[%s] " AKP_RESET AKP_BOLD AKP_NEON_PURPLE "[ ⚡ %-7s ] " AKP_RESET, t, tag ? tag : "AKP");
    va_list args; va_start(args, fmt); vprintf(fmt, args); va_end(args);
    printf("\n");
}

/* ============================================================================
 * [4] GRADIENT PROGRESS BAR & SPINNERS
 * ============================================================================ */

static inline void akp_progress(int current, int total, const char* prefix) {
    if (total <= 0) total = 1;
    float ratio = (float)current / (float)total;
    if (ratio > 1.0f) ratio = 1.0f;
    int percent = (int)(ratio * 100);
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

/* ============================================================================
 * [5] AUTO-SIZING UNICODE TABLES
 * ============================================================================ */

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
    t->cols = cols; t->rows = 0; t->title = title;
    for (int i = 0; i < cols; i++) t->col_widths[i] = 4;
    return t;
}

static inline void akp_table_set_headers(akp_table_t* t, ...) {
    if (!t) return;
    va_list args; va_start(args, t);
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
    va_list args; va_start(args, t);
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
    if (t->title) printf("\n" AKP_BOLD AKP_NEON_YELLOW "📋 [ %s ]" AKP_RESET "\n", t->title);
    else printf("\n");

    akp_table_print_line(t, "╭", "─", "┬", "╮");
    printf(AKP_NEON_CYAN "│" AKP_RESET);
    for (int c = 0; c < t->cols; c++) {
        printf(AKP_BOLD AKP_NEON_PINK " %-*s " AKP_RESET AKP_NEON_CYAN "│" AKP_RESET, 
               t->col_widths[c], t->headers[c]);
    }
    printf("\n");
    akp_table_print_line(t, "├", "─", "┼", "┤");

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
    akp_table_print_line(t, "╰", "─", "┴", "╯");
    printf("\n");
}

static inline void akp_table_free(akp_table_t* t) {
    if (t) free(t);
}

/* ============================================================================
 * [6] MEMORY HEX-DUMP INSPECTOR & HEAP TRACKER
 * ============================================================================ */

static inline void akp_hexdump(const void* ptr, size_t size, const char* label) {
    const uint8_t* byte_ptr = (const uint8_t*)ptr;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_YELLOW "─── [ HEX-DUMP: %s (Address: %p, Size: %zu bytes) ] ───" AKP_RESET "\n", 
           label ? label : "Memory Block", ptr, size);
    printf(AKP_DIM " Offset     00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F  | ASCII          |\n" AKP_RESET);
    printf(AKP_DIM " ─────────  ───────────────────────────────────────────────  | ────────────── |\n" AKP_RESET);

    for (size_t i = 0; i < size; i += 16) {
        printf(AKP_NEON_CYAN " %08zx  " AKP_RESET, i);
        for (size_t j = 0; j < 16; j++) {
            if (i + j < size) {
                uint8_t b = byte_ptr[i + j];
                if (b == 0x00) printf(AKP_DIM "%02x " AKP_RESET, b);
                else if (b >= 32 && b <= 126) printf(AKP_NEON_GREEN "%02x " AKP_RESET, b);
                else printf(AKP_NEON_PINK "%02x " AKP_RESET, b);
            } else printf("   ");
            if (j == 7) printf(" ");
        }
        printf(" | ");
        for (size_t j = 0; j < 16; j++) {
            if (i + j < size) {
                uint8_t b = byte_ptr[i + j];
                if (b >= 32 && b <= 126) printf(AKP_BOLD AKP_FG_WHITE "%c" AKP_RESET, b);
                else printf(AKP_DIM "." AKP_RESET);
            } else printf(" ");
        }
        printf(" |\n");
    }
    printf(AKP_DIM " ─────────  ───────────────────────────────────────────────  | ────────────── |\n\n" AKP_RESET);
}

static size_t g_akp_allocated_bytes = 0;
static size_t g_akp_peak_bytes = 0;
static size_t g_akp_alloc_count = 0;
static size_t g_akp_free_count = 0;

static inline void* akp_malloc_tracked(size_t sz, const char* file, int line) {
    (void)file; (void)line;
    size_t total_sz = sz + sizeof(size_t);
    size_t* p = (size_t*)malloc(total_sz);
    if (!p) return NULL;
    *p = sz;
    g_akp_allocated_bytes += sz;
    if (g_akp_allocated_bytes > g_akp_peak_bytes) g_akp_peak_bytes = g_akp_allocated_bytes;
    g_akp_alloc_count++;
    return (void*)(p + 1);
}

static inline void akp_free_tracked(void* ptr) {
    if (!ptr) return;
    size_t* p = ((size_t*)ptr) - 1;
    size_t sz = *p;
    g_akp_allocated_bytes -= sz;
    g_akp_free_count++;
    free(p);
}

#define AKP_MALLOC(sz) akp_malloc_tracked((sz), __FILE__, __LINE__)
#define AKP_FREE(p)    akp_free_tracked(p)

static inline void akp_mem_report(void) {
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_PURPLE "╔═══════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_PURPLE "║               🔍 AKP HEAP ALLOCATION AUDIT                    ║\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_PURPLE "╠═══════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║  Total Allocations:   " AKP_BOLD AKP_NEON_CYAN "%-10zu" AKP_RESET "                              ║\n", g_akp_alloc_count);
    printf("║  Total Deallocations: " AKP_BOLD AKP_NEON_CYAN "%-10zu" AKP_RESET "                              ║\n", g_akp_free_count);
    printf("║  Peak Memory Used:    " AKP_BOLD AKP_GOLD "%-10zu bytes" AKP_RESET "                        ║\n", g_akp_peak_bytes);
    if (g_akp_allocated_bytes > 0) {
        printf("║  Status:              " AKP_BOLD AKP_FG_RED "⚠ MEMORY LEAK (%zu bytes active)" AKP_RESET "      ║\n", g_akp_allocated_bytes);
    } else {
        printf("║  Status:              " AKP_BOLD AKP_NEON_GREEN "✔ ZERO LEAKS (Clean Memory)" AKP_RESET "               ║\n");
    }
    printf(AKP_BOLD AKP_NEON_PURPLE "╚═══════════════════════════════════════════════════════════════╝\n\n" AKP_RESET);
}

/* ============================================================================
 * [7] HIGH-PRECISION MICRO-BENCHMARK TIMER
 * ============================================================================ */

typedef struct {
#if AKP_PLATFORM_WINDOWS
    LARGE_INTEGER start_time;
    LARGE_INTEGER frequency;
#else
    struct timespec start_time;
#endif
    const char* section_name;
} akp_timer_t;

static inline akp_timer_t akp_timer_start(const char* name) {
    akp_timer_t t; t.section_name = name ? name : "Operation";
#if AKP_PLATFORM_WINDOWS
    QueryPerformanceFrequency(&t.frequency);
    QueryPerformanceCounter(&t.start_time);
#else
    clock_gettime(CLOCK_MONOTONIC, &t.start_time);
#endif
    return t;
}

static inline double akp_timer_stop_ms(akp_timer_t* t) {
#if AKP_PLATFORM_WINDOWS
    LARGE_INTEGER end_time;
    QueryPerformanceCounter(&end_time);
    return (double)(end_time.QuadPart - t->start_time.QuadPart) * 1000.0 / (double)t->frequency.QuadPart;
#else
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    return (end_time.tv_sec - t->start_time.tv_sec) * 1000.0 + 
           (end_time.tv_nsec - t->start_time.tv_nsec) / 1000000.0;
#endif
}

#define AKP_BENCHMARK(name) \
    for (akp_timer_t _akp_t = akp_timer_start(name), *_akp_p = &_akp_t; \
         _akp_p; \
         akp_log_info("Benchmark [" AKP_BOLD AKP_NEON_YELLOW "%s" AKP_RESET "] elapsed: " AKP_BOLD AKP_NEON_GREEN "%.4f ms" AKP_RESET, \
                      _akp_t.section_name, akp_timer_stop_ms(&_akp_t)), _akp_p = NULL)

/* ============================================================================
 * [8] AUDIO SOUND EFFECTS & MELODY
 * ============================================================================ */

#define AKP_NOTE_C4  262
#define AKP_NOTE_CS4 277
#define AKP_NOTE_D4  294
#define AKP_NOTE_DS4 311
#define AKP_NOTE_E4  330
#define AKP_NOTE_F4  349
#define AKP_NOTE_FS4 370
#define AKP_NOTE_G4  392
#define AKP_NOTE_GS4 415
#define AKP_NOTE_A4  440
#define AKP_NOTE_AS4 466
#define AKP_NOTE_B4  494
#define AKP_NOTE_C5  523
#define AKP_NOTE_D5  587
#define AKP_NOTE_E5  659
#define AKP_NOTE_F5  698
#define AKP_NOTE_G5  784
#define AKP_NOTE_A5  880
#define AKP_NOTE_B5  988
#define AKP_NOTE_C6  1046

/* Silent Audio Engine: 0dB by default to eliminate lab/classroom disruption.
   Define AKP_ENABLE_AUDIO_HARDWARE only if motherboard speaker beeps are explicitly requested. */
#ifdef AKP_ENABLE_AUDIO_HARDWARE
  #define AKP_SOUND_ENABLED 1
#else
  #define AKP_SOUND_ENABLED 0
#endif

static inline void akp_beep(int freq_hz, int duration_ms) {
#if AKP_SOUND_ENABLED
  #if AKP_PLATFORM_WINDOWS
    if (freq_hz > 0) Beep(freq_hz, duration_ms);
  #else
    printf("\a"); fflush(stdout);
  #endif
#else
    (void)freq_hz; (void)duration_ms; /* Silent mode */
#endif
}

static inline void akp_sound_coin(void) {
#if AKP_SOUND_ENABLED
#if AKP_PLATFORM_WINDOWS
    Beep(988, 100); Beep(1319, 250);
#else
    printf("\a"); fflush(stdout);
#endif
#endif
}

static inline void akp_sound_success(void) {
#if AKP_SOUND_ENABLED
#if AKP_PLATFORM_WINDOWS
    Beep(523, 100); Beep(659, 100); Beep(784, 150); Beep(1046, 250);
#else
    printf("\a"); fflush(stdout);
#endif
#endif
}

static inline void akp_sound_alert(void) {
#if AKP_SOUND_ENABLED
#if AKP_PLATFORM_WINDOWS
    Beep(440, 200); Beep(330, 250);
#else
    printf("\a"); fflush(stdout);
#endif
#endif
}

static inline void akp_melody_tetris(void) {
#if AKP_SOUND_ENABLED
    int notes[] = { AKP_NOTE_E5, AKP_NOTE_B4, AKP_NOTE_C5, AKP_NOTE_D5, AKP_NOTE_C5, AKP_NOTE_B4, AKP_NOTE_A4, AKP_NOTE_A4, AKP_NOTE_C5, AKP_NOTE_E5 };
    int durs[]  = { 250, 125, 125, 250, 125, 125, 250, 125, 125, 250 };
#if AKP_OS_WIN
    for (size_t i = 0; i < sizeof(notes)/sizeof(notes[0]); i++) Beep(notes[i], durs[i]);
#else
    printf("\a"); fflush(stdout);
#endif
#endif
}

/* ============================================================================
 * [9] DSA ARRAY & MATRIX VISUALIZERS
 * ============================================================================ */

static inline void akp_visualize_array(const int* arr, int n, int highlight_idx, const char* title) {
    if (!arr || n <= 0) return;
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_CYAN "\n📊 Visual Array: %s (N = %d)\n" AKP_RESET, title ? title : "Dataset", n);
    int max_val = 1;
    for (int i = 0; i < n; i++) if (arr[i] > max_val) max_val = arr[i];

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
            if (val == 0) printf(AKP_DIM "%4d " AKP_RESET, val);
            else if (val > 0) printf(AKP_NEON_GREEN "%4d " AKP_RESET, val);
            else printf(AKP_NEON_PINK "%4d " AKP_RESET, val);
        }
        printf(AKP_NEON_CYAN "│\n" AKP_RESET);
    }
    printf("\n");
}

/* ============================================================================
 * [9B] REAL-TIME TERMINAL SORTING ANIMATOR
 * ============================================================================ */

typedef enum {
    AKP_ANIM_BUBBLE,
    AKP_ANIM_SELECTION,
    AKP_ANIM_INSERTION
} akp_sort_type_t;

static inline void akp_sort_render_frame(const int* arr, int n, int idx_a, int idx_b, int step, const char* name) {
    int max_val = 1;
    for (int i = 0; i < n; i++) if (arr[i] > max_val) max_val = arr[i];
    printf(AKP_BOLD AKP_NEON_YELLOW "⚡ %-16s | Step: %-4d (Comparing: [%02d] vs [%02d])\n" AKP_RESET, name, step, idx_a, idx_b);
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
    int step = 0, comparisons = 0, swaps = 0;

    if (type == AKP_ANIM_BUBBLE) {
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                comparisons++; step++;
                akp_sort_render_frame(arr, n, j, j + 1, step, sort_name);
#if AKP_OS_WIN
                Sleep(delay_ms);
#else
                usleep(delay_ms * 1000);
#endif
                if (arr[j] > arr[j + 1]) {
                    int tmp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = tmp; swaps++;
                }
                printf("\x1b[%dA", n + 1);
            }
        }
    }
    akp_sort_render_frame(arr, n, -1, -1, step, sort_name);
    printf(AKP_BOLD AKP_NEON_GREEN "✨ SORT COMPLETED! Total Comparisons: %d | Swaps: %d\n\n" AKP_RESET, comparisons, swaps);
    akp_sound_coin();
}

/* ============================================================================
 * [10] TERMINAL GRAPH & SPARKLINE PLOTTER
 * ============================================================================ */

static const char* AKP_SPARK_BLOCKS[] = { " ", "▂", "▃", "▄", "▅", "▆", "▇", "█" };

static inline void akp_sparkline(const double* values, int count, const char* label) {
    if (!values || count <= 0) return;
    akp_init_console();
    double min_val = values[0], max_val = values[0];
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
            if (target_row == row) printf(AKP_BOLD AKP_NEON_PINK "●" AKP_RESET);
            else if (row == (int)((-y_min / y_range) * (height - 1) + 0.5)) printf(AKP_DIM "─" AKP_RESET);
            else printf(" ");
        }
        printf("\n");
    }
    printf("        └");
    for (int col = 0; col < width; col++) printf("─");
    printf("► (x)\n");
    printf("         %-8.2f%*s%8.2f\n\n", x_min, width - 16, "", x_max);
    free(y_vals);
}

/* ============================================================================
 * [11] BINARY TREE HIERARCHY VISUALIZER
 * ============================================================================ */

typedef struct akp_tree_node {
    int value;
    const char* label;
    struct akp_tree_node* left;
    struct akp_tree_node* right;
} akp_tree_node_t;

static inline akp_tree_node_t* akp_tree_create_node(int val, const char* label) {
    akp_tree_node_t* n = (akp_tree_node_t*)malloc(sizeof(akp_tree_node_t));
    if (!n) return NULL;
    n->value = val; n->label = label; n->left = NULL; n->right = NULL;
    return n;
}

static inline void akp_tree_print_internal(const akp_tree_node_t* node, const char* prefix, bool is_left, bool is_root) {
    if (!node) return;
    char right_prefix[256];
    snprintf(right_prefix, sizeof(right_prefix), "%s%s", prefix, is_left ? "│   " : "    ");
    akp_tree_print_internal(node->right, right_prefix, false, false);
    printf("%s", prefix);
    if (!is_root) printf(AKP_NEON_CYAN "%s" AKP_RESET, is_left ? "└── " : "┌── ");
    if (node->label) printf(AKP_BOLD AKP_NEON_YELLOW "[%d: %s]" AKP_RESET "\n", node->value, node->label);
    else printf(AKP_BOLD AKP_NEON_GREEN "[%d]" AKP_RESET "\n", node->value);
    char left_prefix[256];
    snprintf(left_prefix, sizeof(left_prefix), "%s%s", prefix, is_left ? "    " : "│   ");
    akp_tree_print_internal(node->left, left_prefix, true, false);
}

static inline void akp_tree_print(const akp_tree_node_t* root, const char* title) {
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_PURPLE "🌳 [ Binary Tree Hierarchy: %s ]" AKP_RESET "\n\n", title ? title : "Root");
    if (!root) { printf(AKP_DIM "    (Empty Tree)\n" AKP_RESET); return; }
    akp_tree_print_internal(root, "    ", false, true);
    printf("\n");
}

/* ============================================================================
 * [12] INTERACTIVE PROMPTS & SELECTORS
 * ============================================================================ */

static inline bool akp_prompt_confirm(const char* question) {
    akp_init_console();
    printf(AKP_BOLD AKP_GOLD "❓ %s [y/N]: " AKP_RESET, question ? question : "Continue?");
    fflush(stdout);
#if AKP_PLATFORM_WINDOWS
    int ch = _getch(); printf("%c\n", ch); return (ch == 'y' || ch == 'Y');
#else
    char buf[16]; if (fgets(buf, sizeof(buf), stdin)) return (buf[0] == 'y' || buf[0] == 'Y'); return false;
#endif
}

static inline void akp_prompt_password(const char* prompt, char* buffer, size_t max_len) {
    if (!buffer || max_len == 0) return;
    akp_init_console();
    printf(AKP_BOLD AKP_NEON_CYAN "🔑 %s " AKP_RESET, prompt ? prompt : "Enter Secret:");
    fflush(stdout);
    size_t idx = 0;
#if AKP_PLATFORM_WINDOWS
    while (idx < max_len - 1) {
        int ch = _getch();
        if (ch == '\r' || ch == '\n') break;
        if (ch == '\b') { if (idx > 0) { idx--; printf("\b \b"); fflush(stdout); } }
        else if (ch >= 32 && ch <= 126) { buffer[idx++] = (char)ch; printf(AKP_NEON_PINK "•" AKP_RESET); fflush(stdout); }
    }
    buffer[idx] = '\0'; printf("\n");
#else
    struct termios oldt, newt; tcgetattr(STDIN_FILENO, &oldt); newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (idx < max_len - 1) {
        int ch = getchar();
        if (ch == '\r' || ch == '\n') break;
        if (ch == 127 || ch == '\b') { if (idx > 0) { idx--; printf("\b \b"); fflush(stdout); } }
        else if (ch >= 32 && ch <= 126) { buffer[idx++] = (char)ch; printf(AKP_NEON_PINK "•" AKP_RESET); fflush(stdout); }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); buffer[idx] = '\0'; printf("\n");
#endif
}

static inline int akp_prompt_select(const char* title, const char* options[], int count) {
    if (!options || count <= 0) return -1;
    akp_init_console();
    int selected = 0; bool active = true;
    while (active) {
        printf("\r" AKP_BOLD AKP_NEON_CYAN "🎯 %s (Use ↑/↓ or 1-%d, Enter to pick):" AKP_RESET "\n", title ? title : "Select Option", count);
        for (int i = 0; i < count; i++) {
            if (i == selected) printf(AKP_BOLD AKP_NEON_PINK "  ► [%d] %-30s ◄" AKP_RESET "\n", i + 1, options[i]);
            else printf(AKP_DIM "    [%d] %-30s  " AKP_RESET "\n", i + 1, options[i]);
        }
#if AKP_PLATFORM_WINDOWS
        int ch = _getch();
        if (ch == 224 || ch == 0) {
            int code = _getch();
            if (code == 72) selected = (selected - 1 + count) % count;
            else if (code == 80) selected = (selected + 1) % count;
        } else if (ch == '\r' || ch == '\n') active = false;
        else if (ch >= '1' && ch < '1' + count) { selected = ch - '1'; active = false; }
#else
        struct termios oldt, newt; tcgetattr(STDIN_FILENO, &oldt); newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        int ch = getchar();
        if (ch == '\033') { getchar(); int arrow = getchar(); if (arrow == 'A') selected = (selected - 1 + count) % count; if (arrow == 'B') selected = (selected + 1) % count; }
        else if (ch == '\n' || ch == '\r') active = false;
        else if (ch >= '1' && ch < '1' + count) { selected = ch - '1'; active = false; }
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
        if (active) printf("\x1b[%dA", count + 1);
    }
    printf(AKP_BOLD AKP_NEON_GREEN "✔ Selected: %s" AKP_RESET "\n\n", options[selected]);
    return selected;
}

/* ============================================================================
 * [13] MICRO UNIT-TESTING SUITE
 * ============================================================================ */

typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
    const char* suite_name;
    akp_timer_t timer;
} akp_test_suite_t;

static inline akp_test_suite_t akp_test_suite_begin(const char* name) {
    akp_init_console();
    akp_test_suite_t s; s.total_tests = 0; s.passed_tests = 0; s.failed_tests = 0;
    s.suite_name = name ? name : "AKP Test Suite"; s.timer = akp_timer_start(s.suite_name);
    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║  🧪 RUNNING TEST SUITE: %-37s ║\n" AKP_RESET, s.suite_name);
    printf(AKP_BOLD AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════════════╝\n" AKP_RESET);
    return s;
}

#define AKP_TEST(suite, name, condition) do { \
    (suite).total_tests++; \
    bool _passed = (condition); \
    if (_passed) { \
        (suite).passed_tests++; \
        printf(AKP_BOLD AKP_NEON_GREEN "  ✔ [PASS] " AKP_RESET "%-45s " AKP_DIM "(%s:%d)\n" AKP_RESET, name, __FILE__, __LINE__); \
    } else { \
        (suite).failed_tests++; \
        printf(AKP_BOLD AKP_FG_RED "  ✖ [FAIL] " AKP_RESET AKP_BOLD "%-45s " AKP_FG_RED "(%s:%d)\n" AKP_RESET, name, __FILE__, __LINE__); \
    } \
} while (0)

#define AKP_ASSERT_EQ(suite, name, actual, expected) \
    AKP_TEST(suite, name, ((actual) == (expected)))

#define AKP_ASSERT_TRUE(suite, name, condition) \
    AKP_TEST(suite, name, (condition))

#define AKP_ASSERT_STR_EQ(suite, name, actual, expected) \
    AKP_TEST(suite, name, (strcmp((actual), (expected)) == 0))

static inline int akp_test_suite_end(akp_test_suite_t* s) {
    double elapsed = akp_timer_stop_ms(&s->timer);
    float pass_rate = (s->total_tests > 0) ? ((float)s->passed_tests / (float)s->total_tests * 100.0f) : 0.0f;
    printf("\n" AKP_BOLD AKP_NEON_PURPLE "╔═══════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_PURPLE "║                    📊 TEST SUITE SUMMARY                      ║\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_PURPLE "╠═══════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║  Suite:        " AKP_BOLD AKP_NEON_YELLOW "%-42s" AKP_RESET " ║\n", s->suite_name);
    printf("║  Total Tests:  " AKP_BOLD AKP_NEON_CYAN "%-42d" AKP_RESET " ║\n", s->total_tests);
    printf("║  Passed:       " AKP_BOLD AKP_NEON_GREEN "%-42d" AKP_RESET " ║\n", s->passed_tests);
    printf("║  Failed:       " AKP_BOLD "%s%-42d" AKP_RESET " ║\n", (s->failed_tests > 0 ? AKP_FG_RED : AKP_DIM), s->failed_tests);
    printf("║  Elapsed Time: " AKP_BOLD AKP_GOLD "%-7.2f ms" AKP_RESET "                                  ║\n", elapsed);
    printf("║  Pass Rate:    " AKP_BOLD "%s%-6.1f%%" AKP_RESET "                                    ║\n", (s->failed_tests == 0 ? AKP_NEON_GREEN : AKP_FG_RED), pass_rate);
    printf(AKP_BOLD AKP_NEON_PURPLE "╚═══════════════════════════════════════════════════════════════╝\n" AKP_RESET);
    if (s->failed_tests == 0 && s->total_tests > 0) {
        printf(AKP_BOLD AKP_NEON_GREEN "✨ ALL TESTS PASSED! Engineered by Akshar Miyani.\n\n" AKP_RESET);
        akp_sound_success(); return 0;
    } else {
        printf(AKP_BOLD AKP_FG_RED "⚠️ SOME TESTS FAILED! Review assertions above.\n\n" AKP_RESET);
        akp_sound_alert(); return s->failed_tests;
    }
}

/* ============================================================================
 * [14] 2D GEOMETRIC TERMINAL CANVAS
 * ============================================================================ */

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
    c->width = width; c->height = height;
    c->buffer = (akp_pixel_t*)calloc(width * height, sizeof(akp_pixel_t));
    if (!c->buffer) { free(c); return NULL; }
    for (int i = 0; i < width * height; i++) { c->buffer[i].ch = ' '; c->buffer[i].has_color = false; }
    return c;
}

static inline void akp_canvas_draw_point(akp_canvas_t* c, int x, int y, char ch, akp_rgb_t color) {
    if (!c || x < 0 || x >= c->width || y < 0 || y >= c->height) return;
    int idx = y * c->width + x;
    c->buffer[idx].ch = ch; c->buffer[idx].color = color; c->buffer[idx].has_color = true;
}

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

static inline void akp_canvas_draw_circle(akp_canvas_t* c, int xc, int yc, int r, char ch, akp_rgb_t color) {
    if (!c || r <= 0) return;
    int x = 0, y = r, d = 3 - 2 * r;
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
        if (x + i >= 0 && x + i < c->width) akp_canvas_draw_point(c, x + i, y, text[i], color);
    }
}

static inline void akp_canvas_render(akp_canvas_t* c, const char* title) {
    if (!c) return;
    akp_init_console();
    if (title) printf("\n" AKP_BOLD AKP_NEON_CYAN "🎨 [ Canvas: %s (%dx%d) ]" AKP_RESET "\n", title, c->width, c->height);
    printf(AKP_DIM "┌"); for (int x = 0; x < c->width; x++) printf("─"); printf("┐\n" AKP_RESET);
    for (int y = 0; y < c->height; y++) {
        printf(AKP_DIM "│" AKP_RESET);
        for (int x = 0; x < c->width; x++) {
            akp_pixel_t* p = &c->buffer[y * c->width + x];
            if (p->has_color) { akp_set_fg_rgb(p->color.r, p->color.g, p->color.b); putchar(p->ch); printf(AKP_RESET); }
            else putchar(p->ch);
        }
        printf(AKP_DIM "│\n" AKP_RESET);
    }
    printf(AKP_DIM "└"); for (int x = 0; x < c->width; x++) printf("─"); printf("┘\n\n" AKP_RESET);
}

static inline void akp_canvas_free(akp_canvas_t* c) {
    if (c) { if (c->buffer) free(c->buffer); free(c); }
}

/* ============================================================================
 * [15] HARDWARE TELEMETRY & SYSTEM MONITOR
 * ============================================================================ */

typedef struct {
    uint64_t total_ram_mb;
    uint64_t free_ram_mb;
    uint32_t ram_usage_percent;
    uint32_t cpu_cores;
    char os_name[64];
    char cpu_arch[32];
} akp_sysinfo_t;

static inline akp_sysinfo_t akp_sysinfo_get(void) {
    akp_sysinfo_t info; memset(&info, 0, sizeof(info));
#if AKP_OS_WIN
    MEMORYSTATUSEX mem_stat; mem_stat.dwLength = sizeof(mem_stat);
    if (GlobalMemoryStatusEx(&mem_stat)) {
        info.total_ram_mb = mem_stat.ullTotalPhys / (1024 * 1024);
        info.free_ram_mb = mem_stat.ullAvailPhys / (1024 * 1024);
        info.ram_usage_percent = mem_stat.dwMemoryLoad;
    }
    SYSTEM_INFO sys_info; GetNativeSystemInfo(&sys_info);
    info.cpu_cores = sys_info.dwNumberOfProcessors;
    if (sys_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) strncpy(info.cpu_arch, "x86_64 (64-bit)", sizeof(info.cpu_arch) - 1);
    else if (sys_info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_ARM64) strncpy(info.cpu_arch, "ARM64 (64-bit)", sizeof(info.cpu_arch) - 1);
    else strncpy(info.cpu_arch, "x86 (32-bit)", sizeof(info.cpu_arch) - 1);
    strncpy(info.os_name, "Microsoft Windows NT", sizeof(info.os_name) - 1);
#else
    info.total_ram_mb = 16384; info.free_ram_mb = 8192; info.ram_usage_percent = 50; info.cpu_cores = 8;
    strncpy(info.cpu_arch, "POSIX x86_64", sizeof(info.cpu_arch) - 1); strncpy(info.os_name, "Unix / Linux", sizeof(info.os_name) - 1);
#endif
    return info;
}

static inline void akp_sysinfo_render(void) {
    akp_init_console();
    akp_sysinfo_t s = akp_sysinfo_get();
    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║            💻 AKP HARDWARE & SYSTEM TELEMETRY                 ║\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "╠═══════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║  OS Platform:   " AKP_BOLD AKP_FG_WHITE "%-45s" AKP_RESET " ║\n", s.os_name);
    printf("║  Architecture:  " AKP_BOLD AKP_NEON_YELLOW "%-45s" AKP_RESET " ║\n", s.cpu_arch);
    printf("║  CPU Cores:     " AKP_BOLD AKP_NEON_GREEN "%-45u" AKP_RESET " ║\n", s.cpu_cores);
    printf("║  Physical RAM:  " AKP_BOLD AKP_NEON_PINK "%-10llu MB (Free: %llu MB)" AKP_RESET "                 ║\n", (unsigned long long)s.total_ram_mb, (unsigned long long)s.free_ram_mb);
    printf("║  RAM Usage:     " AKP_BOLD AKP_NEON_CYAN "[");
    int bar_width = 24, filled = (s.ram_usage_percent * bar_width) / 100;
    for (int i = 0; i < bar_width; i++) { if (i < filled) printf("█"); else printf("░"); }
    printf("] %3u%%" AKP_RESET "                 ║\n", s.ram_usage_percent);
    printf(AKP_BOLD AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════════════╝\n\n" AKP_RESET);
}

/* ============================================================================
 * [16] LINEAR ALGEBRA & MATRIX OPERATIONS
 * ============================================================================ */

typedef struct {
    int rows;
    int cols;
    double* data;
} akp_mat_t;

static inline akp_mat_t* akp_mat_create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    akp_mat_t* m = (akp_mat_t*)malloc(sizeof(akp_mat_t));
    if (!m) return NULL;
    m->rows = rows; m->cols = cols;
    m->data = (double*)calloc(rows * cols, sizeof(double));
    if (!m->data) { free(m); return NULL; }
    return m;
}

static inline void akp_mat_set(akp_mat_t* m, int r, int c, double val) {
    if (m && r >= 0 && r < m->rows && c >= 0 && c < m->cols) m->data[r * m->cols + c] = val;
}

static inline double akp_mat_get(const akp_mat_t* m, int r, int c) {
    if (m && r >= 0 && r < m->rows && c >= 0 && c < m->cols) return m->data[r * m->cols + c];
    return 0.0;
}

static inline akp_mat_t* akp_mat_multiply(const akp_mat_t* A, const akp_mat_t* B) {
    if (!A || !B || A->cols != B->rows) return NULL;
    akp_mat_t* C = akp_mat_create(A->rows, B->cols);
    if (!C) return NULL;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < A->cols; k++) sum += akp_mat_get(A, i, k) * akp_mat_get(B, k, j);
            akp_mat_set(C, i, j, sum);
        }
    }
    return C;
}

static inline void akp_mat_render(const akp_mat_t* m, const char* title) {
    if (!m) return;
    akp_init_console();
    if (title) printf("\n" AKP_BOLD AKP_NEON_YELLOW "🔢 [ Matrix: %s (%dx%d) ]" AKP_RESET "\n", title, m->rows, m->cols);
    for (int r = 0; r < m->rows; r++) {
        printf(AKP_NEON_CYAN " │ " AKP_RESET);
        for (int c = 0; c < m->cols; c++) {
            double val = akp_mat_get(m, r, c);
            if (fabs(val) < 0.00001) printf(AKP_DIM " %7.2f " AKP_RESET, 0.0);
            else if (val > 0) printf(AKP_NEON_GREEN " %7.2f " AKP_RESET, val);
            else printf(AKP_NEON_PINK " %7.2f " AKP_RESET, val);
        }
        printf(AKP_NEON_CYAN " │\n" AKP_RESET);
    }
    printf("\n");
}

static inline void akp_mat_free(akp_mat_t* m) {
    if (m) { if (m->data) free(m->data); free(m); }
}

/* ============================================================================
 * [21] VISUAL LIFO STACK & CIRCULAR QUEUE
 * ============================================================================ */

typedef struct {
    int* data;
    int top;
    int capacity;
    char name[32];
} akp_stack_t;

static inline akp_stack_t* akp_stack_create(int capacity, const char* name) {
    akp_init_console();
    if (capacity <= 0) capacity = 8;
    akp_stack_t* s = (akp_stack_t*)malloc(sizeof(akp_stack_t));
    if (!s) return NULL;
    s->data = (int*)malloc(sizeof(int) * capacity);
    s->top = -1;
    s->capacity = capacity;
    strncpy(s->name, name ? name : "Stack", sizeof(s->name) - 1);
    s->name[sizeof(s->name) - 1] = '\0';
    return s;
}

static inline void akp_stack_free(akp_stack_t* s) {
    if (!s) return;
    if (s->data) free(s->data);
    free(s);
}

static inline int akp_stack_is_empty(const akp_stack_t* s) {
    return (s == NULL || s->top < 0);
}

static inline int akp_stack_is_full(const akp_stack_t* s) {
    return (s != NULL && s->top >= s->capacity - 1);
}

static inline int akp_stack_push(akp_stack_t* s, int value) {
    if (!s) return 0;
    if (akp_stack_is_full(s)) {
        akp_log_error("STACK", "Stack Overflow! Cannot push element.");
        return 0;
    }
    s->top++;
    s->data[s->top] = value;
    return 1;
}

static inline int akp_stack_pop(akp_stack_t* s, int* out_value) {
    if (!s || akp_stack_is_empty(s)) {
        akp_log_error("STACK", "Stack Underflow! Stack is currently empty.");
        return 0;
    }
    if (out_value) *out_value = s->data[s->top];
    s->top--;
    return 1;
}

static inline void akp_stack_render(const akp_stack_t* s) {
    if (!s) return;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_CYAN "┌────────────────────────────────────────────────────────┐\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "│ 📦 VISUAL STACK (LIFO): %-31s│\n" AKP_RESET, s->name);
    printf(AKP_BOLD AKP_NEON_CYAN "├────────────────────────────────────────────────────────┤\n" AKP_RESET);
    if (s->top < 0) {
        printf(AKP_BOLD AKP_DIM "│  [ STACK IS CURRENTLY EMPTY (TOP = -1) ]               │\n" AKP_RESET);
    } else {
        for (int i = s->top; i >= 0; i--) {
            const char* tag = (i == s->top) ? "TOP ->" : (i == 0 ? "BOT ->" : "      ");
            const char* col = (i == s->top) ? AKP_NEON_GOLD : AKP_NEON_CYAN;
            printf(AKP_BOLD "│   %s %s│ %6d │%s  (index: %2d)                     │\n" AKP_RESET,
                   tag, col, s->data[i], AKP_RESET, i);
            if (i > 0) printf(AKP_BOLD AKP_DIM "│          ├──--------──┤                                │\n" AKP_RESET);
        }
    }
    printf(AKP_BOLD AKP_NEON_CYAN "├────────────────────────────────────────────────────────┤\n" AKP_RESET);
    int pct = (s->capacity > 0) ? ((s->top + 1) * 100) / s->capacity : 0;
    int filled_bars = (pct * 20) / 100;
    printf(AKP_BOLD "│  Load: [" AKP_NEON_GREEN);
    for (int b = 0; b < 20; b++) {
        if (b < filled_bars) printf("█");
        else printf(AKP_DIM "░" AKP_RESET AKP_BOLD);
    }
    printf(AKP_RESET AKP_BOLD "] %3d%% (%d/%d elements)       │\n" AKP_RESET, pct, s->top + 1, s->capacity);
    printf(AKP_BOLD AKP_NEON_CYAN "└────────────────────────────────────────────────────────┘\n\n" AKP_RESET);
}

typedef struct {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
    char name[32];
} akp_queue_t;

static inline akp_queue_t* akp_queue_create(int capacity, const char* name) {
    akp_init_console();
    if (capacity <= 0) capacity = 6;
    akp_queue_t* q = (akp_queue_t*)malloc(sizeof(akp_queue_t));
    if (!q) return NULL;
    q->data = (int*)malloc(sizeof(int) * capacity);
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
    strncpy(q->name, name ? name : "CircularQueue", sizeof(q->name) - 1);
    q->name[sizeof(q->name) - 1] = '\0';
    return q;
}

static inline void akp_queue_free(akp_queue_t* q) {
    if (!q) return;
    if (q->data) free(q->data);
    free(q);
}

static inline int akp_queue_is_empty(const akp_queue_t* q) {
    return (q == NULL || q->size == 0);
}

static inline int akp_queue_is_full(const akp_queue_t* q) {
    return (q != NULL && q->size >= q->capacity);
}

static inline int akp_queue_enqueue(akp_queue_t* q, int value) {
    if (!q) return 0;
    if (akp_queue_is_full(q)) {
        akp_log_error("QUEUE", "Queue Overflow! Queue is full.");
        return 0;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value;
    q->size++;
    return 1;
}

static inline int akp_queue_dequeue(akp_queue_t* q, int* out_value) {
    if (!q || akp_queue_is_empty(q)) {
        akp_log_error("QUEUE", "Queue Underflow! Queue is currently empty.");
        return 0;
    }
    if (out_value) *out_value = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    return 1;
}

static inline void akp_queue_render(const akp_queue_t* q) {
    if (!q) return;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_PINK "┌────────────────────────────────────────────────────────┐\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_PINK "│ 🔄 CIRCULAR QUEUE (FIFO): %-29s│\n" AKP_RESET, q->name);
    printf(AKP_BOLD AKP_NEON_PINK "├────────────────────────────────────────────────────────┤\n" AKP_RESET);
    printf("│  Slots: ");
    for (int i = 0; i < q->capacity; i++) {
        int occupied = 0;
        if (q->size > 0) {
            if (q->front <= q->rear) occupied = (i >= q->front && i <= q->rear);
            else occupied = (i >= q->front || i <= q->rear);
        }
        if (occupied) printf(AKP_BOLD AKP_NEON_CYAN "[%4d] " AKP_RESET, q->data[i]);
        else printf(AKP_DIM "[  -- ] " AKP_RESET);
    }
    printf("│\n│         ");
    for (int i = 0; i < q->capacity; i++) {
        int is_front = (q->size > 0 && i == q->front);
        int is_rear  = (q->size > 0 && i == q->rear);
        if (is_front && is_rear) printf(AKP_BOLD AKP_NEON_GOLD " F,R   " AKP_RESET);
        else if (is_front) printf(AKP_BOLD AKP_NEON_GREEN "  F    " AKP_RESET);
        else if (is_rear) printf(AKP_BOLD AKP_NEON_PINK "  R    " AKP_RESET);
        else printf("       ");
    }
    printf("│\n" AKP_BOLD AKP_NEON_PINK "├────────────────────────────────────────────────────────┤\n" AKP_RESET);
    printf(AKP_BOLD "│  Front: %2d  |  Rear: %2d  |  Size: %2d / %2d (Capacity)     │\n" AKP_RESET,
           q->front, q->rear, q->size, q->capacity);
    printf(AKP_BOLD AKP_NEON_PINK "└────────────────────────────────────────────────────────┘\n\n" AKP_RESET);
}

/* ============================================================================
 * [22] VISUAL LINEAR & BINARY SEARCH ALGORITHMS
 * ============================================================================ */

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

static inline int akp_search_binary(const int* arr, int n, int target) {
    if (!arr || n <= 0) return -1;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_PINK "⚡ INITIATING VISUAL BINARY SEARCH FOR TARGET: [%d]\n" AKP_RESET, target);
    printf(AKP_DIM "--------------------------------------------------------------------------------\n" AKP_RESET);
    int low = 0, high = n - 1, step = 0;
    while (low <= high) {
        step++;
        int mid = low + (high - low) / 2;
        printf(AKP_BOLD "  [Step %d] Low: %2d (val: %3d) | Mid: %2d (val: " AKP_NEON_GOLD "%3d" AKP_RESET AKP_BOLD ") | High: %2d (val: %3d)\n" AKP_RESET,
               step, low, arr[low], mid, arr[mid], high, arr[high]);
        printf("   Window: ");
        for (int i = 0; i < n; i++) {
            if (i == mid) printf(AKP_BOLD AKP_NEON_GOLD "[%3d]* " AKP_RESET, arr[i]);
            else if (i >= low && i <= high) printf(AKP_BOLD AKP_NEON_CYAN "[%3d]  " AKP_RESET, arr[i]);
            else printf(AKP_DIM "[ . ]  " AKP_RESET);
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

/* ============================================================================
 * [23] GRAPH TOPOLOGY & ADJACENCY MATRIX
 * ============================================================================ */

#define AKP_GRAPH_MAX_VERTICES 32

typedef struct {
    int vertices;
    int is_directed;
    int adj[AKP_GRAPH_MAX_VERTICES][AKP_GRAPH_MAX_VERTICES];
} akp_graph_t;

static inline akp_graph_t* akp_graph_create(int vertices, int is_directed) {
    akp_init_console();
    if (vertices > AKP_GRAPH_MAX_VERTICES) vertices = AKP_GRAPH_MAX_VERTICES;
    if (vertices <= 0) vertices = 4;
    akp_graph_t* g = (akp_graph_t*)malloc(sizeof(akp_graph_t));
    if (!g) return NULL;
    g->vertices = vertices;
    g->is_directed = is_directed;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) g->adj[i][j] = 0;
    }
    return g;
}

static inline void akp_graph_free(akp_graph_t* g) {
    if (g) free(g);
}

static inline void akp_graph_add_edge(akp_graph_t* g, int u, int v, int weight) {
    if (!g || u < 0 || u >= g->vertices || v < 0 || v >= g->vertices) return;
    if (weight == 0) weight = 1;
    g->adj[u][v] = weight;
    if (!g->is_directed) g->adj[v][u] = weight;
}

static inline void akp_graph_render_adj_matrix(const akp_graph_t* g, const char* title) {
    if (!g) return;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║ 🌐 GRAPH ADJACENCY MATRIX: %-26s ║\n" AKP_RESET, title ? title : "Network Graph");
    printf(AKP_BOLD AKP_NEON_CYAN "╠═══════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║ Type: %s | Vertices: %2d                   ║\n",
           g->is_directed ? "Directed  " : "Undirected", g->vertices);
    printf(AKP_BOLD AKP_NEON_CYAN "╚═══════════════════════════════════════════════════════╝\n" AKP_RESET);
    printf("     ");
    for (int j = 0; j < g->vertices; j++) printf(AKP_BOLD AKP_NEON_GOLD " V%d  " AKP_RESET, j);
    printf("\n");
    for (int i = 0; i < g->vertices; i++) {
        printf(AKP_BOLD AKP_NEON_GOLD " V%d " AKP_RESET AKP_BOLD "│" AKP_RESET, i);
        for (int j = 0; j < g->vertices; j++) {
            if (g->adj[i][j] > 0) printf(AKP_BOLD AKP_NEON_GREEN " %2d  " AKP_RESET, g->adj[i][j]);
            else printf(AKP_DIM "  .  " AKP_RESET);
        }
        printf(AKP_BOLD "│\n" AKP_RESET);
    }
    printf("\n");
}

static inline void akp_graph_bfs(const akp_graph_t* g, int start_vertex) {
    if (!g || start_vertex < 0 || start_vertex >= g->vertices) return;
    akp_init_console();
    int visited[AKP_GRAPH_MAX_VERTICES] = {0};
    int queue[AKP_GRAPH_MAX_VERTICES];
    int front = 0, rear = 0;
    printf(AKP_BOLD AKP_NEON_GREEN "🌊 BREADTH-FIRST SEARCH (BFS) STARTING AT V%d:\n" AKP_RESET, start_vertex);
    printf("   Traversal Order: ");
    visited[start_vertex] = 1;
    queue[rear++] = start_vertex;
    int first = 1;
    while (front < rear) {
        int u = queue[front++];
        if (!first) printf(" -> ");
        printf(AKP_BOLD AKP_NEON_GOLD "[V%d]" AKP_RESET, u);
        first = 0;
        for (int v = 0; v < g->vertices; v++) {
            if (g->adj[u][v] > 0 && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }
    printf("\n\n");
}

/* ============================================================================
 * [24] TERMINAL COLOR THEMES
 * ============================================================================ */

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
            t.primary = akp_rgb(0, 255, 65);
            t.secondary = akp_rgb(0, 143, 17);
            t.accent = akp_rgb(200, 255, 200);
            break;
        case AKP_THEME_SYNTHWAVE:
            t.name = "Synthwave 84";
            t.primary = akp_rgb(255, 0, 128);
            t.secondary = akp_rgb(0, 240, 255);
            t.accent = akp_rgb(255, 180, 0);
            break;
        case AKP_THEME_DRACULA:
            t.name = "Dracula Pro";
            t.primary = akp_rgb(189, 147, 249);
            t.secondary = akp_rgb(255, 121, 198);
            t.accent = akp_rgb(80, 250, 123);
            break;
        case AKP_THEME_MONOKAI:
            t.name = "Monokai Sublime";
            t.primary = akp_rgb(230, 219, 116);
            t.secondary = akp_rgb(253, 151, 31);
            t.accent = akp_rgb(102, 217, 239);
            break;
        case AKP_THEME_CYBERPUNK:
        default:
            t.name = "Cyberpunk 2077";
            t.primary = akp_rgb(0, 243, 255);
            t.secondary = akp_rgb(255, 0, 85);
            t.accent = akp_rgb(255, 230, 0);
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

/* ============================================================================
 * [25] HASH TABLE VISUALIZER (CHAINING)
 * ============================================================================ */

typedef struct akp_ht_node {
    int key;
    int value;
    struct akp_ht_node* next;
} akp_ht_node_t;

typedef struct {
    akp_ht_node_t** buckets;
    int num_buckets;
    int num_elements;
    int collisions;
    char name[32];
} akp_ht_t;

static inline int akp_ht_hash(int key, int num_buckets) {
    int h = key % num_buckets;
    return (h < 0) ? (h + num_buckets) : h;
}

static inline akp_ht_t* akp_ht_create(int num_buckets, const char* name) {
    akp_init_console();
    if (num_buckets <= 0) num_buckets = 8;
    akp_ht_t* ht = (akp_ht_t*)malloc(sizeof(akp_ht_t));
    if (!ht) return NULL;
    ht->num_buckets = num_buckets;
    ht->num_elements = 0;
    ht->collisions = 0;
    strncpy(ht->name, name ? name : "HashTable", sizeof(ht->name) - 1);
    ht->name[sizeof(ht->name) - 1] = '\0';
    ht->buckets = (akp_ht_node_t**)calloc((size_t)num_buckets, sizeof(akp_ht_node_t*));
    return ht;
}

static inline void akp_ht_insert(akp_ht_t* ht, int key, int value) {
    if (!ht) return;
    int idx = akp_ht_hash(key, ht->num_buckets);
    akp_ht_node_t* cur = ht->buckets[idx];
    while (cur) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }
    if (ht->buckets[idx] != NULL) ht->collisions++;
    akp_ht_node_t* new_node = (akp_ht_node_t*)malloc(sizeof(akp_ht_node_t));
    new_node->key = key;
    new_node->value = value;
    new_node->next = ht->buckets[idx];
    ht->buckets[idx] = new_node;
    ht->num_elements++;
}

static inline int akp_ht_search(const akp_ht_t* ht, int key, int* out_value) {
    if (!ht) return 0;
    int idx = akp_ht_hash(key, ht->num_buckets);
    akp_ht_node_t* cur = ht->buckets[idx];
    while (cur) {
        if (cur->key == key) {
            if (out_value) *out_value = cur->value;
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

static inline void akp_ht_render(const akp_ht_t* ht) {
    if (!ht) return;
    akp_init_console();
    float load_factor = (ht->num_buckets > 0) ? ((float)ht->num_elements / (float)ht->num_buckets) : 0.0f;
    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_CYAN "║ 🗄️  HASH TABLE VISUALIZER (CHAINING): %-33s ║\n" AKP_RESET, ht->name);
    printf(AKP_BOLD AKP_NEON_CYAN "╠═════════════════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║ Buckets: %2d | Elements: %2d | Collisions: %2d | Load Factor: %4.2f      ║\n",
           ht->num_buckets, ht->num_elements, ht->collisions, load_factor);
    printf(AKP_BOLD AKP_NEON_CYAN "╚═════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);
    for (int i = 0; i < ht->num_buckets; i++) {
        printf(AKP_BOLD AKP_NEON_GOLD " [Bucket %2d] " AKP_RESET, i);
        akp_ht_node_t* cur = ht->buckets[i];
        if (!cur) {
            printf(AKP_DIM "--> (empty)\n" AKP_RESET);
        } else {
            while (cur) {
                printf("--> " AKP_BOLD AKP_NEON_CYAN "[Key: %3d | Val: %4d]" AKP_RESET " ", cur->key, cur->value);
                cur = cur->next;
            }
            printf("--> " AKP_DIM "NULL\n" AKP_RESET);
        }
    }
    printf("\n");
}

static inline void akp_ht_free(akp_ht_t* ht) {
    if (!ht) return;
    for (int i = 0; i < ht->num_buckets; i++) {
        akp_ht_node_t* cur = ht->buckets[i];
        while (cur) {
            akp_ht_node_t* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(ht->buckets);
    free(ht);
}

/* ============================================================================
 * [26] LINKED LIST VISUALIZER (SINGLY & DOUBLY)
 * ============================================================================ */

typedef struct akp_snode {
    int data;
    struct akp_snode* next;
} akp_snode_t;

typedef struct {
    akp_snode_t* head;
    int size;
    char name[32];
} akp_slist_t;

static inline akp_slist_t* akp_slist_create(const char* name) {
    akp_init_console();
    akp_slist_t* list = (akp_slist_t*)malloc(sizeof(akp_slist_t));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    strncpy(list->name, name ? name : "SinglyList", sizeof(list->name) - 1);
    list->name[sizeof(list->name) - 1] = '\0';
    return list;
}

static inline void akp_slist_insert_head(akp_slist_t* list, int data) {
    if (!list) return;
    akp_snode_t* node = (akp_snode_t*)malloc(sizeof(akp_snode_t));
    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
}

static inline void akp_slist_insert_tail(akp_slist_t* list, int data) {
    if (!list) return;
    akp_snode_t* node = (akp_snode_t*)malloc(sizeof(akp_snode_t));
    node->data = data;
    node->next = NULL;
    if (!list->head) {
        list->head = node;
    } else {
        akp_snode_t* cur = list->head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
    list->size++;
}

static inline int akp_slist_delete(akp_slist_t* list, int data) {
    if (!list || !list->head) return 0;
    akp_snode_t* cur = list->head;
    akp_snode_t* prev = NULL;
    while (cur && cur->data != data) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return 0;
    if (!prev) list->head = cur->next;
    else prev->next = cur->next;
    free(cur);
    list->size--;
    return 1;
}

static inline void akp_slist_render(const akp_slist_t* list) {
    if (!list) return;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_CYAN "🔗 SINGLY LINKED LIST: %s (Length: %d)\n" AKP_RESET, list->name, list->size);
    printf("   " AKP_BOLD AKP_NEON_YELLOW "[HEAD]" AKP_RESET);
    if (!list->head) {
        printf(" -> " AKP_DIM "NULL\n\n" AKP_RESET);
        return;
    }
    akp_snode_t* cur = list->head;
    while (cur) {
        printf(" -> " AKP_BOLD AKP_NEON_CYAN "[ %4d | • ]" AKP_RESET, cur->data);
        cur = cur->next;
    }
    printf(" -> " AKP_DIM "NULL\n\n" AKP_RESET);
}

static inline void akp_slist_free(akp_slist_t* list) {
    if (!list) return;
    akp_snode_t* cur = list->head;
    while (cur) {
        akp_snode_t* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(list);
}

typedef struct akp_dnode {
    int data;
    struct akp_dnode* prev;
    struct akp_dnode* next;
} akp_dnode_t;

typedef struct {
    akp_dnode_t* head;
    akp_dnode_t* tail;
    int size;
    char name[32];
} akp_dlist_t;

static inline akp_dlist_t* akp_dlist_create(const char* name) {
    akp_init_console();
    akp_dlist_t* list = (akp_dlist_t*)malloc(sizeof(akp_dlist_t));
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    strncpy(list->name, name ? name : "DoublyList", sizeof(list->name) - 1);
    list->name[sizeof(list->name) - 1] = '\0';
    return list;
}

static inline void akp_dlist_insert_tail(akp_dlist_t* list, int data) {
    if (!list) return;
    akp_dnode_t* node = (akp_dnode_t*)malloc(sizeof(akp_dnode_t));
    node->data = data;
    node->next = NULL;
    node->prev = list->tail;
    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

static inline void akp_dlist_render(const akp_dlist_t* list) {
    if (!list) return;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_PINK "↔️  DOUBLY LINKED LIST: %s (Length: %d)\n" AKP_RESET, list->name, list->size);
    printf("   " AKP_BOLD AKP_NEON_YELLOW "[HEAD]" AKP_RESET);
    if (!list->head) {
        printf(" <-> " AKP_DIM "NULL\n\n" AKP_RESET);
        return;
    }
    akp_dnode_t* cur = list->head;
    while (cur) {
        printf(" <-> " AKP_BOLD AKP_NEON_PINK "[ • | %4d | • ]" AKP_RESET, cur->data);
        cur = cur->next;
    }
    printf(" <-> " AKP_BOLD AKP_NEON_YELLOW "[TAIL]\n\n" AKP_RESET);
}

static inline void akp_dlist_free(akp_dlist_t* list) {
    if (!list) return;
    akp_dnode_t* cur = list->head;
    while (cur) {
        akp_dnode_t* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(list);
}

/* ============================================================================
 * [27] DIJKSTRA SHORTEST PATH ANALYSIS
 * ============================================================================ */

#define AKP_INF 999999

typedef struct {
    int dist[AKP_GRAPH_MAX_VERTICES];
    int parent[AKP_GRAPH_MAX_VERTICES];
    int visited[AKP_GRAPH_MAX_VERTICES];
    int vertices;
    int source;
} akp_dijkstra_t;

static inline akp_dijkstra_t akp_dijkstra_solve(const akp_graph_t* g, int source) {
    akp_dijkstra_t res;
    res.vertices = g ? g->vertices : 0;
    res.source = source;
    if (!g || source < 0 || source >= g->vertices) return res;

    for (int i = 0; i < g->vertices; i++) {
        res.dist[i] = AKP_INF;
        res.visited[i] = 0;
        res.parent[i] = -1;
    }
    res.dist[source] = 0;

    for (int count = 0; count < g->vertices - 1; count++) {
        int min_dist = AKP_INF;
        int u = -1;
        for (int v = 0; v < g->vertices; v++) {
            if (!res.visited[v] && res.dist[v] <= min_dist) {
                min_dist = res.dist[v];
                u = v;
            }
        }
        if (u == -1 || min_dist == AKP_INF) break;
        res.visited[u] = 1;

        for (int v = 0; v < g->vertices; v++) {
            if (!res.visited[v] && g->adj[u][v] > 0 && res.dist[u] != AKP_INF
                && res.dist[u] + g->adj[u][v] < res.dist[v]) {
                res.dist[v] = res.dist[u] + g->adj[u][v];
                res.parent[v] = u;
            }
        }
    }
    return res;
}

static inline void akp_dijkstra_print_path(const akp_dijkstra_t* res, int j) {
    if (res->parent[j] == -1) {
        printf("V%d", j);
        return;
    }
    akp_dijkstra_print_path(res, res->parent[j]);
    printf(" -> V%d", j);
}

static inline void akp_dijkstra_render(const akp_dijkstra_t* res) {
    if (!res) return;
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_GREEN "╔═════════════════════════════════════════════════════════════════════════╗\n" AKP_RESET);
    printf(AKP_BOLD AKP_NEON_GREEN "║ 🛣️  DIJKSTRA SHORTEST PATH ANALYSIS (Source: V%-2d)                      ║\n" AKP_RESET, res->source);
    printf(AKP_BOLD AKP_NEON_GREEN "╠═════════════════════════════════════════════════════════════════════════╣\n" AKP_RESET);
    printf("║ Destination │ Shortest Cost │ Full Route Sequence                     ║\n");
    printf(AKP_BOLD AKP_NEON_GREEN "╠═════════════╪═══════════════╪═════════════════════════════════════════╣\n" AKP_RESET);
    for (int i = 0; i < res->vertices; i++) {
        if (res->dist[i] == AKP_INF) {
            printf("║ V%-10d │ " AKP_DIM "UNREACHABLE " AKP_RESET "│ (No directed path)                    ║\n", i);
        } else {
            printf("║ V%-10d │ " AKP_BOLD AKP_NEON_GOLD "%13d" AKP_RESET " │ ", i, res->dist[i]);
            akp_dijkstra_print_path(res, i);
            printf("\n");
        }
    }
    printf(AKP_BOLD AKP_NEON_GREEN "╚═════════════╧═══════════════╧═════════════════════════════════════════╝\n\n" AKP_RESET);
}

/* ============================================================================
 * [28] STRING PATTERN MATCHING (NAIVE & KMP)
 * ============================================================================ */

static inline int akp_search_naive_pattern(const char* text, const char* pattern) {
    if (!text || !pattern) return -1;
    akp_init_console();
    size_t n = strlen(text);
    size_t m = strlen(pattern);
    if (m == 0 || m > n) return -1;

    printf("\n" AKP_BOLD AKP_NEON_CYAN "🔤 NAIVE PATTERN SEARCH: \"%s\" in \"%s\"\n" AKP_RESET, pattern, text);
    printf(AKP_DIM "----------------------------------------------------------------------\n" AKP_RESET);

    int comparisons = 0;
    for (size_t i = 0; i <= n - m; i++) {
        size_t j;
        for (j = 0; j < m; j++) {
            comparisons++;
            if (text[i + j] != pattern[j]) break;
        }
        if (j == m) {
            printf(AKP_BOLD AKP_NEON_GREEN "✔ Match found at index %zu after %d comparisons! ✨\n\n" AKP_RESET, i, comparisons);
            return (int)i;
        }
    }
    printf(AKP_BOLD AKP_NEON_RED "✖ Pattern not found after %d comparisons.\n\n" AKP_RESET, comparisons);
    return -1;
}

static inline void akp_kmp_compute_lps(const char* pattern, int* lps, size_t m) {
    size_t len = 0;
    lps[0] = 0;
    size_t i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = (int)len;
            i++;
        } else {
            if (len != 0) len = (size_t)lps[len - 1];
            else { lps[i] = 0; i++; }
        }
    }
}

static inline int akp_search_kmp(const char* text, const char* pattern) {
    if (!text || !pattern) return -1;
    akp_init_console();
    size_t n = strlen(text);
    size_t m = strlen(pattern);
    if (m == 0 || m > n) return -1;

    int* lps = (int*)malloc(sizeof(int) * m);
    if (!lps) return -1;
    akp_kmp_compute_lps(pattern, lps, m);

    printf("\n" AKP_BOLD AKP_NEON_PINK "⚡ KMP ALGORITHM SEARCH: \"%s\" (Length: %zu)\n" AKP_RESET, pattern, m);
    printf("   Computed LPS Table: ");
    for (size_t k = 0; k < m; k++) printf("[%c: %d] ", pattern[k], lps[k]);
    printf("\n");

    size_t i = 0, j = 0;
    int comparisons = 0;
    while (i < n) {
        comparisons++;
        if (pattern[j] == text[i]) { j++; i++; }
        if (j == m) {
            int match_idx = (int)(i - j);
            printf(AKP_BOLD AKP_NEON_GREEN "✨ KMP MATCH LOCATED at index %d in %d comparisons (Time: O(N))!\n\n" AKP_RESET,
                   match_idx, comparisons);
            free(lps);
            return match_idx;
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = (size_t)lps[j - 1];
            else i++;
        }
    }
    printf(AKP_BOLD AKP_NEON_RED "✖ KMP search: Pattern not found in text.\n\n" AKP_RESET);
    free(lps);
    return -1;
}

/* ============================================================================
 * 29. VISUAL BINARY MIN-HEAP & PRIORITY QUEUE
 * ============================================================================ */
typedef struct {
    int* data;
    int size;
    int capacity;
    char name[32];
} akp_min_heap_t;

static inline akp_min_heap_t* akp_min_heap_create(int capacity, const char* name) {
    akp_min_heap_t* heap = (akp_min_heap_t*)malloc(sizeof(akp_min_heap_t));
    if (!heap) return NULL;
    heap->capacity = capacity > 0 ? capacity : 16;
    heap->data = (int*)malloc((size_t)heap->capacity * sizeof(int));
    heap->size = 0;
    if (name) {
        strncpy(heap->name, name, sizeof(heap->name) - 1);
        heap->name[sizeof(heap->name) - 1] = '\0';
    } else {
        strcpy(heap->name, "MinHeap");
    }
    return heap;
}

static inline void akp_min_heap_destroy(akp_min_heap_t* heap) {
    if (!heap) return;
    if (heap->data) free(heap->data);
    free(heap);
}

static inline void akp_min_heap_swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

static inline bool akp_min_heap_insert(akp_min_heap_t* heap, int val) {
    if (!heap) return false;
    if (heap->size >= heap->capacity) {
        int new_cap = heap->capacity * 2;
        int* new_data = (int*)realloc(heap->data, (size_t)new_cap * sizeof(int));
        if (!new_data) return false;
        heap->data = new_data;
        heap->capacity = new_cap;
    }
    
    int i = heap->size++;
    heap->data[i] = val;

    while (i != 0) {
        int parent = (i - 1) / 2;
        if (heap->data[parent] > heap->data[i]) {
            akp_min_heap_swap(&heap->data[parent], &heap->data[i]);
            i = parent;
        } else {
            break;
        }
    }
    return true;
}

static inline bool akp_min_heap_extract_min(akp_min_heap_t* heap, int* out_val) {
    if (!heap || heap->size <= 0) return false;
    if (out_val) *out_val = heap->data[0];

    if (heap->size == 1) {
        heap->size--;
        return true;
    }

    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    int i = 0;
    while (true) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) smallest = left;
        if (right < heap->size && heap->data[right] < heap->data[smallest]) smallest = right;
        if (smallest != i) {
            akp_min_heap_swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return true;
}

static inline int akp_min_heap_peek(const akp_min_heap_t* heap) {
    if (!heap || heap->size <= 0) return -1;
    return heap->data[0];
}

static inline void akp_min_heap_render(const akp_min_heap_t* heap, const char* title) {
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  🔷 BINARY MIN-HEAP & PRIORITY QUEUE TELEMETRY                                ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    if (title) {
        printf(AKP_BOLD AKP_NEON_YELLOW "  ⚡ Heap Name: %s (%s)\n" AKP_RESET, heap ? heap->name : "N/A", title);
    }

    if (!heap || heap->size == 0) {
        printf(AKP_BOLD AKP_NEON_RED "  [ Heap is currently EMPTY ]\n\n" AKP_RESET);
        return;
    }

    printf(AKP_BOLD AKP_NEON_GREEN "  Elements: %d / %d  |  Min Value (Root): %d\n\n" AKP_RESET, heap->size, heap->capacity, heap->data[0]);

    printf("  Linear Memory Layout (Array Storage):\n  ");
    for (int i = 0; i < heap->size; i++) {
        if (i == 0) {
            printf(AKP_BOLD AKP_NEON_YELLOW "[%d: ROOT(%d)] " AKP_RESET, i, heap->data[i]);
        } else {
            int p = (i - 1) / 2;
            printf(AKP_BOLD AKP_NEON_BLUE "[%d: %d (P:%d)] " AKP_RESET, i, heap->data[i], p);
        }
    }
    printf("\n\n  Binary Tree Level Breakdown:\n");
    int level = 0, count = 1, idx = 0;
    while (idx < heap->size) {
        printf(AKP_BOLD AKP_NEON_PINK "    Level %d: " AKP_RESET, level);
        for (int c = 0; c < count && idx < heap->size; c++, idx++) {
            printf(AKP_BOLD "(%d) " AKP_RESET, heap->data[idx]);
        }
        printf("\n");
        level++;
        count *= 2;
    }
    printf("\n");
}

/* ============================================================================
 * 30. VISUAL PREFIX TREE (TRIE) & AUTOCOMPLETE ENGINE
 * ============================================================================ */
#define AKP_TRIE_ALPHABET_SIZE 26

typedef struct akp_trie_node {
    struct akp_trie_node* children[AKP_TRIE_ALPHABET_SIZE];
    bool is_end_of_word;
    char ch;
} akp_trie_node_t;

typedef struct {
    akp_trie_node_t* root;
    int word_count;
    int node_count;
} akp_trie_t;

static inline akp_trie_node_t* akp_trie_node_create(char ch) {
    akp_trie_node_t* node = (akp_trie_node_t*)malloc(sizeof(akp_trie_node_t));
    if (!node) return NULL;
    node->is_end_of_word = false;
    node->ch = ch;
    for (int i = 0; i < AKP_TRIE_ALPHABET_SIZE; i++) node->children[i] = NULL;
    return node;
}

static inline akp_trie_t* akp_trie_create(void) {
    akp_trie_t* trie = (akp_trie_t*)malloc(sizeof(akp_trie_t));
    if (!trie) return NULL;
    trie->root = akp_trie_node_create('/');
    trie->word_count = 0;
    trie->node_count = 1;
    return trie;
}

static inline void akp_trie_destroy_nodes(akp_trie_node_t* node) {
    if (!node) return;
    for (int i = 0; i < AKP_TRIE_ALPHABET_SIZE; i++) {
        if (node->children[i]) akp_trie_destroy_nodes(node->children[i]);
    }
    free(node);
}

static inline void akp_trie_destroy(akp_trie_t* trie) {
    if (!trie) return;
    if (trie->root) akp_trie_destroy_nodes(trie->root);
    free(trie);
}

static inline bool akp_trie_insert(akp_trie_t* trie, const char* word) {
    if (!trie || !word || !trie->root) return false;
    akp_trie_node_t* curr = trie->root;
    int len = (int)strlen(word);

    for (int i = 0; i < len; i++) {
        char c = (char)tolower((unsigned char)word[i]);
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';

        if (!curr->children[idx]) {
            curr->children[idx] = akp_trie_node_create(c);
            trie->node_count++;
        }
        curr = curr->children[idx];
    }

    if (!curr->is_end_of_word) {
        curr->is_end_of_word = true;
        trie->word_count++;
        return true;
    }
    return false;
}

static inline bool akp_trie_search(const akp_trie_t* trie, const char* word) {
    if (!trie || !word || !trie->root) return false;
    akp_trie_node_t* curr = trie->root;
    int len = (int)strlen(word);

    for (int i = 0; i < len; i++) {
        char c = (char)tolower((unsigned char)word[i]);
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';
        if (!curr->children[idx]) return false;
        curr = curr->children[idx];
    }
    return curr != NULL && curr->is_end_of_word;
}

static inline bool akp_trie_starts_with(const akp_trie_t* trie, const char* prefix) {
    if (!trie || !prefix || !trie->root) return false;
    akp_trie_node_t* curr = trie->root;
    int len = (int)strlen(prefix);

    for (int i = 0; i < len; i++) {
        char c = (char)tolower((unsigned char)prefix[i]);
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';
        if (!curr->children[idx]) return false;
        curr = curr->children[idx];
    }
    return true;
}

static inline void akp_trie_print_recursive(const akp_trie_node_t* node, char* prefix, int depth) {
    if (!node) return;
    for (int i = 0; i < AKP_TRIE_ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            akp_trie_node_t* child = node->children[i];
            for (int d = 0; d < depth; d++) printf(AKP_DIM "│  " AKP_RESET);
            printf(AKP_BOLD AKP_NEON_CYAN "└── [%c]" AKP_RESET, child->ch);
            if (child->is_end_of_word) printf(AKP_BOLD AKP_NEON_YELLOW " ★ (WORD)" AKP_RESET);
            printf("\n");

            prefix[depth] = child->ch;
            prefix[depth + 1] = '\0';
            akp_trie_print_recursive(child, prefix, depth + 1);
        }
    }
}

static inline void akp_trie_render(const akp_trie_t* trie, const char* title) {
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  🌳 PREFIX TREE (TRIE) STRUCTURE & VOCABULARY HIERARCHY                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    if (title) printf(AKP_BOLD AKP_NEON_YELLOW "  ⚡ Vocabulary Group: %s\n" AKP_RESET, title);
    if (!trie || !trie->root) {
        printf(AKP_BOLD AKP_NEON_RED "  [ Trie is NULL ]\n\n" AKP_RESET);
        return;
    }

    printf(AKP_BOLD AKP_NEON_GREEN "  Total Words: %d  |  Total Nodes: %d  |  Root: '/'\n\n" AKP_RESET, trie->word_count, trie->node_count);
    char buf[128];
    buf[0] = '\0';
    printf(AKP_BOLD AKP_NEON_PINK "  [ROOT] (/)\n" AKP_RESET);
    akp_trie_print_recursive(trie->root, buf, 0);
    printf("\n");
}

/* ============================================================================
 * 31. VISUAL HUFFMAN CODING & DATA COMPRESSION VISUALIZER
 * ============================================================================ */
typedef struct akp_huffman_node {
    char ch;
    int freq;
    struct akp_huffman_node* left;
    struct akp_huffman_node* right;
} akp_huffman_node_t;

typedef struct {
    char ch;
    char code[32];
    int freq;
} akp_huffman_code_t;

typedef struct {
    akp_huffman_code_t codes[256];
    int unique_chars;
    int original_bits;
    int compressed_bits;
    double compression_ratio;
    double savings_percent;
} akp_huffman_result_t;

static inline akp_huffman_node_t* akp_huffman_create_node(char ch, int freq) {
    akp_huffman_node_t* node = (akp_huffman_node_t*)malloc(sizeof(akp_huffman_node_t));
    if (!node) return NULL;
    node->ch = ch;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static inline void akp_huffman_free_tree(akp_huffman_node_t* root) {
    if (!root) return;
    akp_huffman_free_tree(root->left);
    akp_huffman_free_tree(root->right);
    free(root);
}

static inline void akp_huffman_generate_codes(akp_huffman_node_t* root, char* prefix, int depth, akp_huffman_result_t* res) {
    if (!root) return;
    if (!root->left && !root->right) {
        prefix[depth] = '\0';
        for (int i = 0; i < res->unique_chars; i++) {
            if (res->codes[i].ch == root->ch) {
                if (depth == 0) strcpy(res->codes[i].code, "0");
                else strcpy(res->codes[i].code, prefix);
                break;
            }
        }
        return;
    }
    if (root->left) {
        prefix[depth] = '0';
        akp_huffman_generate_codes(root->left, prefix, depth + 1, res);
    }
    if (root->right) {
        prefix[depth] = '1';
        akp_huffman_generate_codes(root->right, prefix, depth + 1, res);
    }
}

static inline bool akp_huffman_encode(const char* input, akp_huffman_result_t* out_res) {
    if (!input || !out_res) return false;
    memset(out_res, 0, sizeof(akp_huffman_result_t));
    int len = (int)strlen(input);
    if (len == 0) return false;

    int freqs[256] = {0};
    for (int i = 0; i < len; i++) freqs[(unsigned char)input[i]]++;

    akp_huffman_node_t* forest[256];
    int forest_size = 0;
    for (int i = 0; i < 256; i++) {
        if (freqs[i] > 0) {
            forest[forest_size] = akp_huffman_create_node((char)i, freqs[i]);
            out_res->codes[forest_size].ch = (char)i;
            out_res->codes[forest_size].freq = freqs[i];
            forest_size++;
        }
    }
    out_res->unique_chars = forest_size;

    while (forest_size > 1) {
        int min1 = 0, min2 = 1;
        if (forest[min1]->freq > forest[min2]->freq) {
            int t = min1; min1 = min2; min2 = t;
        }
        for (int i = 2; i < forest_size; i++) {
            if (forest[i]->freq < forest[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (forest[i]->freq < forest[min2]->freq) {
                min2 = i;
            }
        }

        akp_huffman_node_t* parent = akp_huffman_create_node('$', forest[min1]->freq + forest[min2]->freq);
        parent->left = forest[min1];
        parent->right = forest[min2];

        forest[min1] = parent;
        forest[min2] = forest[forest_size - 1];
        forest_size--;
    }

    akp_huffman_node_t* root = forest[0];
    char prefix[64];
    akp_huffman_generate_codes(root, prefix, 0, out_res);
    akp_huffman_free_tree(root);

    out_res->original_bits = len * 8;
    out_res->compressed_bits = 0;
    for (int i = 0; i < out_res->unique_chars; i++) {
        out_res->compressed_bits += out_res->codes[i].freq * (int)strlen(out_res->codes[i].code);
    }
    if (out_res->original_bits > 0) {
        out_res->compression_ratio = (double)out_res->original_bits / (double)out_res->compressed_bits;
        out_res->savings_percent = ((double)(out_res->original_bits - out_res->compressed_bits) / (double)out_res->original_bits) * 100.0;
    }
    return true;
}

static inline void akp_huffman_render(const char* input, const akp_huffman_result_t* res, const char* title) {
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  📦 HUFFMAN OPTIMAL PREFIX CODING & DATA COMPRESSION ENGINE                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    if (title) printf(AKP_BOLD AKP_NEON_YELLOW "  ⚡ Dataset: %s\n" AKP_RESET, title);
    if (!res || res->unique_chars == 0) {
        printf(AKP_BOLD AKP_NEON_RED "  [ Empty dataset for Huffman encoding ]\n\n" AKP_RESET);
        return;
    }

    printf(AKP_BOLD AKP_NEON_GREEN "  Original Text: \"%s\" (Length: %zu chars)\n" AKP_RESET, input ? input : "N/A", input ? strlen(input) : 0);
    printf("  Original Size:   %d bits (%d bytes)\n", res->original_bits, res->original_bits / 8);
    printf("  Compressed Size: %d bits (%.1f bytes)\n", res->compressed_bits, (double)res->compressed_bits / 8.0);
    printf(AKP_BOLD AKP_NEON_CYAN "  Bandwidth Savings: %.2f%%  |  Ratio: %.2f:1\n\n" AKP_RESET, res->savings_percent, res->compression_ratio);

    printf(AKP_BOLD AKP_NEON_PINK "  ┌───────────┬─────────────┬───────────────────────────┐\n");
    printf("  │ Character │  Frequency  │  Generated Variable Code  │\n");
    printf("  ├───────────┼─────────────┼───────────────────────────┤\n" AKP_RESET);

    for (int i = 0; i < res->unique_chars; i++) {
        char display_c = res->codes[i].ch;
        if (display_c == ' ') printf("  │  [SPACE]  │ %11d │  ", res->codes[i].freq);
        else if (display_c == '\n') printf("  │  [NEWL]   │ %11d │  ", res->codes[i].freq);
        else printf("  │     '%c'   │ %11d │  ", display_c, res->codes[i].freq);
        printf(AKP_BOLD AKP_NEON_CYAN "%-25s" AKP_RESET, res->codes[i].code);
        printf("│\n");
    }
    printf(AKP_BOLD AKP_NEON_PINK "  └───────────┴─────────────┴───────────────────────────┘\n\n" AKP_RESET);
}

/* ============================================================================
 * 32. VISUAL LRU (LEAST RECENTLY USED) CACHE SIMULATOR
 * ============================================================================ */
typedef struct akp_lru_node {
    int key;
    int value;
    struct akp_lru_node* prev;
    struct akp_lru_node* next;
} akp_lru_node_t;

typedef struct {
    int capacity;
    int count;
    int hits;
    int misses;
    akp_lru_node_t* head;
    akp_lru_node_t* tail;
} akp_lru_cache_t;

static inline akp_lru_cache_t* akp_lru_create(int capacity) {
    if (capacity <= 0) capacity = 4;
    akp_lru_cache_t* cache = (akp_lru_cache_t*)malloc(sizeof(akp_lru_cache_t));
    if (!cache) return NULL;
    cache->capacity = capacity;
    cache->count = 0;
    cache->hits = 0;
    cache->misses = 0;
    cache->head = NULL;
    cache->tail = NULL;
    return cache;
}

static inline void akp_lru_destroy(akp_lru_cache_t* cache) {
    if (!cache) return;
    akp_lru_node_t* curr = cache->head;
    while (curr) {
        akp_lru_node_t* nxt = curr->next;
        free(curr);
        curr = nxt;
    }
    free(cache);
}

static inline void akp_lru_move_to_head(akp_lru_cache_t* cache, akp_lru_node_t* node) {
    if (!cache || !node || cache->head == node) return;
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (cache->tail == node) cache->tail = node->prev;

    node->prev = NULL;
    node->next = cache->head;
    if (cache->head) cache->head->prev = node;
    cache->head = node;
    if (!cache->tail) cache->tail = node;
}

static inline int akp_lru_get(akp_lru_cache_t* cache, int key) {
    if (!cache) return -1;
    akp_lru_node_t* curr = cache->head;
    while (curr) {
        if (curr->key == key) {
            cache->hits++;
            akp_lru_move_to_head(cache, curr);
            return curr->value;
        }
        curr = curr->next;
    }
    cache->misses++;
    return -1;
}

static inline void akp_lru_put(akp_lru_cache_t* cache, int key, int value) {
    if (!cache) return;
    akp_lru_node_t* curr = cache->head;
    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            akp_lru_move_to_head(cache, curr);
            return;
        }
        curr = curr->next;
    }

    akp_lru_node_t* new_node = (akp_lru_node_t*)malloc(sizeof(akp_lru_node_t));
    if (!new_node) return;
    new_node->key = key;
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = cache->head;

    if (cache->head) cache->head->prev = new_node;
    cache->head = new_node;
    if (!cache->tail) cache->tail = new_node;
    cache->count++;

    if (cache->count > cache->capacity) {
        akp_lru_node_t* lru = cache->tail;
        if (lru) {
            if (lru->prev) lru->prev->next = NULL;
            cache->tail = lru->prev;
            free(lru);
            cache->count--;
        }
    }
}

static inline void akp_lru_render(const akp_lru_cache_t* cache, const char* title) {
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_CYAN "╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  💾 LRU (LEAST RECENTLY USED) CACHE & BUFFER POOL TELEMETRY                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    if (title) printf(AKP_BOLD AKP_NEON_YELLOW "  ⚡ Cache Domain: %s\n" AKP_RESET, title);
    if (!cache) {
        printf(AKP_BOLD AKP_NEON_RED "  [ Cache is NULL ]\n\n" AKP_RESET);
        return;
    }

    int total_queries = cache->hits + cache->misses;
    double hit_ratio = total_queries > 0 ? ((double)cache->hits / (double)total_queries) * 100.0 : 0.0;

    printf(AKP_BOLD AKP_NEON_GREEN "  Capacity: %d | Occupancy: %d / %d | Hits: %d | Misses: %d | Hit Ratio: %.1f%%\n\n" AKP_RESET,
           cache->capacity, cache->count, cache->capacity, cache->hits, cache->misses, hit_ratio);

    printf("  Cache Line Order (MRU to LRU):\n  ");
    printf(AKP_BOLD AKP_NEON_YELLOW "[MRU / HEAD] -> " AKP_RESET);

    akp_lru_node_t* curr = cache->head;
    while (curr) {
        printf(AKP_BOLD AKP_NEON_CYAN "[K:%d | V:%d]" AKP_RESET, curr->key, curr->value);
        if (curr->next) printf(AKP_BOLD AKP_NEON_PINK " <-> " AKP_RESET);
        curr = curr->next;
    }
    printf(AKP_BOLD AKP_NEON_RED " -> [LRU / TAIL]\n\n" AKP_RESET);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_H */
