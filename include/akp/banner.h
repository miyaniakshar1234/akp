/**
 * ============================================================================
 *  AKP ENGINE - BRANDING & BANNER MODULE (akp/banner.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_BANNER_H
#define AKP_BANNER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

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

#ifdef __cplusplus
}
#endif

#endif /* AKP_BANNER_H */
