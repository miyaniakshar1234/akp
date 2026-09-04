/**
 * ============================================================================
 *  AKP ENGINE - STATUS BADGES & LOGGING MODULE (akp/badge.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_BADGE_H
#define AKP_BADGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"
#include <stdarg.h>
#include <time.h>

static inline void akp_timestamp(char* buffer, size_t max_len) {
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
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

static inline void akp_log_crit(const char* fmt, ...) {
    char t[16]; akp_timestamp(t, sizeof(t));
    printf(AKP_DIM "[%s] " AKP_RESET AKP_BOLD AKP_BG_RED AKP_FG_WHITE " [ 💥 CRITICAL ] " AKP_RESET " ", t);
    va_list args; va_start(args, fmt); vprintf(fmt, args); va_end(args);
    printf("\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_BADGE_H */
