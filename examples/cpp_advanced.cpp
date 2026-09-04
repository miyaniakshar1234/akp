/**
 * ============================================================================
 *  AKP ENGINE - MODERN C++20 ADVANCED STL SUITE (examples/cpp_advanced.cpp)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#include "akp.hpp"

int main() {
    akp_banner();
    akp_stamp("Modern C++ STL & 2D Canvas Suite");

    std::cout << akp::neon_cyan << "🚀 Running Modern C++ AKP Engine by " 
              << akp::bold << akp::neon_yellow << "Akshar Miyani" << akp::reset << std::endl;

    /* 1. RAII Scoped Benchmark Timer */
    {
        akp::ScopedTimer timer("STL Computation Benchmark");
        std::vector<double> metrics = { 12.4, 25.6, 38.1, 42.0, 65.4, 78.9, 91.2, 105.0 };
        akp::sparkline(metrics, "Cache Bus Throughput (GB/s)");
    }

    /* 2. Modern C++ Fluent Table Builder */
    akp::Table table("Memory Hierarchy Speeds", { "Tier", "Latency", "Bandwidth" });
    table.addRow({ "L1 Cache",   "0.9 ns", "2.1 TB/s" });
    table.addRow({ "L2 Cache",   "2.8 ns", "950 GB/s" });
    table.addRow({ "L3 Cache",  "11.5 ns", "480 GB/s" });
    table.addRow({ "Main DDR5", "65.0 ns",  "85 GB/s" });
    table.render();

    /* 3. 2D Geometric Terminal Canvas */
    akp::Canvas canvas(40, 14);
    akp_rgb_t cyan = akp_hex(0x00FFEAu);
    akp_rgb_t pink = akp_hex(0xFF007Fu);
    akp_rgb_t gold = akp_hex(0xFFB800u);

    canvas.drawRect(2, 1, 36, 12, '#', cyan);
    canvas.drawCircle(20, 6, 4, '*', pink);
    canvas.drawText(8, 6, "AKP C++ ENGINE", gold);
    canvas.render("Hardware Vector Canvas");

    akp_sound_success();
    akp_log_success("C++ Advanced Demonstration completed with 100%% precision!");

    return 0;
}
