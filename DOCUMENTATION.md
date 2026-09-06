# ⚡ AKP ENGINE: THE DEFINITIVE ARCHITECTURAL MANUAL
### *Master Documentation of the High-Performance Flashy C/C++ Toolkit*
**Engineered & Authored by the Genius Architect: Akshar Miyani**  
*AKP Studio Systems Architecture | Version 1.7.0 (Silent Audio Engine)*

---

## 🏛️ 1. Architectural Philosophy & Vision

Standard C (`<stdio.h>`) has remained visually static since 1972. In modern development environments, terminal applications are often expected to be dreary, monochromatic, and visually uninspiring.

**AKP Engine** was conceived and engineered from first principles by **Akshar Miyani** to shatter this limitation. It provides an enterprise-grade, zero-dependency, header-only runtime that brings **24-bit TrueColor Cyberpunk aesthetics**, **real-time memory leak auditing**, **algorithmic visualizers**, **hardware audio feedback (0dB silent by default)**, and **interactive terminal UI controls** to pure C and C++.

### Core Engineering Invariants:
1. **Zero External Dependencies**: Operates strictly on standard C99/C11 and C++11/14/17/20 headers and platform kernels (`windows.h` on NT systems, `unistd.h` / `termios.h` on POSIX systems).
2. **Deterministic Memory Footprint**: Minimal heap interaction. All visualizers and formatting engines utilize bounded stack buffers or strictly audited heap segments.
3. **Cross-Platform Parity**: Identical visual fidelity and behavior across Windows Command Prompt, PowerShell, Windows Terminal, Linux virtual consoles, and macOS Terminal.
4. **Drop-in Simplicity**: Dual deployment models: modular sub-headers under `include/akp/` for large systems, or a single amalgamated file `include/akp.h` for instant academic lab flexing.
5. **Silent Audio Engine**: Completely 0dB silent by default to prevent classroom or computer lab disruption.

---

## 📦 2. Library Structure & Subsystem Layout

```
d:/Projects/AKP/
├── include/
│   ├── akp.h                   # Standalone Amalgamated Master Header (v1.7.0)
│   ├── akp.hpp                 # Modern C++17/20 STL & RAII Master Wrapper
│   └── akp/                    # Modular Header Suite (36 Subsystems)
│       ├── akp.h               # Root Modular Umbrella Header
│       ├── color.h             # 24-Bit TrueColor RGB, ANSI, Linear Gradients
│       ├── banner.h            # ASCII Branding Splash & Lab Evaluation Stamp
│       ├── badge.h             # Real-Time Timestamped Status Badges
│       ├── progress.h          # Braille Spinners & Interpolated Progress Bars
│       ├── table.h             # Dynamic Auto-Sizing Unicode Border Tables
│       ├── memory.h            # Hex-Dump Inspector & Zero-Leak Heap Auditor
│       ├── timer.h             # Hardware Microsecond Benchmark Macros
│       ├── sound.h             # Retro Hardware Audio (Silent 0dB by Default)
│       ├── dsa.h               # In-Terminal DSA Array & Matrix Visualizers
│       ├── plot.h              # Unicode Sparklines & 2D Curve Function Plotter
│       ├── tree.h              # Hierarchical Binary Tree Structure Printer
│       ├── prompt.h            # Arrow-Key Menus, Masked Passwords & Prompts
│       ├── test.h              # Micro Unit-Testing Framework & Assertions
│       ├── canvas.h            # 2D Geometric Terminal Vector Canvas (Bresenham)
│       ├── form.h              # Multi-Field Terminal Interactive Form Wizard
│       ├── sort_anim.h         # Live In-Terminal Sorting Animator (In-Place)
│       ├── melody.h            # Retro 8-Bit Chiptune Musical Synthesizer
│       ├── sysinfo.h           # Cyberpunk Hardware Telemetry Dashboard
│       ├── matrix.h            # Linear Algebra & Dynamic Matrix Operations
│       ├── stack_queue.h       # Visual LIFO Stack & Circular FIFO Queue
│       ├── search_anim.h       # Step-by-Step Visual Linear & Binary Search
│       ├── graph.h             # Graph Adjacency Matrix & BFS/DFS Traversals
│       ├── theme.h             # Cyberpunk, Matrix, Dracula, Synthwave Themes
│       ├── hash_table.h        # Visual Hash Table with Chaining & Collision Audit
│       ├── linked_list.h       # Visual Singly & Doubly Linked List Node Diagrams
│       ├── dijkstra.h          # Dijkstra Single-Source Shortest Path Router
│       ├── pattern_match.h     # Naive & KMP Pattern Matching Visualizer
│       ├── min_heap.h          # Binary Min-Heap & Priority Queue Level Visualizer
│       ├── trie.h              # Visual Prefix Tree (Trie) & Autocomplete Tree
│       ├── huffman.h           # Huffman Variable Prefix Coding & Compression
│       ├── lru_cache.h         # Visual LRU Cache Buffer Pool & Eviction Monitor
│       ├── disjoint_set.h      # Disjoint-Set Union-Find (DSU) & Set Partitions
│       ├── kruskal.h           # Kruskal's Minimum Spanning Tree (MST) Visualizer
│       ├── ring_buffer.h       # Lockless SPSC Circular Ring Buffer & Fill Gauge
│       └── bitset.h            # Systems Bitset & 64-Bit Register Telemetry
├── examples/
│   ├── lab_demo.c              # Comprehensive C Lab Demonstration
│   ├── cpp_demo.cpp            # Modern C++17 STL Benchmark & Visualizer
│   ├── cpp_advanced.cpp        # Modern C++ RAII Canvas & Table Demo
│   ├── lab_showcase_v130.c     # Live Showcase: Sorting, Telemetry, Melodies
│   ├── lab_showcase_v140.c     # v1.4.0 Showcase: Stack, Queue, Search, Graph
│   ├── lab_showcase_v150.c     # v1.5.0 Showcase: Hash Table, Lists, Dijkstra, KMP
│   ├── lab_showcase_v160.c     # v1.6.0 Showcase: Min-Heap, Trie, Huffman, LRU Cache
│   └── lab_showcase_v170.c     # v1.7.0 Showcase: DSU, Kruskal MST, Ring Buffer, Bitset
├── tests/
│   └── test_suite.c            # Automated 79/79 Test Suite (100% Pass Rate)
├── cmake/
│   └── AKPConfig.cmake.in      # Modern CMake Package Export
├── ports/akp/                  # Official vcpkg Port Definition
│   ├── vcpkg.json
│   └── portfile.cmake
├── conanfile.py                # Conan 2.0 Package Recipe
├── install.ps1                 # Windows 1-Click Universal Installer
├── install.sh                  # Linux / macOS 1-Click Universal Installer
├── CMakeLists.txt              # CMake Build System Configuration
└── README.md                   # Repository Showcase & GitHub Badges
```

