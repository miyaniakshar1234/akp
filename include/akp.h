/**
 * ============================================================================
 *   █████╗ ██╗  ██╗██████╗      ███████╗███╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗
 *  ██╔══██╗██║ ██╔╝██╔══██╗     ██╔════╝████╗  ██║██╔════╝ ██║████╗  ██║██╔════╝
 *  ███████║█████═╝ ██████╔╝     █████╗  ██╔██╗ ██║██║  ███╗██║██╔██╗ ██║█████╗  
 *  ██╔══██║██╔═██╗ ██╔═══╝      ██╔══╝  ██║╚██╗██║██║   ██║██║██║╚██╗██║██╔══╝  
 *  ██║  ██║██║ ╚██╗██║          ███████╗██║ ╚████║╚██████╔╝██║██║ ╚████║███████╗
 *  ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝          ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝
 * ============================================================================
 *  🚀 AKP CORE ENGINE v1.0.0
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

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #include <conio.h>
    #define AKP_PLATFORM_WINDOWS 1
#else
    #include <unistd.h>
    #include <termios.h>
    #include <sys/time.h>
    #define AKP_PLATFORM_WINDOWS 0
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

/* Cyberpunk Neon Palette (TrueColor 24-bit) */
#define AKP_NEON_CYAN    "\x1b[38;2;0;255;234m"
#define AKP_NEON_PINK    "\x1b[38;2;255;0;127m"
#define AKP_NEON_PURPLE  "\x1b[38;2;179;0;255m"
#define AKP_NEON_GREEN   "\x1b[38;2;57;255;20m"
#define AKP_NEON_YELLOW  "\x1b[38;2;255;231;0m"
#define AKP_GOLD         "\x1b[38;2;255;184;0m"
#define AKP_FIRE_ORANGE  "\x1b[38;2;255;94;0m"
#define AKP_DEEP_BLUE    "\x1b[38;2;0;102;255m"

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
    printf(AKP_NEON_CYAN "║" AKP_BOLD AKP_NEON_YELLOW "        🚀 AKP CORE ENGINE v1.0.0  |  ENGINEERED BY: AKSHAR MIYANI              " AKP_NEON_CYAN "║\n" AKP_RESET);
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
            } else {
                printf("   ");
            }
            if (j == 7) printf(" ");
        }
        printf(" | ");
        for (size_t j = 0; j < 16; j++) {
            if (i + j < size) {
                uint8_t b = byte_ptr[i + j];
                if (b >= 32 && b <= 126) printf(AKP_BOLD AKP_FG_WHITE "%c" AKP_RESET, b);
                else printf(AKP_DIM "." AKP_RESET);
            } else {
                printf(" ");
            }
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
    akp_timer_t t;
    t.section_name = name ? name : "Operation";
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
 * [8] AUDIO SOUND EFFECTS
 * ============================================================================ */

static inline void akp_sound_coin(void) {
#if AKP_PLATFORM_WINDOWS
    Beep(988, 100);  /* B5 */
    Beep(1319, 250); /* E6 */
#else
    printf("\a"); fflush(stdout);
#endif
}

static inline void akp_sound_success(void) {
#if AKP_PLATFORM_WINDOWS
    Beep(523, 100); Beep(659, 100); Beep(784, 150); Beep(1046, 250);
#else
    printf("\a"); fflush(stdout);
#endif
}

static inline void akp_sound_alert(void) {
#if AKP_PLATFORM_WINDOWS
    Beep(440, 200); Beep(330, 250);
#else
    printf("\a"); fflush(stdout);
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
 * [10] INTERACTIVE PROMPTS
 * ============================================================================ */

static inline bool akp_prompt_confirm(const char* question) {
    akp_init_console();
    printf(AKP_BOLD AKP_GOLD "❓ %s [y/N]: " AKP_RESET, question ? question : "Continue?");
    fflush(stdout);
#if AKP_PLATFORM_WINDOWS
    int ch = _getch();
    printf("%c\n", ch);
    return (ch == 'y' || ch == 'Y');
#else
    char buf[16];
    if (fgets(buf, sizeof(buf), stdin)) return (buf[0] == 'y' || buf[0] == 'Y');
    return false;
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
        if (ch == '\b') {
            if (idx > 0) { idx--; printf("\b \b"); fflush(stdout); }
        } else if (ch >= 32 && ch <= 126) {
            buffer[idx++] = (char)ch;
            printf(AKP_NEON_PINK "•" AKP_RESET);
            fflush(stdout);
        }
    }
    buffer[idx] = '\0';
    printf("\n");
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    while (idx < max_len - 1) {
        int ch = getchar();
        if (ch == '\r' || ch == '\n') break;
        if (ch == 127 || ch == '\b') {
            if (idx > 0) { idx--; printf("\b \b"); fflush(stdout); }
        } else if (ch >= 32 && ch <= 126) {
            buffer[idx++] = (char)ch;
            printf(AKP_NEON_PINK "•" AKP_RESET);
            fflush(stdout);
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    buffer[idx] = '\0';
    printf("\n");
#endif
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_H */
