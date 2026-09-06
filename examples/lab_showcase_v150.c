/**
 * ============================================================================
 *  AKP ENGINE v1.5.0 - ADVANCED LAB SHOWCASE (examples/lab_showcase_v150.c)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Demonstrates Hash Table with Chaining, Singly/Doubly Linked Lists,
 *           Dijkstra Shortest Path, and KMP String Pattern Matching (0dB Silent).
 * ============================================================================
 */

#include "akp.h"

int main(void) {
    /* 1. Author Splash Banner & Lab Evaluation Stamp */
    akp_banner();
    akp_stamp("Practical Lab Showcase v1.5.0: Advanced Data Structures");

    akp_log_akp("INIT", "AKP Core Engine v1.5.0 loaded successfully.");
    akp_log_info("Silent Audio Engine active: 0dB emitted for quiet computer lab compliance.");

    /* 2. Hash Table with Chaining Visualizer */
    printf("\n" AKP_BOLD AKP_NEON_YELLOW "--- [1] HASH TABLE WITH COLLISION RESOLUTION (CHAINING) ---" AKP_RESET "\n");
    akp_ht_t* ht = akp_ht_create(5, "StudentRegistry_HashTable");
    akp_log_info("Inserting 7 keys with intentional bucket collisions...");
    akp_ht_insert(ht, 101, 95);
    akp_ht_insert(ht, 106, 88); /* 101 % 5 == 1, 106 % 5 == 1 -> Collision! */
    akp_ht_insert(ht, 111, 92); /* Collision! */
    akp_ht_insert(ht, 102, 79);
    akp_ht_insert(ht, 107, 85);
    akp_ht_insert(ht, 103, 99);
    akp_ht_insert(ht, 104, 91);

    akp_ht_render(ht);

    int search_val = 0;
    if (akp_ht_search(ht, 106, &search_val)) {
        akp_log_success("Retrieved Key 106 from chained bucket! Value = %d", search_val);
    }
    akp_ht_free(ht);

    /* 3. Singly & Doubly Linked List Visualizers */
    printf("\n" AKP_BOLD AKP_NEON_YELLOW "--- [2] LINKED LIST STRUCTURE VISUALIZERS ---" AKP_RESET "\n");
    akp_slist_t* slist = akp_slist_create("TaskExecution_Queue");
    akp_slist_insert_tail(slist, 10);
    akp_slist_insert_tail(slist, 20);
    akp_slist_insert_tail(slist, 30);
    akp_slist_insert_head(slist, 5);
    akp_slist_render(slist);

    akp_log_info("Deleting element 20 from Singly Linked List...");
    akp_slist_delete(slist, 20);
    akp_slist_render(slist);
    akp_slist_free(slist);

    akp_dlist_t* dlist = akp_dlist_create("Bidirectional_Buffer");
    akp_dlist_insert_tail(dlist, 100);
    akp_dlist_insert_tail(dlist, 200);
    akp_dlist_insert_tail(dlist, 300);
    akp_dlist_render(dlist);
    akp_dlist_free(dlist);

    /* 4. Dijkstra Single-Source Shortest Path */
    printf(AKP_BOLD AKP_NEON_YELLOW "--- [3] DIJKSTRA SHORTEST PATH ANALYSIS ---" AKP_RESET "\n");
    akp_graph_t* g = akp_graph_create(5, 0);
    akp_graph_add_edge(g, 0, 1, 10);
    akp_graph_add_edge(g, 0, 4, 3);
    akp_graph_add_edge(g, 1, 2, 2);
    akp_graph_add_edge(g, 1, 4, 4);
    akp_graph_add_edge(g, 2, 3, 9);
    akp_graph_add_edge(g, 3, 2, 7);
    akp_graph_add_edge(g, 4, 1, 1);
    akp_graph_add_edge(g, 4, 2, 8);
    akp_graph_add_edge(g, 4, 3, 2);

    akp_graph_render_adj_matrix(g, "Routing Topology");
    akp_dijkstra_t dres = akp_dijkstra_solve(g, 0);
    akp_dijkstra_render(&dres);
    akp_graph_free(g);

    /* 5. String Pattern Matching (KMP & Naive) */
    printf(AKP_BOLD AKP_NEON_YELLOW "--- [4] STRING PATTERN MATCHING VISUALIZER ---" AKP_RESET "\n");
    const char* genome_seq = "ACGTACGTAGCTACGTACGTACTGACG";
    const char* marker     = "ACGTACGTAC";
    akp_search_naive_pattern(genome_seq, marker);
    akp_search_kmp(genome_seq, marker);

    /* 6. Conclusion */
    akp_log_success("AKP v1.5.0 demonstration completed with 100%% precision & ZERO noise!");
    akp_log_info("Engineered by Akshar Miyani | AKP Studio");

    return 0;
}
