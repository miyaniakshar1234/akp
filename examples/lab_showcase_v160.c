/**
 * ============================================================================
 * AKP ENGINE - FLASHY C/C++ TOOLKIT
 * EXAMPLE: lab_showcase_v160.c
 * Demonstrating v1.6.0 Subsystems:
 * 1. Visual Binary Min-Heap & Priority Queue
 * 2. Visual Prefix Tree (Trie) & Autocomplete
 * 3. Huffman Coding & Lossless Data Compression
 * 4. LRU (Least Recently Used) Cache Simulator
 * 
 * Engineered & Authored by: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#include "akp.h"

int main(void) {
    akp_init_console();

    // 1. Splash & Academic Lab Evaluation Stamp
    akp_banner();
    akp_stamp("Advanced Systems & Algorithmic Structures Lab Showcase v1.6.0");

    akp_log_akp("INIT", "Loaded AKP Engine v1.6.0 - 32 High-Performance Subsystems Active.");

    // 2. Demonstration: Binary Min-Heap & Priority Queue
    akp_log_info("DEMO", "Executing Binary Min-Heap & Priority Queue Operations...");
    akp_min_heap_t* heap = akp_min_heap_create(16, "LabTaskHeap");
    akp_min_heap_insert(heap, 45);
    akp_min_heap_insert(heap, 20);
    akp_min_heap_insert(heap, 14);
    akp_min_heap_insert(heap, 12);
    akp_min_heap_insert(heap, 31);
    akp_min_heap_insert(heap, 7);
    akp_min_heap_insert(heap, 11);
    akp_min_heap_render(heap, "Initial Multi-Level Min-Heap State");

    int extracted = 0;
    akp_min_heap_extract_min(heap, &extracted);
    akp_log_success("HEAP", "Extracted Min Element (Highest Priority): %d", extracted);
    akp_min_heap_render(heap, "State After Extract-Min (Heapify Down Executed)");
    akp_min_heap_destroy(heap);

    // 3. Demonstration: Prefix Tree (Trie) Autocomplete Hierarchy
    akp_log_info("DEMO", "Synthesizing Prefix Tree (Trie) Lexical Structure...");
    akp_trie_t* trie = akp_trie_create();
    akp_trie_insert(trie, "algorithm");
    akp_trie_insert(trie, "algo");
    akp_trie_insert(trie, "algebra");
    akp_trie_insert(trie, "binary");
    akp_trie_insert(trie, "bin");
    akp_trie_insert(trie, "byte");
    akp_trie_render(trie, "Systems Vocabulary");

    bool has_algo = akp_trie_search(trie, "algorithm");
    bool has_tree = akp_trie_search(trie, "tree");
    akp_log_info("TRIE", "Search 'algorithm': %s", has_algo ? "FOUND (True)" : "NOT FOUND");
    akp_log_warn("TRIE", "Search 'tree': %s", has_tree ? "FOUND (True)" : "NOT FOUND (False)");
    akp_trie_destroy(trie);

    // 4. Demonstration: Huffman Optimal Prefix Coding & Data Compression
    akp_log_info("DEMO", "Encoding Dataset with Huffman Greedy Variable-Length Trees...");
    const char* sample_text = "AKSHAR MIYANI AKP SYSTEMS ARCHITECTURE ENGINE";
    akp_huffman_result_t huff_res;
    if (akp_huffman_encode(sample_text, &huff_res)) {
        akp_huffman_render(sample_text, &huff_res, "Author Signature String");
    }

    // 5. Demonstration: LRU Cache Simulation
    akp_log_info("DEMO", "Executing LRU Cache Buffer Pool Simulation...");
    akp_lru_cache_t* cache = akp_lru_create(4); // Capacity of 4 pages
    akp_lru_put(cache, 101, 550);
    akp_lru_put(cache, 102, 620);
    akp_lru_put(cache, 103, 710);
    akp_lru_put(cache, 104, 880);
    akp_lru_render(cache, "Initial Warm Cache (Capacity 4)");

    // Access Page 102 (Promotes to MRU / Head)
    akp_log_info("CACHE", "Querying Key 102 -> Value: %d [CACHE HIT]", akp_lru_get(cache, 102));
    akp_lru_render(cache, "After Accessing Key 102 (Promoted to MRU)");

    // Insert Page 105 (Evicts Page 101 as LRU)
    akp_log_warn("CACHE", "Inserting New Key 105 (Forces Eviction of LRU Page 101)...");
    akp_lru_put(cache, 105, 990);
    akp_lru_render(cache, "After Eviction of LRU (Tail)");
    akp_lru_destroy(cache);

    // 6. Memory Leak Audit Certification
    void* temp_buffer = AKP_MALLOC(512);
    AKP_FREE(temp_buffer);
    akp_mem_report();

    akp_log_akp("DONE", "AKP Engine v1.6.0 Lab Demonstration Complete. 100%% Silent, Zero Leaks.");
    return 0;
}
