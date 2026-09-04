/**
 * ============================================================================
 *  AKP ENGINE - MODERN C++ DEMONSTRATION (examples/cpp_demo.cpp)
 *  Author: Akshar Miyani | AKP Studio
 *  Compile: g++ examples/cpp_demo.cpp -I include -std=c++17 -o cpp_demo.exe
 * ============================================================================
 */

#include "akp.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    /* 1. Print Author Splash Banner */
    akp_banner();
    akp_stamp("Modern C++ STL & Benchmarks Suite");

    akp_log_akp("C++17", "C++ Integration verified for Akshar Miyani.");

    /* 2. C++ Vector Benchmarking */
    std::vector<int> numbers = { 64, 25, 12, 22, 11, 90, 88, 34 };
    akp_visualize_array(numbers.data(), (int)numbers.size(), 0, "Initial std::vector");

    AKP_BENCHMARK("std::sort execution") {
        std::sort(numbers.begin(), numbers.end());
    }

    akp_visualize_array(numbers.data(), (int)numbers.size(), (int)numbers.size() - 1, "Sorted std::vector");
    akp_log_success("Vector sorted in ascending order.");

    /* 3. Display Table of Performance Metrics */
    akp_table_t* t = akp_table_create(3, "Modern C++ Container Comparison");
    akp_table_set_headers(t, "Container", "Access Complexity", "Memory Contiguity");
    akp_table_add_row(t, "std::vector", "O(1) Direct", "Contiguous Buffer");
    akp_table_add_row(t, "std::deque",  "O(1) Chunked", "Segmented Pages");
    akp_table_add_row(t, "std::list",   "O(N) Traversal", "Heap Node Pointers");
    akp_table_render(t);
    akp_table_free(t);

    akp_sound_success();
    akp_log_success("C++ Demonstration completed with zero issues!");
    return 0;
}