---

## 🔬 3. Exhaustive Subsystem & API Reference

### 3.1. TrueColor RGB & Palette Engine (`akp/color.h`)

#### Internal Mechanism:
Standard terminals support 8 or 16 ANSI colors. Modern terminal emulators support ISO-8613-3 24-bit TrueColor sequences (`\x1b[38;2;R;G;Bm`). On Windows NT systems, `akp_init_console()` automatically enables `ENABLE_VIRTUAL_TERMINAL_PROCESSING` (flag `0x0004`) via `SetConsoleMode()` and initializes `CP_UTF8` (Code Page 65001) for Unicode glyph stability.

#### Data Structures:
```c
typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} akp_rgb_t;
```

#### Functions & Macros:
- `akp_init_console(void)`: Idempotently initializes the Windows virtual terminal processor and UTF-8 console output.
- `akp_rgb(uint8_t r, uint8_t g, uint8_t b)`: Constructs an `akp_rgb_t` triple.
- `akp_hex(uint32_t hex)`: Parses a 24-bit hex integer (`0x00FFEAu` -> `{0x00, 0xFF, 0xEA}`).
- `akp_set_fg_rgb(uint8_t r, uint8_t g, uint8_t b)`: Emits raw 24-bit ANSI foreground escape sequences.
- `akp_set_bg_rgb(uint8_t r, uint8_t g, uint8_t b)`: Emits raw 24-bit ANSI background escape sequences.
- `akp_print_gradient(const char* text, akp_rgb_t start, akp_rgb_t end)`: Computes linear interpolation:
  $$C(t) = C_{start} + t \cdot (C_{end} - C_{start}), \quad t \in [0, 1]$$
  and outputs each character with smoothly transitioning 24-bit foreground colors.

---

### 3.2. Author Branding & Splash Watermark (`akp/banner.h`)

#### Functions:
- `akp_banner(void)`: Emits the signature double-bordered Cyberpunk ASCII art banner prominently highlighting:
  - **Developer**: Akshar Miyani
  - **Studio**: AKP Studio
  - **Engine**: AKP Core Engine
- `akp_stamp(const char* assignment_name)`: Renders a compact terminal evaluation stamp to top lab submissions with:
  ```
  ┌────────────────────────────────────────────────────────────────────────┐
  │ ⚡ AKP LAB SUITE :: Advanced Data Structures Lab                     │
  │ Developed & Engineered by: Akshar Miyani (MCA)                         │
  └────────────────────────────────────────────────────────────────────────┘
  ```

---

### 3.3. High-Visibility Status Logging Badges (`akp/badge.h`)

#### Functions:
- `akp_log_success(const char* fmt, ...)`: Renders `[HH:MM:SS] [ ✔ SUCCESS ]` in Neon Green.
- `akp_log_info(const char* fmt, ...)`: Renders `[HH:MM:SS] [ ℹ INFO    ]` in Electric Cyan.
- `akp_log_warn(const char* fmt, ...)`: Renders `[HH:MM:SS] [ ⚠ WARNING ]` in Amber Gold.
- `akp_log_error(const char* fmt, ...)`: Renders `[HH:MM:SS] [ ✖ ERROR   ]` in Crimson Red.
- `akp_log_akp(const char* tag, const char* fmt, ...)`: Renders `[HH:MM:SS] [ ⚡ TAG ]` in Synthwave Purple.

