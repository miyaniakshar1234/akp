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

    /* End Suite & Summary */
    return akp_test_suite_end(&suite);
}
