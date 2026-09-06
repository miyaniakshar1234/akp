/**
 * ============================================================================
 * AKP ENGINE - FLASHY C/C++ TOOLKIT
 * EXAMPLE: lab_showcase_v170.c
 * Demonstrating v1.7.0 Subsystems:
 * 1. Visual Disjoint-Set Union (DSU / Union-Find)
 * 2. Visual Kruskal's Minimum Spanning Tree (MST)
 * 3. Lockless SPSC Circular Ring Buffer
 * 4. Systems Bitset & Binary Register Telemetry
 * 
 * Engineered & Authored by: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#include "akp.h"

int main(void) {
    akp_init_console();

    // 1. Academic Lab Banner & Stamp
    akp_banner();
    akp_stamp("Advanced Graph Theory & Low-Level Systems Lab Showcase v1.7.0");

    akp_log_akp("INIT", "Loaded AKP Engine v1.7.0 - 36 High-Performance Subsystems Active.");

    // 2. Demonstration: Disjoint-Set Union (DSU)
    akp_log_info("DEMO", "Initializing Disjoint-Set Union-Find (DSU) Partition Engine...");
    akp_dsu_t* dsu = akp_dsu_create(8);
    akp_dsu_union(dsu, 0, 1);
    akp_dsu_union(dsu, 1, 2);
    akp_dsu_union(dsu, 3, 4);
    akp_dsu_union(dsu, 5, 6);
    akp_dsu_union(dsu, 6, 7);
    akp_dsu_render(dsu, "Initial 3-Partition Graph Connectivity");

    akp_log_info("DSU", "Merging Component {0, 1, 2} with Component {3, 4}...");
    akp_dsu_union(dsu, 2, 3);
    akp_dsu_render(dsu, "Post-Merge Partition State");
    akp_dsu_destroy(dsu);

    // 3. Demonstration: Kruskal's Minimum Spanning Tree (MST)
    akp_log_info("DEMO", "Executing Kruskal's Greedy MST with Cycle Detection...");
    akp_graph_t* g = akp_graph_create(5, 0); // 5 vertices, undirected
    akp_graph_add_edge(g, 0, 1, 2);
    akp_graph_add_edge(g, 0, 3, 6);
    akp_graph_add_edge(g, 1, 2, 3);
    akp_graph_add_edge(g, 1, 3, 8);
    akp_graph_add_edge(g, 1, 4, 5);
    akp_graph_add_edge(g, 2, 4, 7);
    akp_graph_add_edge(g, 3, 4, 9);

    akp_kruskal_result_t mst_res;
    if (akp_kruskal_solve(g, &mst_res)) {
        akp_kruskal_render(g, &mst_res, "Campus Optical Backbone Network");
    }
    akp_graph_free(g);

    // 4. Demonstration: Lockless SPSC Circular Ring Buffer
    akp_log_info("DEMO", "Benchmarking Lockless SPSC Ring Buffer Streaming...");
    akp_ring_buf_t* rb = akp_ring_create(16);
    for (uint8_t b = 0x10; b <= 0x1A; b++) {
        akp_ring_write(rb, b);
    }
    akp_ring_render(rb, "Telemetry Streaming Ingress Queue");

    // Consume 4 bytes
    uint8_t out_val = 0;
    for (int i = 0; i < 4; i++) {
        akp_ring_read(rb, &out_val);
    }
    akp_ring_render(rb, "After Consuming 4 Bytes from Tail");
    akp_ring_destroy(rb);

    // 5. Demonstration: Systems Bitset & Binary Register Telemetry
    akp_log_info("DEMO", "Configuring 64-bit Systems Hardware Control Register...");
    akp_bitset_t* bs = akp_bitset_create(64);
    akp_bitset_set(bs, 0);  // Enable bit
    akp_bitset_set(bs, 3);  // Interrupt enable
    akp_bitset_set(bs, 7);  // DMA channel active
    akp_bitset_set(bs, 15); // Cache write-through
    akp_bitset_set(bs, 31); // 32-bit boundary flag
    akp_bitset_set(bs, 63); // Sign / MSB flag
    akp_bitset_render(bs, "CPU Control Register CR0");
    akp_bitset_destroy(bs);

    // 6. Zero-Leak Heap Memory Audit
    void* audit_ptr = AKP_MALLOC(1024);
    AKP_FREE(audit_ptr);
    akp_mem_report();

    akp_log_akp("DONE", "AKP Engine v1.7.0 Demonstration Finished. 100%% Silent, Zero Leaks.");
    return 0;
}