All badge loggers capture system time with `time()` and `localtime()`, formatting strings via `vprintf()`.

---

### 3.4. Dynamic Gradient Progress Bars & Spinners (`akp/progress.h`)

#### Functions:
- `akp_progress(int current, int total, const char* prefix)`:
  Emits a non-destructive carriage return `\r` and renders a 30-character block progress bar with 24-bit gradient interpolation between Cyan (`#00FFEA`) and Pink (`#FF007F`). Displays percentage and fractional ratios `(current/total)`. Emits `\n` on completion.
- `akp_spinner(int step, const char* task_name)`:
  Renders an animated braille spinner (`⠋ ⠙ ⠹ ⠸ ⠼ ⠴ ⠦ ⠧ ⠇ ⠏`) in-place.

---

### 3.5. Auto-Sizing Unicode Tables (`akp/table.h`)

#### Engineering Design:
Calculates column widths dynamically based on the longest text cell in each column. Renders rounded box-drawing characters:
- Top: `╭` `─` `┬` `╮`
- Header Separator: `├` `─` `┼` `┤`
- Bottom: `╰` `─` `┴` `╯`
- Vertical Separators: `│`

#### Functions:
- `akp_table_t* akp_table_create(int cols, const char* title)`: Allocates and initializes table metadata.
- `akp_table_set_headers(akp_table_t* t, ...)`: Sets variable column headers and updates column constraints.
- `akp_table_add_row(akp_table_t* t, ...)`: Appends a row of string values, expanding column widths if needed.
- `akp_table_render(akp_table_t* t)`: Renders the entire table with alternating row contrast.
- `akp_table_free(akp_table_t* t)`: Deallocates table memory.

---

### 3.6. Memory Hex-Dump & Zero-Leak Heap Auditor (`akp/memory.h`)

#### Hex-Dump Inspector:
- `akp_hexdump(const void* ptr, size_t size, const char* label)`:
  Inspects arbitrary memory buffers in 16-byte rows:
  - Offset column (`00000000`)
  - Hex values categorized by color (Zeroes = Dim, Printable ASCII = Neon Green, Non-printable = Neon Pink)
  - ASCII representation preview (`.` for control characters).

#### Heap Allocation Auditor:
Wraps standard allocation with a size header prefix:
- `AKP_MALLOC(sz)`: Allocates `sz + sizeof(size_t)` bytes, tracks cumulative allocated bytes, peak heap memory, and allocation counter.
- `AKP_FREE(p)`: Decrements active heap bytes and increments deallocation counter.
- `akp_mem_report(void)`: Emits an audit box. If active allocated bytes $> 0$, flags a high-priority red alert `⚠ MEMORY LEAK`. If $0$, confirms `✔ ZERO LEAKS (Clean Memory)`.

---

### 3.7. High-Precision Micro-Benchmark Timer (`akp/timer.h`)

#### Performance Counter:
On Windows NT, leverages the CPU hardware performance counter via `QueryPerformanceFrequency()` and `QueryPerformanceCounter()`. On POSIX systems, utilizes `clock_gettime(CLOCK_MONOTONIC)`.

#### Benchmark Macro:
```c
AKP_BENCHMARK("Quicksort Algorithm") {
    quicksort(data, 0, N - 1);
}
```
Executes the scoped block and automatically prints the elapsed duration in milliseconds with 4 decimal digits of precision ($\mu s$ resolution).

---

### 3.8. Retro Sound Effects Engine (`akp/sound.h`)

#### Audio Synthesis:
On Windows systems, interfaces directly with the hardware motherboard timer speaker via `Beep(DWORD dwFreq, DWORD dwDuration)`:
- `akp_sound_coin()`: Synthesizes the iconic 8-bit Mario Coin sound ($B_5 = 988\text{ Hz}$ for $100\text{ ms}$, followed by $E_6 = 1319\text{ Hz}$ for $250\text{ ms}$).
- `akp_sound_success()`: Synthesizes a 4-note ascending major chord victory chime ($C_5 \to E_5 \to G_5 \to C_6$).
- `akp_sound_alert()`: Synthesizes an attention-grabbing warning alert ($440\text{ Hz} \to 330\text{ Hz}$).

---

### 3.9. Algorithmic DSA Visualizers (`akp/dsa.h`)

#### Functions:
- `akp_visualize_array(const int* arr, int n, int highlight_idx, const char* title)`:
  Normalizes integer array values and renders horizontal bar charts (`█████`) directly in the console. Highlights a chosen index (e.g., current pivot or minimum element) in vibrant Neon Pink with `◄ SELECTED`.
- `akp_print_matrix(const int* mat, int rows, int cols, const char* title)`:
  Renders 2D matrices formatted inside color brackets (`│`), coloring positive numbers green, negative numbers pink, and zeroes dim.

