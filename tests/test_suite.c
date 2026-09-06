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

    /* Test 14: Hash Table (Chaining & Collisions) */
    akp_ht_t* ht = akp_ht_create(4, "TestHashTable");
    AKP_TEST(suite, "HashTable: Instance Created", ht != NULL);
    akp_ht_insert(ht, 10, 100);
    akp_ht_insert(ht, 14, 140); /* 10 % 4 == 2, 14 % 4 == 2 -> collision */
    int ht_val = 0;
    int ht_found = akp_ht_search(ht, 14, &ht_val);
    AKP_TEST(suite, "HashTable: Key 14 Search Success", ht_found == 1);
    AKP_ASSERT_EQ(suite, "HashTable: Key 14 Value Check", ht_val, 140);
    AKP_TEST(suite, "HashTable: Collision Detection (>0)", ht->collisions > 0);
    akp_ht_free(ht);

    /* Test 15: Singly Linked List */
    akp_slist_t* slist = akp_slist_create("TestSList");
    AKP_TEST(suite, "SList: Instance Created", slist != NULL);
    akp_slist_insert_head(slist, 50);
    akp_slist_insert_tail(slist, 100);
    AKP_ASSERT_EQ(suite, "SList: Size Check (2)", slist->size, 2);
    int sdel = akp_slist_delete(slist, 50);
    AKP_TEST(suite, "SList: Delete Head Element (50)", sdel == 1 && slist->head->data == 100);
    akp_slist_free(slist);

    /* Test 16: Doubly Linked List */
    akp_dlist_t* dlist = akp_dlist_create("TestDList");
    AKP_TEST(suite, "DList: Instance Created", dlist != NULL);
    akp_dlist_insert_tail(dlist, 10);
    akp_dlist_insert_tail(dlist, 20);
    AKP_ASSERT_EQ(suite, "DList: Tail Node Value (20)", dlist->tail->data, 20);
    AKP_TEST(suite, "DList: Doubly Linked Pointers Non-Null", dlist->tail->prev == dlist->head);
    akp_dlist_free(dlist);

    /* Test 17: Dijkstra Shortest Path */
    akp_graph_t* dg = akp_graph_create(4, 0);
    akp_graph_add_edge(dg, 0, 1, 4);
    akp_graph_add_edge(dg, 0, 2, 1);
    akp_graph_add_edge(dg, 2, 1, 2);
    akp_graph_add_edge(dg, 1, 3, 1);
    akp_dijkstra_t dres = akp_dijkstra_solve(dg, 0);
    AKP_ASSERT_EQ(suite, "Dijkstra: Shortest Path to V1 (via V2: 3)", dres.dist[1], 3);
    AKP_ASSERT_EQ(suite, "Dijkstra: Shortest Path to V3 (4)", dres.dist[3], 4);
    akp_graph_free(dg);

    /* Test 18: String Pattern Matching (KMP & Naive) */
    const char* text_str = "ABABDABACDABABCABAB";
    const char* pat_str  = "ABABCABAB";
    int naive_idx = akp_search_naive_pattern(text_str, pat_str);
    int kmp_idx   = akp_search_kmp(text_str, pat_str);
    AKP_ASSERT_EQ(suite, "Pattern: Naive Match Index (10)", naive_idx, 10);
    AKP_ASSERT_EQ(suite, "Pattern: KMP Match Index (10)", kmp_idx, 10);

    /* Test 19: Min-Heap & Priority Queue */
    akp_min_heap_t* h = akp_min_heap_create(8, "TestHeap");
    AKP_ASSERT_TRUE(suite, "MinHeap: Created Successfully", h != NULL);
    akp_min_heap_insert(h, 50);
    akp_min_heap_insert(h, 20);
    akp_min_heap_insert(h, 10);
    akp_min_heap_insert(h, 30);
    AKP_ASSERT_EQ(suite, "MinHeap: Peek Root Value (10)", akp_min_heap_peek(h), 10);
    int ext_min = 0;
    akp_min_heap_extract_min(h, &ext_min);
    AKP_ASSERT_EQ(suite, "MinHeap: Extracted Min Value (10)", ext_min, 10);
    AKP_ASSERT_EQ(suite, "MinHeap: New Root Value After Heapify (20)", akp_min_heap_peek(h), 20);
    akp_min_heap_destroy(h);

    /* Test 20: Prefix Tree (Trie) */
    akp_trie_t* tr = akp_trie_create();
    AKP_ASSERT_TRUE(suite, "Trie: Created Successfully", tr != NULL);
    akp_trie_insert(tr, "cat");
    akp_trie_insert(tr, "car");
    akp_trie_insert(tr, "cart");
    AKP_ASSERT_TRUE(suite, "Trie: Search Existing Word 'car'", akp_trie_search(tr, "car"));
    AKP_ASSERT_TRUE(suite, "Trie: Search Non-Existing Word 'card'", !akp_trie_search(tr, "card"));
    AKP_ASSERT_TRUE(suite, "Trie: Prefix Check 'ca'", akp_trie_starts_with(tr, "ca"));
    akp_trie_destroy(tr);

    /* Test 21: Huffman Coding & Compression */
    akp_huffman_result_t hres;
    bool h_ok = akp_huffman_encode("AAAAABBBCCDD", &hres);
    AKP_ASSERT_TRUE(suite, "Huffman: Encode Successful", h_ok);
    AKP_ASSERT_EQ(suite, "Huffman: Unique Characters Count (4)", hres.unique_chars, 4);
    AKP_ASSERT_TRUE(suite, "Huffman: Compression Reduced Bits", hres.compressed_bits < hres.original_bits);
    AKP_ASSERT_TRUE(suite, "Huffman: Positive Savings Ratio", hres.savings_percent > 0.0);

    /* Test 22: LRU Cache Simulator */
    akp_lru_cache_t* lru = akp_lru_create(2);
    AKP_ASSERT_TRUE(suite, "LRU: Created Successfully", lru != NULL);
    akp_lru_put(lru, 1, 100);
    akp_lru_put(lru, 2, 200);
    AKP_ASSERT_EQ(suite, "LRU: Cache Get Key 1 (100)", akp_lru_get(lru, 1), 100);
    akp_lru_put(lru, 3, 300); /* Evicts Key 2 */
    AKP_ASSERT_EQ(suite, "LRU: Cache Get Evicted Key 2 (-1)", akp_lru_get(lru, 2), -1);
    AKP_ASSERT_EQ(suite, "LRU: Cache Get Key 3 (300)", akp_lru_get(lru, 3), 300);
    akp_lru_destroy(lru);

    /* Test 23: Disjoint-Set Union (DSU) */
    akp_dsu_t* dsu = akp_dsu_create(6);
    AKP_ASSERT_TRUE(suite, "DSU: Created Successfully", dsu != NULL);
    akp_dsu_union(dsu, 0, 1);
    akp_dsu_union(dsu, 1, 2);
    AKP_ASSERT_TRUE(suite, "DSU: Connected (0, 2) in Same Set", akp_dsu_connected(dsu, 0, 2));
    AKP_ASSERT_TRUE(suite, "DSU: Disconnected (0, 3) in Different Sets", !akp_dsu_connected(dsu, 0, 3));
    AKP_ASSERT_EQ(suite, "DSU: Total Sets Remaining (4)", dsu->num_sets, 4);
    akp_dsu_destroy(dsu);

    /* Test 24: Kruskal's Minimum Spanning Tree */
    akp_graph_t* kg = akp_graph_create(4, 0);
    akp_graph_add_edge(kg, 0, 1, 1);
    akp_graph_add_edge(kg, 1, 2, 2);
    akp_graph_add_edge(kg, 2, 3, 3);
    akp_graph_add_edge(kg, 0, 3, 10); // cycle causing heavy edge
    akp_kruskal_result_t kres;
    bool k_ok = akp_kruskal_solve(kg, &kres);
    AKP_ASSERT_TRUE(suite, "Kruskal: MST Solved Successfully", k_ok);
    AKP_ASSERT_EQ(suite, "Kruskal: MST Edge Count (3)", kres.mst_edge_count, 3);
    AKP_ASSERT_EQ(suite, "Kruskal: Total Minimal Weight (6)", kres.total_mst_weight, 6);
    AKP_ASSERT_EQ(suite, "Kruskal: Cycles Rejected Count (1)", kres.cycles_rejected, 1);
    akp_graph_free(kg);

    /* Test 25: Lockless Ring Buffer */
    akp_ring_buf_t* rb = akp_ring_create(8);
    AKP_ASSERT_TRUE(suite, "RingBuffer: Created Successfully", rb != NULL);
    akp_ring_write(rb, 0xAA);
    akp_ring_write(rb, 0xBB);
    akp_ring_write(rb, 0xCC);
    AKP_ASSERT_EQ(suite, "RingBuffer: Available Count (3)", akp_ring_available(rb), 3);
    uint8_t read_b = 0;
    akp_ring_read(rb, &read_b);
    AKP_ASSERT_EQ(suite, "RingBuffer: Read First Byte (0xAA)", read_b, 0xAA);
    AKP_ASSERT_EQ(suite, "RingBuffer: Remaining Available (2)", akp_ring_available(rb), 2);
    akp_ring_destroy(rb);

    /* Test 26: Systems Bitset */
    akp_bitset_t* bs = akp_bitset_create(64);
    AKP_ASSERT_TRUE(suite, "Bitset: Created Successfully", bs != NULL);
    akp_bitset_set(bs, 0);
    akp_bitset_set(bs, 7);
    akp_bitset_set(bs, 63);
    AKP_ASSERT_TRUE(suite, "Bitset: Test Bit 0 (Set)", akp_bitset_test(bs, 0));
    AKP_ASSERT_TRUE(suite, "Bitset: Test Bit 1 (Clear)", !akp_bitset_test(bs, 1));
    AKP_ASSERT_TRUE(suite, "Bitset: Test Bit 63 (Set)", akp_bitset_test(bs, 63));
    AKP_ASSERT_EQ(suite, "Bitset: Hamming Weight / Popcount (3)", akp_bitset_count(bs), 3);
    akp_bitset_flip(bs, 0);
    AKP_ASSERT_EQ(suite, "Bitset: Popcount After Flip (2)", akp_bitset_count(bs), 2);
    akp_bitset_destroy(bs);

    /* End Suite & Summary */
    return akp_test_suite_end(&suite);
}
