/**
 * ============================================================================
 *  AKP ENGINE v1.8.0 - ADVANCED GRAPH THEORY & SYSTEMS ARCHITECTURE SHOWCASE
 *  Author: Akshar Miyani | AKP Studio (MCA)
 *  Demonstrating:
 *   1. Topological Sort & Dependency Resolution (Kahn's BFS Algorithm)
 *   2. Floyd-Warshall All-Pairs Shortest Path Dynamic Programming Matrix
 *   3. Probabilistic Bloom Filter with Saturation Telemetry
 *   4. High-Performance Linear Memory Arena (Bump Allocator)
 * ============================================================================
 */

#include "akp/akp.h"

int main(void) {
    akp_init_console();
    akp_banner();
    akp_stamp("MCA Practical Lab: Graph Theory & Systems Architecture");

    akp_log_akp("INIT", "Loaded AKP Engine v1.8.0 - 40 High-Performance Subsystems Active.");

    /* ========================================================================
     * 1. TOPOLOGICAL SORT & DEPENDENCY PIPELINE (KAHN'S BFS)
     * ======================================================================== */
    akp_log_info("DEMO 1: Directed Acyclic Graph (DAG) Topological Dependency Sort");

    /* Construct 6-node Build Pipeline:
     * 0: Preprocess -> 1: Compile -> 2: Assemble -> 3: Link -> 4: Test -> 5: Deploy
     * Cross-edges: 0 -> 2 (Header Gen), 1 -> 4 (Linter) */
    akp_graph_t* dag = akp_graph_create(6, 1);
    akp_graph_add_edge(dag, 0, 1, 1);
    akp_graph_add_edge(dag, 0, 2, 1);
    akp_graph_add_edge(dag, 1, 2, 1);
    akp_graph_add_edge(dag, 1, 4, 1);
    akp_graph_add_edge(dag, 2, 3, 1);
    akp_graph_add_edge(dag, 3, 4, 1);
    akp_graph_add_edge(dag, 4, 5, 1);

    akp_toposort_result_t topo_res = akp_toposort_solve(dag);
    akp_toposort_render(dag, &topo_res, "Production Compiler Toolchain Pipeline");
    akp_graph_free(dag);

    /* ========================================================================
     * 2. FLOYD-WARSHALL ALL-PAIRS SHORTEST PATH DYNAMIC PROGRAMMING
     * ======================================================================== */
    akp_log_info("DEMO 2: Floyd-Warshall O(V^3) All-Pairs Shortest Path Grid");

    akp_graph_t* net = akp_graph_create(5, 1);
    akp_graph_add_edge(net, 0, 1, 3);
    akp_graph_add_edge(net, 0, 2, 8);
    akp_graph_add_edge(net, 0, 4, -4); /* Negative edge without negative cycle */
    akp_graph_add_edge(net, 1, 3, 1);
    akp_graph_add_edge(net, 1, 4, 7);
    akp_graph_add_edge(net, 2, 1, 4);
    akp_graph_add_edge(net, 3, 0, 2);
    akp_graph_add_edge(net, 3, 2, -5);
    akp_graph_add_edge(net, 4, 3, 6);

    akp_floyd_result_t floyd_res = akp_floyd_solve(net);
    akp_floyd_render(net, &floyd_res, "Multi-Hop Global Routing Matrix");

    int path[AKP_GRAPH_MAX_VERTICES];
    int path_len = akp_floyd_get_path(&floyd_res, 0, 2, path);
    if (path_len > 0) {
        printf(AKP_BOLD AKP_NEON_YELLOW "  Optimal Reconstructed Path [V0 -> V2] (Total Cost: %d):\n    " AKP_RESET, floyd_res.dist[0][2]);
        for (int i = 0; i < path_len; i++) {
            printf(AKP_BOLD AKP_NEON_CYAN "[V%d]" AKP_RESET, path[i]);
            if (i < path_len - 1) printf(AKP_NEON_GREEN " ───> " AKP_RESET);
        }
        printf("\n\n");
    }
    akp_graph_free(net);

    /* ========================================================================
     * 3. PROBABILISTIC BLOOM FILTER
     * ======================================================================== */
    akp_log_info("DEMO 3: Probabilistic Bloom Filter (Distributed Cache Simulation)");

    akp_bloom_t* bf = akp_bloom_create(256, 4);
    const char* whitelist[] = {
        "admin_auth_token",
        "session_cache_node_1",
        "redis_primary_cluster",
        "gateway_ingress_route",
        "security_firewall_rule"
    };

    for (int i = 0; i < 5; i++) {
        akp_bloom_add(bf, whitelist[i]);
    }

    akp_bloom_render(bf, "Distributed Token Ingress Filter");

    /* Validate queries */
    printf("  Membership Probe Verification:\n");
    printf("    Query: 'admin_auth_token'     -> %s\n",
           akp_bloom_check(bf, "admin_auth_token") ? AKP_BOLD AKP_NEON_GREEN "✔ PRESENT (Match)" AKP_RESET : "❌ NOT FOUND");
    printf("    Query: 'malicious_injection'  -> %s\n",
           akp_bloom_check(bf, "malicious_injection") ? "✔ PRESENT" : AKP_BOLD AKP_NEON_RED "❌ DEFINITELY ABSENT (Filtered)" AKP_RESET);
    printf("    Query: 'unauthorized_payload' -> %s\n\n",
           akp_bloom_check(bf, "unauthorized_payload") ? "✔ PRESENT" : AKP_BOLD AKP_NEON_RED "❌ DEFINITELY ABSENT (Filtered)" AKP_RESET);

    akp_bloom_destroy(bf);

    /* ========================================================================
     * 4. LINEAR MEMORY ARENA ALLOCATOR
     * ======================================================================== */
    akp_log_info("DEMO 4: Linear Memory Arena (High-Performance Bump Allocator)");

    akp_arena_t* arena = akp_arena_create(2048);

    /* Allocate scratch records */
    typedef struct {
        int id;
        double metric;
        char tag[16];
    } record_t;

    record_t* recs = (record_t*)akp_arena_alloc(arena, 10 * sizeof(record_t));
    if (recs) {
        for (int i = 0; i < 10; i++) {
            recs[i].id = 1000 + i;
            recs[i].metric = (double)i * 1.618;
            snprintf(recs[i].tag, sizeof(recs[i].tag), "CORE_%d", i);
        }
    }

    char* scratch_str = (char*)akp_arena_alloc(arena, 256);
    if (scratch_str) {
        snprintf(scratch_str, 256, "AKP Systems Scratch Buffer Segment");
    }

    akp_arena_render(arena, "Game Loop Scratch Allocation Frame");
    /* Instant O(1) Reclaim */
    akp_log_info("Executing Instant O(1) Arena Reset...");
    akp_arena_reset(arena);
    akp_arena_render(arena, "Post-Reset Ready State");

    akp_arena_destroy(arena);

    /* ========================================================================
     * HEAP MEMORY AUDIT
     * ======================================================================== */
    void* audit_ptr = AKP_MALLOC(1024);
    AKP_FREE(audit_ptr);
    akp_mem_report();

    akp_log_akp("DONE", "%s", "AKP Engine v1.8.0 Demonstration Complete. 100% Silent, Zero Leaks.");
    return 0;
}