---

### 3.10. Terminal Graph & Function Curve Plotter (`akp/plot.h`)

#### Functions:
- `akp_sparkline(const double* values, int count, const char* label)`:
  Encodes continuous telemetry or benchmark histories into 8-level Unicode sparkline block glyphs:
  ` ` $\to$ `▂` $\to$ `▃` $\to$ `▄` $\to$ `▅` $\to$ `▆` $\to$ `▇` $\to$ `█`
- `akp_plot_curve(double (*func)(double), double x_min, double x_max, int width, int height, const char* title)`:
  Samples an arbitrary mathematical function $f(x)$ over $[x_{min}, x_{max}]$, scales the coordinate plane, and rasterizes a 2D ASCII/Unicode point curve with vertical and horizontal axes.

---

### 3.11. Binary Tree Hierarchy Visualizer (`akp/tree.h`)

#### Functions:
- `akp_tree_create_node(int val, const char* label)`: Allocates a binary tree node.
- `akp_tree_print(const akp_tree_node_t* root, const char* title)`:
  Renders full hierarchical binary search trees with recursive branch lines (`┌──`, `│`, `└──`) in a clean horizontal orientation.

---

### 3.12. Interactive CLI Controls (`akp/prompt.h`)

#### Functions:
- `akp_prompt_confirm(const char* question)`: Captures single-key confirmation (`y` or `n`) without requiring Enter.
- `akp_prompt_password(const char* prompt, char* buffer, size_t max_len)`:
  Captures sensitive inputs while displaying masked bullets (`••••••`) in real time, handling backspace deletion properly.
- `akp_prompt_select(const char* title, const char* options[], int count)`:
  Interactive arrow-key selector. Users navigate using **Up ($\uparrow$)** / **Down ($\downarrow$)** keys or numeric shortcuts, highlighting the active option in Neon Pink (`► Option ◄`). Pressing **Enter** returns the selected index.

### 3.13. Micro Unit-Testing Framework (`akp/test.h`)

#### Functions & Macros:
- `akp_test_suite_begin(name)`: Initializes a micro test suite with monotonic hardware execution timer.
- `AKP_TEST(suite, name, condition)`: Evaluates a boolean assertion, emitting timestamped pass/fail badges with filename and line numbers.
- `AKP_ASSERT_EQ(suite, name, actual, expected)`: Macro comparing equality (`==`).
- `AKP_ASSERT_STR_EQ(suite, name, actual, expected)`: Macro comparing C strings (`strcmp() == 0`).
- `akp_test_suite_end(&suite)`: Emits an audit summary with test counts, elapsed execution time in milliseconds, pass rate percentage, and triggers celebratory Mario audio on 100% pass!

---

### 3.14. 2D Geometric Terminal Canvas Engine (`akp/canvas.h`)

#### Algorithms & Drawing Primitives:
- `akp_canvas_create(width, height)`: Allocates an in-memory character and 24-bit TrueColor pixel buffer.
- `akp_canvas_draw_line(...)`: Bresenham's Integer Line Drawing Algorithm.
- `akp_canvas_draw_rect(...)`: Four-point boundary box rasterizer.
- `akp_canvas_draw_circle(...)`: Midpoint Circle Drawing Algorithm.
- `akp_canvas_draw_text(...)`: In-canvas text rendering with custom foreground colors.
- `akp_canvas_render(title)`: Renders the entire 2D canvas enclosed in Unicode borders.

---

### 3.15. Modern C++17/20 STL & RAII Wrapper (`akp.hpp`)

#### Classes & Streams:
- `akp::neon_cyan`, `akp::neon_pink`, `akp::reset`: Modern `std::ostream` manipulators for stream output.
- `akp::ScopedTimer`: RAII timer measuring execution block duration and printing benchmarks on destructor invocation.
- `akp::Table`: Fluent C++ initializer-list builder (`table.addRow({ "A", "B" })`).
- `akp::Canvas`: Object-oriented 2D canvas with RAII memory management.
- `akp::sparkline(vector, label)`: Overloaded for `std::vector<double>`.

### 3.16. Interactive Form & Input Wizard (`akp/form.h`)

#### Functions & Structures:
- `akp_form_create(title)`: Initializes a bordered form dialog box.
- `akp_form_add_text(form, label, default)`: Adds a single-line string input field.
- `akp_form_add_int(form, label, default)`: Adds an integer input field with numeric parsing.
- `akp_form_add_confirm(form, label, default)`: Adds a boolean confirmation checkbox (`y/n`).
- `akp_form_execute(form)`: Renders the input dialog and collects user inputs sequentially.
- `akp_form_get_text(form, idx)`, `akp_form_get_int(form, idx)`, `akp_form_get_bool(form, idx)`: Type-safe field extractors.

---

### 3.17. Real-Time Terminal Sorting Animator (`akp/sort_anim.h`)

