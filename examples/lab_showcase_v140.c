/**
 * ============================================================================
 *  AKP ENGINE v1.4.0 - ADVANCED LAB SHOWCASE (examples/lab_showcase_v140.c)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Demonstrates Visual Stack, Circular Queue, Binary Search, Graph,
 *           Terminal Themes & 100% Silent Execution in College Computer Labs.
 * ============================================================================
 */

#include "akp.h"

int main(void) {
    /* 1. Splash Banner & Official Evaluation Stamp */
    akp_banner();
    akp_stamp("Advanced Systems & Algorithms: v1.4.0 Showcase");

    akp_log_akp("INIT", "AKP Core Engine v1.4.0 loaded with Silent Audio Mode.");
    akp_log_info("Hardware Speaker Beeps: SILENCED (0dB) for quiet lab compliance.");

    /* 2. Terminal Theme Previews */
    printf("\n" AKP_BOLD AKP_NEON_YELLOW "--- [1] TERMINAL COLOR THEMES ENGINE ---" AKP_RESET "\n");
    akp_theme_preview(AKP_THEME_CYBERPUNK);
    akp_theme_preview(AKP_THEME_MATRIX);
    akp_theme_preview(AKP_THEME_SYNTHWAVE);
    akp_theme_preview(AKP_THEME_DRACULA);

    /* 3. Visual LIFO Stack Demo */
    printf("\n" AKP_BOLD AKP_NEON_YELLOW "--- [2] VISUAL LIFO STACK DEMONSTRATION ---" AKP_RESET "\n");
    akp_stack_t* stack = akp_stack_create(5, "CallStack_Register");
    akp_log_info("Pushing 3 registers onto LIFO stack...");
    akp_stack_push(stack, 1024);
    akp_stack_push(stack, 2048);
    akp_stack_push(stack, 4096);
    akp_stack_render(stack);

    int popped = 0;
    akp_stack_pop(stack, &popped);
    akp_log_success("Popped TOP element: %d", popped);
    akp_stack_render(stack);
    akp_stack_free(stack);

    /* 4. Visual Circular Queue Demo */
    printf("\n" AKP_BOLD AKP_NEON_YELLOW "--- [3] VISUAL CIRCULAR FIFO QUEUE DEMONSTRATION ---" AKP_RESET "\n");
    akp_queue_t* queue = akp_queue_create(5, "PacketScheduler");
    akp_log_info("Enqueuing 4 network packets...");
    akp_queue_enqueue(queue, 100);
    akp_queue_enqueue(queue, 200);
    akp_queue_enqueue(queue, 300);
    akp_queue_enqueue(queue, 400);
    akp_queue_render(queue);

    int deq = 0;
    akp_queue_dequeue(queue, &deq);
    akp_log_success("Dequeued FRONT packet: %d", deq);
    akp_queue_render(queue);
    akp_queue_free(queue);

    /* 5. Step-by-Step Visual Binary Search */
    printf("\n" AKP_BOLD AKP_NEON_YELLOW "--- [4] STEP-BY-STEP VISUAL BINARY SEARCH ---" AKP_RESET "\n");
    int sorted_data[] = {5, 12, 19, 28, 37, 46, 55, 64, 73, 82, 91};
    int n = sizeof(sorted_data) / sizeof(sorted_data[0]);
    int target = 64;
    akp_search_binary(sorted_data, n, target);

    /* 6. Graph Topology & Breadth-First Search */
    printf(AKP_BOLD AKP_NEON_YELLOW "--- [5] GRAPH ADJACENCY MATRIX & BFS TRAVERSAL ---" AKP_RESET "\n");
    akp_graph_t* g = akp_graph_create(5, 0); /* 5 vertices, undirected */
    akp_graph_add_edge(g, 0, 1, 10);
    akp_graph_add_edge(g, 0, 4, 20);
    akp_graph_add_edge(g, 1, 2, 30);
    akp_graph_add_edge(g, 1, 3, 40);
    akp_graph_add_edge(g, 2, 3, 50);
    akp_graph_add_edge(g, 3, 4, 60);

    akp_graph_render_adj_matrix(g, "Lab Network Graph");
    akp_graph_bfs(g, 0);
    akp_graph_free(g);

    /* 7. Conclusion */
    akp_log_success("AKP v1.4.0 showcase completed with 100%% precision & ZERO noise!");
    akp_log_info("Engineered by Akshar Miyani | AKP Studio");

    return 0;
}
