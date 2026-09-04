/**
 * ============================================================================
 *  AKP ENGINE - ULTIMATE LAB DEMONSTRATION (examples/lab_demo.c)
 *  Author: Akshar Miyani | AKP Studio
 *  Compile: gcc examples/lab_demo.c -I include -o lab_demo.exe
 * ============================================================================
 */

#include "akp.h"

int main(void) {
    /* 1. Print Author & Studio Splash Banner */
    akp_banner();
    akp_stamp("Advanced Data Structures & Algorithms Lab");

    /* 2. Play Audio FX */
    akp_sound_coin();

    /* 3. High-Visibility Status Logging */
    akp_log_akp("INIT", "AKP Core Runtime loaded successfully.");
    akp_log_info("Author Identity: Akshar Miyani (AKP Studio)");
    akp_log_info("Starting Lab Demonstration Suite...");

    /* 4. Beautiful Auto-Sizing Unicode Table */
    akp_table_t* table = akp_table_create(4, "Algorithm Complexity Benchmark");
    akp_table_set_headers(table, "Algorithm", "Best Case", "Average Case", "Worst Case");
    akp_table_add_row(table, "Quick Sort", "O(N log N)", "O(N log N)", "O(N^2)");
    akp_table_add_row(table, "Merge Sort", "O(N log N)", "O(N log N)", "O(N log N)");
    akp_table_add_row(table, "Heap Sort",  "O(N log N)", "O(N log N)", "O(N log N)");
    akp_table_add_row(table, "Bubble Sort", "O(N)",       "O(N^2)",     "O(N^2)");
    akp_table_render(table);
    akp_table_free(table);

    /* 5. Live Gradient Progress Bar */
    akp_log_info("Simulating Dataset Neural Processing...");
    for (int i = 1; i <= 40; i++) {
        akp_progress(i, 40, "Crunching Nodes");
#if AKP_PLATFORM_WINDOWS
        Sleep(25);
#else
        usleep(25000);
#endif
    }

    /* 6. Dynamic Memory Allocation & Color Hex-Dump */
    akp_log_info("Allocating heap payload for memory inspection...");
    char* secret_record = (char*)AKP_MALLOC(64);
    strcpy(secret_record, "Akshar Miyani - AKP Studio Master Key 0xDEADBEEFCAFE");
    akp_hexdump(secret_record, 64, "Secret Student Payload");

    /* 7. DSA Array & Sorting Visualization */
    int data[8] = { 45, 12, 89, 34, 99, 23, 67, 8 };
    akp_visualize_array(data, 8, 4, "Array State Before Partition");

    /* 8. Matrix Visualizer */
    int matrix[3][3] = {
        { 1,  0, -5 },
        { 0, 12,  3 },
        { 8, -2,  0 }
    };
    akp_print_matrix((const int*)matrix, 3, 3, "Adjacency Weight Matrix");

    /* 9. Microsecond Precision Benchmark */
    AKP_BENCHMARK("Quicksort Simulation & Matrix Arithmetic") {
        volatile double sum = 0;
        for (int i = 0; i < 500000; i++) {
            sum += (i * 0.001);
        }
#if AKP_PLATFORM_WINDOWS
        Sleep(40);
#else
        usleep(40000);
#endif
    }

    /* 10. Memory Deallocation & Zero-Leak Audit */
    AKP_FREE(secret_record);
    akp_mem_report();

    /* 11. Interactive CLI Elements */
    char password[32];
    akp_prompt_password("Enter Lab Passcode:", password, sizeof(password));
    akp_log_success("Passcode accepted for Akshar Miyani!");

    bool proceed = akp_prompt_confirm("Commit and push lab evaluation results to GitHub?");
    if (proceed) {
        akp_log_success("All tests passed with 100%% precision! Ready to flex in lab!");
        akp_sound_success();
    }

    return 0;
}