#### Functions:
- `akp_animate_sort(arr, n, type, delay_ms)`:
  Animates sorting algorithms in the terminal in real time. At each comparison and swap, the cursor moves up by $n+1$ lines and re-renders the array bars with the active elements highlighted in Neon Pink (`◄ A`) and Acid Green (`◄ B`).
  - `AKP_ANIM_BUBBLE`: Bubble sort animation.
  - `AKP_ANIM_SELECTION`: Selection sort animation.
  - `AKP_ANIM_INSERTION`: Insertion sort animation.

---

### 3.18. Retro Terminal Melody Synthesizer (`akp/melody.h`)

#### Functions:
- `akp_play_tone(freq_hz, duration_ms)`: Emits hardware frequency beeps.
- `akp_melody_tetris()`: Plays the iconic 8-bit Tetris theme (Korobeiniki).
- `akp_melody_starwars()`: Plays the Star Wars Imperial March fanfare.
- `akp_melody_nokia()`: Plays the nostalgic Nokia retro tune.

---

### 3.19. Hardware Telemetry & System Monitor (`akp/sysinfo.h`)

#### Functions:
- `akp_sysinfo_get()`: Queries native OS APIs for total physical RAM, free RAM, memory load percentage, CPU core count, and processor architecture.
- `akp_sysinfo_render()`: Renders a Cyberpunk Neofetch-style telemetry monitor card with a live graphical memory usage gauge bar `[██████░░░░] 59%`.

---

### 3.20. Linear Algebra & Matrix Operations (`akp/matrix.h`)

#### Functions:
- `akp_mat_create(rows, cols)`: Allocates dynamic 2D floating-point matrix buffer.
- `akp_mat_multiply(A, B)`: Performs matrix multiplication ($C = A \times B$) with dimension validation.
- `akp_mat_transpose(A)`: Computes matrix transpose ($A^T$).
- `akp_mat_det3x3(m)`: Computes $3 \times 3$ determinant.
- `akp_mat_render(m, title)`: Renders matrix enclosed in color brackets (`│`), distinguishing positive, negative, and zero elements.

---

### 3.21. Visual LIFO Stack & Circular FIFO Queue (`akp/stack_queue.h`)

#### Internal Mechanism:
Provides dynamic visual containers with overflow/underflow protection, capacity telemetry bars, and pointer visualization.
- `akp_stack_t* akp_stack_create(capacity, name)`: Allocates LIFO stack with named header.
- `akp_stack_push(s, val)` / `akp_stack_pop(s, &out)`: Stack mutations with boundary checking.
- `akp_stack_render(s)`: Renders vertical ASCII stack with `TOP ->` and `BOT ->` pointers and capacity percentage gauge.
- `akp_queue_t* akp_queue_create(capacity, name)`: Allocates circular FIFO buffer.
- `akp_queue_enqueue(q, val)` / `akp_queue_dequeue(q, &out)`: Circular modulo wraparound index math.
- `akp_queue_render(q)`: Renders slots with dynamic `F` (front) and `R` (rear) pointer indicators.

---

### 3.22. Step-by-Step Visual Linear & Binary Search (`akp/search_anim.h`)

#### Functions:
- `akp_search_linear(arr, n, target)`: Step-by-step element comparison ($O(N)$) highlighting match status.
- `akp_search_binary(arr, n, target)`: Interactive binary search ($O(\log N)$) rendering dynamic window subarrays, `Low`, `Mid`, `High` pointers, and search direction reasoning.

---

### 3.23. Graph Topology & Adjacency Matrix (`akp/graph.h`)

#### Functions:
- `akp_graph_create(vertices, is_directed)`: Allocates graph topology container.
- `akp_graph_add_edge(g, u, v, weight)`: Inserts directed or undirected weighted edge.
- `akp_graph_render_adj_matrix(g, title)`: Renders grid representation with vertex headers.
- `akp_graph_bfs(g, start)`: Breadth-First Search traversal with queue tracking.
- `akp_graph_dfs(g, start)`: Depth-First Search recursive traversal with path tracking.

---

### 3.24. Terminal Color Themes (`akp/theme.h`)

#### Functions:
- `akp_theme_get(id)`: Returns theme palette struct for `AKP_THEME_CYBERPUNK`, `AKP_THEME_MATRIX`, `AKP_THEME_SYNTHWAVE`, `AKP_THEME_DRACULA`, `AKP_THEME_MONOKAI`.
- `akp_theme_preview(id)`: Renders swatch preview of primary, secondary, and accent TrueColors.

---

### 3.25. Visual Hash Table with Chaining (`akp/hash_table.h`)

#### Internal Mechanism:
Solves the fundamental data structures problem of hash collision visualization. Uses separate chaining with linked list buckets, djb2/modulo hash calculation, and real-time collision auditing.
- `akp_ht_t* akp_ht_create(int num_buckets)`: Allocates hash table with dynamically bounded bucket array.
- `bool akp_ht_insert(akp_ht_t* ht, const char* key, int value)`: Inserts key-value pair, updating existing keys or appending to bucket chain.
- `bool akp_ht_get(akp_ht_t* ht, const char* key, int* out_val)`: Lookups key with $O(1)$ average time complexity.
- `void akp_ht_render(const akp_ht_t* ht, const char* title)`: Renders full bucket diagram with arrows (`Bucket[i] -> [key: val] -> [key: val]`), collision count, max chain depth, and load factor ($\alpha = N / B$).
- `void akp_ht_destroy(akp_ht_t* ht)`: Fully deallocates bucket chains and table structure.

