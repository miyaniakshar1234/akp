/**
 * ============================================================================
 *  AKP ENGINE - HIGH-PRECISION MICRO-BENCHMARK TIMER (akp/timer.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_TIMER_H
#define AKP_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"
#include "badge.h"

typedef struct {
#if AKP_OS_WIN
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
#if AKP_OS_WIN
    QueryPerformanceFrequency(&t.frequency);
    QueryPerformanceCounter(&t.start_time);
#else
    clock_gettime(CLOCK_MONOTONIC, &t.start_time);
#endif
    return t;
}

static inline double akp_timer_stop_ms(akp_timer_t* t) {
#if AKP_OS_WIN
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

#ifdef __cplusplus
}
#endif

#endif /* AKP_TIMER_H */
