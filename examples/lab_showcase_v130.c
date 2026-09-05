/**
 * ============================================================================
 *  AKP ENGINE - ULTIMATE LAB SHOWCASE v1.3.0 (examples/lab_showcase_v130.c)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#include "akp.h"

int main(void) {
    /* 1. Header Splash Banner */
    akp_banner();
    akp_stamp("Advanced Systems & Algorithms Showcase v1.3.0");

    /* 2. Hardware Telemetry Dashboard */
    akp_sysinfo_render();

    /* 3. Retro 8-Bit Melody */
    akp_melody_tetris();

    /* 4. Live Terminal Sorting Animation */
    int sort_demo[6] = { 85, 23, 64, 12, 99, 41 };
    akp_animate_sort(sort_demo, 6, AKP_ANIM_BUBBLE, 40);

    /* 5. Matrix Math Operations */
    akp_mat_t* A = akp_mat_create(2, 2);
    akp_mat_t* B = akp_mat_create(2, 2);
    akp_mat_set(A, 0, 0, 3.0); akp_mat_set(A, 0, 1, -1.0);
    akp_mat_set(A, 1, 0, 2.0); akp_mat_set(A, 1, 1, 4.0);

    akp_mat_set(B, 0, 0, 2.0); akp_mat_set(B, 0, 1, 5.0);
    akp_mat_set(B, 1, 0, -3.0); akp_mat_set(B, 1, 1, 1.0);

    akp_mat_t* C = akp_mat_multiply(A, B);
    akp_mat_render(A, "Matrix A");
    akp_mat_render(B, "Matrix B");
    akp_mat_render(C, "Matrix Product (A x B)");

    akp_mat_free(A);
    akp_mat_free(B);
    akp_mat_free(C);

    /* 6. Conclusion */
    akp_log_success("AKP Engine v1.3.0 Demonstration completed! Engineered by Akshar Miyani.");

    return 0;
}