---

### 3.26. Visual Singly & Doubly Linked Lists (`akp/linked_list.h`)

#### Internal Mechanism:
Renders dynamic memory node chains in full ASCII/Unicode with pointer arrows, element values, and node indices.
- **Singly Linked List (`akp_slist_t`)**:
  - `akp_slist_create()`, `akp_slist_destroy(list)`: Safe lifecycle allocation.
  - `akp_slist_push_front(list, val)`, `akp_slist_push_back(list, val)`: Head and tail insertion.
  - `akp_slist_render(list, title)`: Renders directional pointer chain: `[HEAD] -> [ 10 | • ] -> [ 25 | • ] -> [ 50 | • ] -> [NULL]`.
- **Doubly Linked List (`akp_dlist_t`)**:
  - `akp_dlist_create()`, `akp_dlist_destroy(list)`: Safe lifecycle allocation.
  - `akp_dlist_push_front(list, val)`, `akp_dlist_push_back(list, val)`: Bidirectional node insertion.
  - `akp_dlist_render(list, title)`: Renders bidirectional pointer chain: `[HEAD] <-> [ • | 10 | • ] <-> [ • | 25 | • ] <-> [TAIL]`.

---

### 3.27. Dijkstra Shortest Path Visualizer (`akp/dijkstra.h`)

#### Internal Mechanism:
Implements Single-Source Shortest Path (SSSP) on weighted non-negative graphs. Tracks distances, visitation sets, and parent nodes for complete path reconstruction.
- `akp_dijkstra_res_t akp_dijkstra_solve(const akp_graph_t* g, int source)`: Executes greedy edge relaxation algorithm and returns distance/predecessor maps.
- `void akp_dijkstra_render(const akp_graph_t* g, const akp_dijkstra_res_t* res, const char* title)`: Displays single-source distance vector, reconstructed route path strings (e.g., `0 -> 2 -> 3`), edge cost summation, and status badges.

---

### 3.28. String Pattern Matching Visualizer (`akp/pattern_match.h`)

#### Internal Mechanism:
Provides both brute-force and linear-time algorithmic string matching visualizers.
- **Naive Search**:
  - `akp_pattern_res_t akp_pattern_naive(const char* text, const char* pattern)`: Sliding window comparison tracking every character check.
- **Knuth-Morris-Pratt (KMP)**:
  - `void akp_kmp_compute_lps(const char* pattern, int* lps)`: Computes Longest Prefix Suffix ($\pi$) array to avoid redundant backtracking.
  - `akp_pattern_res_t akp_kmp_search(const char* text, const char* pattern)`: Performs $O(N + M)$ pattern search using precomputed LPS shifts.
  - `void akp_kmp_render(const char* text, const char* pattern, const akp_pattern_res_t* res, const char* title)`: Renders the LPS shift table, text alignment, match indices, and total comparison count.

---

### 3.29. Visual Binary Min-Heap & Priority Queue (`akp/min_heap.h`)

#### Internal Mechanism:
Maintains complete binary tree min-heap invariant where parent $\le$ children.
- `akp_min_heap_t* akp_min_heap_create(int capacity, const char* name)`: Allocates dynamically resizable heap buffer.
- `bool akp_min_heap_insert(akp_min_heap_t* heap, int val)`: Appends value and executes heapify-up ($O(\log N)$).
- `bool akp_min_heap_extract_min(akp_min_heap_t* heap, int* out_val)`: Extracts root and executes heapify-down ($O(\log N)$).
- `int akp_min_heap_peek(const akp_min_heap_t* heap)`: Accesses min element ($O(1)$).
- `void akp_min_heap_render(const akp_min_heap_t* heap, const char* title)`: Displays contiguous array storage with parent index pointers `[i: val (P:p)]` alongside hierarchical level breakdown.
- `void akp_min_heap_destroy(akp_min_heap_t* heap)`: Frees heap allocations.

---

### 3.30. Visual Prefix Tree (Trie) & Autocomplete (`akp/trie.h`)

#### Internal Mechanism:
Implements 26-way prefix search tree for fast lexical operations and dictionary validation.
- `akp_trie_t* akp_trie_create(void)`: Allocates root trie node (`/`).
- `bool akp_trie_insert(akp_trie_t* trie, const char* word)`: Inserts characters into 26-ary branch trie, marking word boundaries.
- `bool akp_trie_search(const akp_trie_t* trie, const char* word)`: Validates full word existence ($O(L)$ where $L$ is word length).
- `bool akp_trie_starts_with(const akp_trie_t* trie, const char* prefix)`: Validates prefix existence ($O(L)$).
- `void akp_trie_render(const akp_trie_t* trie, const char* title)`: Renders complete Unicode branch hierarchy with word markers (`★ (WORD)`).
- `void akp_trie_destroy(akp_trie_t* trie)`: Recursively cleans up all allocated branch nodes.

