/**
 * ============================================================================
 *  AKP ENGINE - COMPREHENSIVE AUTOMATED TEST SUITE (tests/test_suite.c)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#include "akp.h"

int main(void) {
    akp_banner();
    akp_test_suite_t suite = akp_test_suite_begin("AKP Subsystem Integrity Validation");

    /* Test 1: Hex color parser */
    akp_rgb_t cyan = akp_hex(0x00FFEAu);
    AKP_ASSERT_EQ(suite, "Color: Hex Parse Red Component", cyan.r, 0x00);
    AKP_ASSERT_EQ(suite, "Color: Hex Parse Green Component", cyan.g, 0xFF);
    AKP_ASSERT_EQ(suite, "Color: Hex Parse Blue Component", cyan.b, 0xEA);

    /* Test 2: Memory Heap Auditor */
    size_t before_alloc = g_akp_allocated_bytes;
    int* mem = (int*)AKP_MALLOC(128);
    AKP_TEST(suite, "Memory: Pointer Allocation", mem != NULL);
    AKP_ASSERT_EQ(suite, "Memory: Allocation Byte Tracking", g_akp_allocated_bytes, before_alloc + 128);
    AKP_FREE(mem);
    AKP_ASSERT_EQ(suite, "Memory: Zero-Leak Deallocation", g_akp_allocated_bytes, before_alloc);

    /* Test 3: Table Creation & Col Constraints */
    akp_table_t* t = akp_table_create(3, "Test Table");
    AKP_TEST(suite, "Table: Instance Creation", t != NULL);
    akp_table_set_headers(t, "ID", "Name", "Score");
    akp_table_add_row(t, "101", "Akshar Miyani", "100.0");
    AKP_ASSERT_EQ(suite, "Table: Row Count", t->rows, 1);
    AKP_ASSERT_STR_EQ(suite, "Table: Cell Value Check", t->cells[0][1], "Akshar Miyani");
    akp_table_free(t);

    /* Test 4: Binary Tree Node Allocation */
    akp_tree_node_t* root = akp_tree_create_node(42, "Root");
    AKP_TEST(suite, "Tree: Node Creation", root != NULL);
    AKP_ASSERT_EQ(suite, "Tree: Node Value Verification", root->value, 42);
    AKP_ASSERT_STR_EQ(suite, "Tree: Node Label Verification", root->label, "Root");
    free(root);

    /* Test 5: 2D Geometric Canvas */
    akp_canvas_t* canvas = akp_canvas_create(20, 10);
    AKP_TEST(suite, "Canvas: Buffer Allocation", canvas != NULL);
    akp_canvas_draw_rect(canvas, 2, 2, 10, 5, '#', cyan);
    AKP_ASSERT_EQ(suite, "Canvas: Pixel Inspection (Corner)", canvas->buffer[2 * 20 + 2].ch, '#');
    akp_canvas_free(canvas);

    /* Test 6: High-Precision Benchmark Timer */
    akp_timer_t timer = akp_timer_start("Timer Precision Test");
#if AKP_PLATFORM_WINDOWS
    Sleep(10);
#else
    usleep(10000);
#endif
    double elapsed = akp_timer_stop_ms(&timer);
    AKP_TEST(suite, "Timer: Monotonic Elapsed Duration (>5ms)", elapsed >= 5.0);

    /* Test 7: Matrix Math & Multiplication */
    akp_mat_t* m1 = akp_mat_create(2, 2);
    akp_mat_t* m2 = akp_mat_create(2, 2);
    akp_mat_set(m1, 0, 0, 1.0); akp_mat_set(m1, 1, 1, 1.0); /* Identity */
    akp_mat_set(m2, 0, 0, 5.0); akp_mat_set(m2, 0, 1, 3.0);
    akp_mat_set(m2, 1, 0, 2.0); akp_mat_set(m2, 1, 1, 4.0);
    akp_mat_t* m3 = akp_mat_multiply(m1, m2);
    AKP_TEST(suite, "Matrix: Multiplication Instance", m3 != NULL);
    AKP_ASSERT_EQ(suite, "Matrix: Multiplication Result [0,0]", (int)akp_mat_get(m3, 0, 0), 5);
    AKP_ASSERT_EQ(suite, "Matrix: Multiplication Result [1,1]", (int)akp_mat_get(m3, 1, 1), 4);
    akp_mat_free(m1); akp_mat_free(m2); akp_mat_free(m3);

    /* Test 8: Hardware Telemetry */
    akp_sysinfo_t sys = akp_sysinfo_get();
    AKP_TEST(suite, "SysInfo: Physical RAM Detection", sys.total_ram_mb > 0);
    AKP_TEST(suite, "SysInfo: CPU Core Count Detection", sys.cpu_cores > 0);

    /* Test 9: Visual LIFO Stack */
    akp_stack_t* stack = akp_stack_create(4, "TestStack");
    AKP_TEST(suite, "Stack: Instance Created", stack != NULL);
    akp_stack_push(stack, 42);
    akp_stack_push(stack, 99);
    int popped_val = 0;
    akp_stack_pop(stack, &popped_val);
    AKP_ASSERT_EQ(suite, "Stack: LIFO Popped Value (99)", popped_val, 99);
    AKP_ASSERT_EQ(suite, "Stack: Remaining Top Index (0)", stack->top, 0);
    akp_stack_free(stack);

    /* Test 10: Visual Circular Queue */
    akp_queue_t* queue = akp_queue_create(4, "TestQueue");
    AKP_TEST(suite, "Queue: Instance Created", queue != NULL);
    akp_queue_enqueue(queue, 10);
    akp_queue_enqueue(queue, 20);
    int deq_val = 0;
    akp_queue_dequeue(queue, &deq_val);
    AKP_ASSERT_EQ(suite, "Queue: FIFO Dequeued Value (10)", deq_val, 10);
    AKP_ASSERT_EQ(suite, "Queue: Remaining Size (1)", queue->size, 1);
    akp_queue_free(queue);

    /* Test 11: Linear & Binary Search */
    int search_arr[] = {12, 24, 36, 48, 60, 72, 84};
    int lin_idx = akp_search_linear(search_arr, 7, 48);
    int bin_idx = akp_search_binary(search_arr, 7, 72);
    AKP_ASSERT_EQ(suite, "Search: Linear Search Index for 48", lin_idx, 3);
    AKP_ASSERT_EQ(suite, "Search: Binary Search Index for 72", bin_idx, 5);

    /* Test 12: Graph Topology */
    akp_graph_t* g = akp_graph_create(4, 0);
    akp_graph_add_edge(g, 0, 1, 5);
    akp_graph_add_edge(g, 1, 2, 8);
    AKP_TEST(suite, "Graph: Undirected Symmetry Edge [0,1]", g->adj[0][1] == 5 && g->adj[1][0] == 5);
    AKP_ASSERT_EQ(suite, "Graph: Edge Weight [1,2]", g->adj[1][2], 8);
    akp_graph_free(g);

    /* Test 13: Terminal Themes */
    akp_theme_t t_dracula = akp_theme_get(AKP_THEME_DRACULA);
    AKP_TEST(suite, "Theme: Dracula Primary Purple Non-Zero", t_dracula.primary.r > 0 && t_dracula.primary.b > 0);

    /* End Suite & Summary */
    return akp_test_suite_end(&suite);
}
