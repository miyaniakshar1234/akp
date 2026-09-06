/**
 * ============================================================================
 *  AKP ENGINE - FLASHY MICRO UNIT-TESTING FRAMEWORK (akp/test.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_TEST_H
#define AKP_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"
#include "badge.h"
#include "timer.h"
#include "sound.h"

typedef struct {
    int total_tests;
    int passed_tests;
    int failed_tests;
    const char* suite_name;
    akp_timer_t timer;
} akp_test_suite_t;

static inline akp_test_suite_t akp_test_suite_begin(const char* name) {
    akp_init_console();
    akp_test_suite_t s;
    s.total_tests = 0;
    s.passed_tests = 0;
    s.failed_tests = 0;
    s.suite_name = name ? name : "AKP Test Suite";
    s.timer = akp_timer_start(s.suite_name);

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
    printf("║  Pass Rate:    " AKP_BOLD "%s%-6.1f%%" AKP_RESET "                                    ║\n", 
           (s->failed_tests == 0 ? AKP_NEON_GREEN : AKP_FG_RED), pass_rate);
    printf(AKP_BOLD AKP_NEON_PURPLE "╚═══════════════════════════════════════════════════════════════╝\n" AKP_RESET);

    if (s->failed_tests == 0 && s->total_tests > 0) {
        printf(AKP_BOLD AKP_NEON_GREEN "✨ ALL TESTS PASSED! Engineered by Akshar Miyani.\n\n" AKP_RESET);
        akp_sound_success();
        return 0;
    } else {
        printf(AKP_BOLD AKP_FG_RED "⚠️ SOME TESTS FAILED! Review assertions above.\n\n" AKP_RESET);
        akp_sound_alert();
        return s->failed_tests;
    }
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_TEST_H */