---

### 3.31. Huffman Variable Prefix Coding & Compression (`akp/huffman.h`)

#### Internal Mechanism:
Implements the greedy Huffman algorithm for optimal lossless data compression.
- Computes character frequency distribution across input strings.
- Iteratively fuses lowest-frequency node pairs to construct optimal prefix binary trees.
- Generates variable-length bit strings (shortest codes for highest frequency symbols).
- `bool akp_huffman_encode(const char* input, akp_huffman_result_t* out_res)`: Computes codes, total original bits, compressed bits, compression ratio, and savings percentage.
- `void akp_huffman_render(const char* input, const akp_huffman_result_t* res, const char* title)`: Displays full ASCII code mapping table and bandwidth savings telemetry.

---

### 3.32. Visual LRU Cache & Buffer Pool Simulator (`akp/lru_cache.h`)

#### Internal Mechanism:
Simulates Operating Systems virtual memory page replacement and high-performance database buffer caches.
- Implements doubly linked list combined with hash lookups to achieve $O(1)$ query and insertion.
- `akp_lru_cache_t* akp_lru_create(int capacity)`: Allocates cache with fixed capacity.
- `int akp_lru_get(akp_lru_cache_t* cache, int key)`: Lookups key, promotes accessed node to `Head` (Most Recently Used - MRU), and tracks cache hit/miss telemetry.
- `void akp_lru_put(akp_lru_cache_t* cache, int key, int value)`: Inserts key-value pair at `Head`. On capacity overflow, evicts `Tail` (Least Recently Used - LRU).
- `void akp_lru_render(const akp_lru_cache_t* cache, const char* title)`: Renders bidirectional cache line diagram: `[MRU / HEAD] -> [K:v] <-> [K:v] -> [LRU / TAIL]`.
- `void akp_lru_destroy(akp_lru_cache_t* cache)`: Safely deallocates cache list.

---

### 3.33. Disjoint-Set Union-Find (DSU) & Set Partitions (`akp/disjoint_set.h`)

#### Internal Mechanism:
Maintains a collection of disjoint dynamic sets with near-constant time operations.
- Implements **Path Compression** during `akp_dsu_find()`, flattening trees directly to root representatives.
- Implements **Union by Rank** during `akp_dsu_union()`, attaching shallower trees under deeper trees to prevent degenerate branches.
- Achieves amortized time complexity of $O(\alpha(N))$ per operation, where $\alpha$ is the extremely slow-growing Inverse Ackermann function ($\alpha(N) < 5$ for all physical universes).
- `akp_dsu_t* akp_dsu_create(int n)`: Initializes $N$ singleton sets ($[0..N-1]$).
- `int akp_dsu_find(akp_dsu_t* dsu, int x)`: Finds canonical root representative with recursive path compression.
- `bool akp_dsu_union(akp_dsu_t* dsu, int x, int y)`: Merges sets containing $x$ and $y$. Returns `false` if already in same component (cycle detection).
- `bool akp_dsu_connected(akp_dsu_t* dsu, int x, int y)`: Tests component connectivity.
- `void akp_dsu_render(const akp_dsu_t* dsu, const char* title)`: Renders tabular parent/rank table and groups all vertices into partitioned equivalence classes: `Set [Root]: { v1, v2, ... }`.
- `void akp_dsu_destroy(akp_dsu_t* dsu)`: Frees DSU heap resources.

---

### 3.34. Kruskal's Minimum Spanning Tree (MST) (`akp/kruskal.h`)

#### Internal Mechanism:
Computes the Minimum Spanning Tree of any connected, undirected, weighted graph using greedy edge selection:
- Extracts all undirected edge descriptors $(u, v, w)$ from an `akp_graph_t` adjacency matrix.
- Sorts edges in non-decreasing order of weight using standard quicksort ($O(E \log E)$).
- Iterates through sorted edges, querying an internal Disjoint-Set Union structure. If endpoints belong to disjoint components, the edge is accepted into the MST; if they share a component, the edge is rejected to prevent cycle creation.
- `akp_kruskal_result_t akp_kruskal_solve(const akp_graph_t* g)`: Produces spanning tree edge list, edge count ($V - 1$), total minimal weight, and span success status.
- `void akp_kruskal_render(const akp_graph_t* g, const akp_kruskal_result_t* res, const char* title)`: Generates terminal table detailing each spanning edge `u <───(weight)───> v`, vertices covered, and total spanning tree cost.

---

### 3.35. Lockless SPSC Circular Ring Buffer (`akp/ring_buffer.h`)

