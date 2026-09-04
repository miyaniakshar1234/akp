/**
 * ============================================================================
 *  AKP ENGINE - ULTIMATE LAB DEMONSTRATION v1.1.0 (examples/lab_demo.c)
 *  Author: Akshar Miyani | AKP Studio
 *  Compile: gcc examples/lab_demo.c -I include -o lab_demo.exe
 * ============================================================================
 */

#include "akp.h"

/* Sample mathematical function for plotting */
static double sample_curve(double x) {
    return sin(x) * cos(x * 0.5) * 10.0;
}

int main(void) {
    /* 1. Print Author & Studio Splash Banner */
    akp_banner();
    akp_stamp("Advanced Data Structures & Algorithms Lab");

    /* 2. Play Audio FX */
    akp_sound_coin();

    /* 3. High-Visibility Status Logging */
    akp_log_akp("INIT", "AKP Core Runtime v1.1.0 loaded successfully.");
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
    for (int i = 1; i <= 30; i++) {
        akp_progress(i, 30, "Crunching Nodes");
#if AKP_PLATFORM_WINDOWS
        Sleep(15);
#else
        usleep(15000);
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

    /* 9. Sparklines & 2D Curve Plotter */
    double metric_history[16] = { 10.2, 14.5, 12.0, 18.9, 25.4, 22.1, 30.8, 45.2, 38.0, 52.4, 61.1, 58.7, 72.0, 68.4, 85.1, 92.3 };
    akp_sparkline(metric_history, 16, "Memory Throughput (MB/s)");
    akp_plot_curve(sample_curve, 0.0, 6.28, 45, 8, "Trigonometric Damping Signal");

    /* 10. Binary Search Tree Visualizer */
    akp_tree_node_t* root = akp_tree_create_node(50, "Root");
    root->left = akp_tree_create_node(25, "L1");
    root->right = akp_tree_create_node(75, "R1");
    root->left->left = akp_tree_create_node(10, "L2_Min");
    root->left->right = akp_tree_create_node(35, "L2_Mid");
    root->right->left = akp_tree_create_node(60, "R2_Mid");
    root->right->right = akp_tree_create_node(95, "R2_Max");
    akp_tree_print(root, "Binary Search Tree Partition");

    /* Free Tree */
    free(root->left->left); free(root->left->right);
    free(root->right->left); free(root->right->right);
    free(root->left); free(root->right); free(root);

    /* 11. Microsecond Precision Benchmark */
    AKP_BENCHMARK("Quicksort Simulation & Matrix Arithmetic") {
        volatile double sum = 0;
        for (int i = 0; i < 500000; i++) {
            sum += (i * 0.001);
        }
#if AKP_PLATFORM_WINDOWS
        Sleep(20);
#else
        usleep(20000);
#endif
    }

    /* 12. Memory Deallocation & Zero-Leak Audit */
    AKP_FREE(secret_record);
    akp_mem_report();

    /* 13. Interactive Selection Menu */
    const char* lab_options[] = {
        "Submit Evaluation to Lab Server",
        "Export Diagnostic JSON Telemetry",
        "Benchmark CPU Cache Lines",
        "Exit & Save State"
    };
    int chosen = akp_prompt_select("Choose Lab Operation", lab_options, 4);
    akp_log_success("Executing Operation #%d: %s", chosen + 1, lab_options[chosen]);

    akp_sound_success();
    akp_log_success("All tests passed with 100%% precision! Engineered by Akshar Miyani.");

    return 0;
}