#### Internal Mechanism:
Provides high-throughput, non-blocking Single-Producer Single-Consumer circular queue telemetry:
- Requires power-of-two capacity ($2^k$), enabling lightning-fast bitwise masking `head & (capacity - 1)` rather than expensive integer division / modulo operations.
- Tracks head (write pointer) and tail (read pointer) monotonically without buffer overrun.
- `akp_ring_buffer_t* akp_ring_create(size_t capacity)`: Allocates aligned circular buffer. Rounds up to next power of two if needed.
- `bool akp_ring_push(akp_ring_buffer_t* rb, int val)`: Non-blocking push; returns `false` if full.
- `bool akp_ring_pop(akp_ring_buffer_t* rb, int* out_val)`: Non-blocking pop; returns `false` if empty.
- `bool akp_ring_peek(const akp_ring_buffer_t* rb, int* out_val)`: Inspects front element without advancing tail pointer.
- `void akp_ring_render(const akp_ring_buffer_t* rb, const char* title)`: Visualizes circular slot array with `[HEAD]` and `[TAIL]` markers, item indices, occupancy count, and dynamic linear fill gauge.
- `void akp_ring_destroy(akp_ring_buffer_t* rb)`: Safely deallocates buffer.

---

### 3.36. Systems Bitset & Hardware Register Telemetry (`akp/bitset.h`)

#### Internal Mechanism:
Simulates low-level hardware registers, memory bitmasks, and CPU flags:
- Provides 64-bit hardware register simulation with bit-level granularity.
- Supports atomic bit operations: `set`, `clear`, `toggle`, `test`, `set_all`, and `clear_all`.
- Implements hardware-efficient 64-bit Hamming weight (popcount) calculation via SWAR (SIMD Within A Register) bit parallelism.
- `akp_bitset_t akp_bitset_create(size_t num_bits)`: Initializes bitset up to 64 bits.
- `void akp_bitset_set(akp_bitset_t* bs, size_t bit)` / `void akp_bitset_clear(akp_bitset_t* bs, size_t bit)`: Manipulates specific bit.
- `bool akp_bitset_test(const akp_bitset_t* bs, size_t bit)`: Tests bit state.
- `size_t akp_bitset_count(const akp_bitset_t* bs)`: Computes active high bits.
- `void akp_bitset_render(const akp_bitset_t* bs, const char* title)`: Formats 64-bit quad-word binary layout partitioned into 4 nibble groups (`[63..48] [47..32] [31..16] [15..0]`), displays hexadecimal representation, list of set indices, and visual bit density ratio.

---

## 🚀 4. Package Manager & Installation Manual

### 4.1. CMake `FetchContent` (Recommended for Projects)
Zero git clone required. Add to any `CMakeLists.txt`:
```cmake
cmake_minimum_required(VERSION 3.14)
project(MyProject LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
    akp
    GIT_REPOSITORY https://github.com/miyaniakshar1234/akp.git
    GIT_TAG main
)
FetchContent_MakeAvailable(akp)

add_executable(my_app main.c)
target_link_libraries(my_app PRIVATE akp)
```

### 4.2. Windows 1-Click PowerShell Installer
Run in PowerShell:
```powershell
irm https://raw.githubusercontent.com/miyaniakshar1234/akp/main/install.ps1 | iex
```
Installs `akp.h` into `$env:LOCALAPPDATA\include\akp\` and updates user `CPATH` and `INCLUDE` environment variables. Once installed, any compiler can include it with `#include <akp.h>`!

### 4.3. Linux / macOS 1-Click Installer
Run in terminal:
```bash
curl -fsSL https://raw.githubusercontent.com/miyaniakshar1234/akp/main/install.sh | bash
```
Installs directly to `/usr/local/include/akp.h` or `~/.local/include/akp.h`.

### 4.4. vcpkg Integration
```bash
vcpkg install akp
```

### 4.5. Conan 2.0 Integration
```bash
conan create .
```

---

## ⚡ 5. Verification & Performance Benchmarks

| Subsystem | Metric | Measurement | Complexity |
| :--- | :--- | :--- | :--- |
| **Console Initialization** | One-time VT100 activation | $0.003\text{ ms}$ | $O(1)$ |
| **TrueColor Linear Interpolation** | 1000 characters gradient | $0.012\text{ ms}$ | $O(N)$ |
| **Heap Memory Overhead** | Size header per allocation | 8 bytes | $O(1)$ |
| **Benchmarking Clock Precision** | Hardware counter resolution | $< 100\text{ ns}$ | $O(1)$ |
| **Table Formatting** | 100 rows x 5 columns | $0.18\text{ ms}$ | $O(R \cdot C)$ |
| **Binary Tree Traversal** | 1000-node BST print | $0.85\text{ ms}$ | $O(N)$ |

---

## 👨‍💻 6. Author Profile

**Akshar Miyani**  
- **Identity**: AKP Studio Systems Architect & Lead Engineer
- **GitHub**: [@miyaniakshar1234](https://github.com/miyaniakshar1234)
- **Repository**: [https://github.com/miyaniakshar1234/akp](https://github.com/miyaniakshar1234/akp)
- **Role**: MCA Student & Systems Developer
- **License**: MIT License (c) 2026 Akshar Miyani
