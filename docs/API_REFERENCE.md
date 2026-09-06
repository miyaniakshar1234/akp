# 📚 AKP ENGINE: COMPLETE API & SUBSYSTEM REFERENCE
### *Technical Specification, Function Signatures & Execution Contracts*
**Architect: Akshar Miyani | AKP Studio**  
*Release: v1.6.0 | Language Targets: C99, C11, C++17, C++20*

---

## 📑 Table of Contents
1. [Core Console & Color Engine](#1-core-console--color-engine)
2. [Branding & Academic Banners](#2-branding--academic-banners)
3. [Timestamped Status Logging](#3-timestamped-status-logging)
4. [Animated Spinners & Progress Bars](#4-animated-spinners--progress-bars)
5. [Unicode Auto-Sizing Tables](#5-unicode-auto-sizing-tables)
6. [Memory Hex-Dump & Heap Auditor](#6-memory-hex-dump--heap-auditor)
7. [Micro-Benchmark Timers](#7-micro-benchmark-timers)
8. [Hardware Audio Sound FX](#8-hardware-audio-sound-fx)
9. [DSA Array & Matrix Visualizers](#9-dsa-array--matrix-visualizers)
10. [Sparklines & 2D Curve Plotter](#10-sparklines--2d-curve-plotter)
11. [Binary Tree Structure Visualizer](#11-binary-tree-structure-visualizer)
12. [Interactive Console Prompts](#12-interactive-console-prompts)
13. [Micro Unit-Testing Framework](#13-micro-unit-testing-framework)
14. [2D Geometric Vector Canvas](#14-2d-geometric-vector-canvas)
15. [Interactive Form Wizard](#15-interactive-form-wizard)
16. [Live In-Terminal Sorting Animator](#16-live-in-terminal-sorting-animator)
17. [Retro Chiptune Synthesizer](#17-retro-chiptune-synthesizer)
18. [Cyberpunk Hardware Telemetry HUD](#18-cyberpunk-hardware-telemetry-hud)
19. [Linear Algebra & Matrix Engine](#19-linear-algebra--matrix-engine)
20. [Modern C++ STL Wrapper (akp.hpp)](#20-modern-c-stl-wrapper-akphpp)
21. [Visual LIFO Stack & Circular FIFO Queue](#21-visual-lifo-stack--circular-fifo-queue)
22. [Visual Linear & Binary Search Visualizer](#22-visual-linear--binary-search-visualizer)
23. [Graph Topology & Adjacency Matrix](#23-graph-topology--adjacency-matrix)
24. [Terminal Color Themes Engine](#24-terminal-color-themes-engine)
25. [Visual Hash Table with Chaining](#25-visual-hash-table-with-chaining)
26. [Visual Singly & Doubly Linked Lists](#26-visual-singly--doubly-linked-lists)
27. [Dijkstra Shortest Path Visualizer](#27-dijkstra-shortest-path-visualizer)
28. [String Pattern Matching Visualizer](#28-string-pattern-matching-visualizer)
29. [Visual Binary Min-Heap & Priority Queue](#29-visual-binary-min-heap--priority-queue)
30. [Visual Prefix Tree (Trie) & Autocomplete Engine](#30-visual-prefix-tree-trie--autocomplete-engine)
31. [Visual Huffman Coding & Data Compression](#31-visual-huffman-coding--data-compression)
32. [Visual LRU Cache & Buffer Pool Simulator](#32-visual-lru-cache--buffer-pool-simulator)

---

## 1. Core Console & Color Engine

Header: `<akp/color.h>` or `<akp.h>`

### `void akp_init_console(void)`
- **Description**: Idempotently configures stdout for UTF-8 code page (65001) and enables VT100 / Virtual Terminal Processing on Windows (`ENABLE_VIRTUAL_TERMINAL_PROCESSING`). No-op on POSIX.
- **Complexity**: $O(1)$

### `akp_rgb_t akp_rgb(uint8_t r, uint8_t g, uint8_t b)`
- **Description**: Constructs an RGB color struct with red, green, and blue byte components.
- **Returns**: `akp_rgb_t`

### `akp_rgb_t akp_hex(uint32_t hex)`
- **Description**: Converts a 24-bit integer hex code (e.g. `0x00FF99`) into an `akp_rgb_t`.
- **Returns**: `akp_rgb_t`

### `void akp_set_fg_rgb(uint8_t r, uint8_t g, uint8_t b)`
- **Description**: Emits ANSI escape sequence `\033[38;2;R;G;Bm` for 24-bit TrueColor foreground.

### `void akp_set_bg_rgb(uint8_t r, uint8_t g, uint8_t b)`
- **Description**: Emits ANSI escape sequence `\033[48;2;R;G;Bm` for 24-bit TrueColor background.

### `void akp_reset_color(void)`
- **Description**: Resets terminal foreground, background, and text styling attributes to default (`\033[0m`).

### `void akp_print_gradient(const char* text, akp_rgb_t start, akp_rgb_t end)`
- **Description**: Computes per-character linear RGB interpolation and prints `text` with a smooth horizontal color gradient.

---

## 2. Branding & Academic Banners

Header: `<akp/banner.h>` or `<akp.h>`

### `void akp_banner(void)`
- **Description**: Displays the signature double-bordered cyberpunk ASCII art splash banner, featuring developer credit to **Akshar Miyani** and **AKP Studio**.

### `void akp_stamp(const char* assignment_name)`
- **Description**: Renders a formal, high-contrast terminal watermark box containing assignment title, developer name, and student credentials.

---

## 3. Timestamped Status Logging

Header: `<akp/badge.h>` or `<akp.h>`

### `void akp_log_success(const char* tag, const char* message)`
- Renders: `[12:34:56] [ ✔ SUCCESS ] [TAG] Message` in bold emerald green.

### `void akp_log_info(const char* tag, const char* message)`
- Renders: `[12:34:56] [ ℹ INFO ] [TAG] Message` in vibrant cyan.

### `void akp_log_warn(const char* tag, const char* message)`
- Renders: `[12:34:56] [ ⚠ WARNING ] [TAG] Message` in golden amber.

### `void akp_log_error(const char* tag, const char* message)`
- Renders: `[12:34:56] [ ✖ ERROR ] [TAG] Message` in high-intensity crimson.

### `void akp_log_akp(const char* tag, const char* message)`
- Renders: `[12:34:56] [ ⚡ AKP-DEV ] [TAG] Message` in neon violet/magenta.

---

## 4. Animated Spinners & Progress Bars

Header: `<akp/progress.h>` or `<akp.h>`

### `const char* akp_spinner_frame(int step)`
- **Description**: Returns 10-frame Unicode braille spinner character (`⠋`, `⠙`, `⠹`, `⠸`, `⠼`, `⠴`, `⠦`, `⠧`, `⠇`, `⠏`) for index `step`.

### `void akp_progress(int current, int total, const char* task_name)`
- **Description**: Emits an in-place updating TrueColor gradient progress bar with braille animation, step counter, and percentage.

---

## 5. Unicode Auto-Sizing Tables

Header: `<akp/table.h>` or `<akp.h>`

### `akp_table_t* akp_table_create(int col_count, ...)`
- **Description**: Allocates a dynamic table with variable column titles.
- **Example**: `akp_table_t* t = akp_table_create(3, "ID", "Name", "Score");`

### `void akp_table_add_row(akp_table_t* table, ...)`
- **Description**: Appends a row of string cells matching `col_count`.

### `void akp_table_render(const akp_table_t* table)`
- **Description**: Computes optimal column widths, renders double-bordered Unicode frame (`╭─┬─╮`, `│ │ │`, `╰─┴─╯`) with alternating row styles.

### `void akp_table_free(akp_table_t* table)`
- **Description**: Deallocates table structure and all stored cells.

---

## 6. Memory Hex-Dump & Heap Auditor

Header: `<akp/memory.h>` or `<akp.h>`

### `void akp_hexdump(const void* ptr, size_t size, const char* label)`
- **Description**: Produces a color-coded hex and ASCII inspector with address offsets, byte classification (zero, printable, non-printable), and boundary borders.

### `void* akp_malloc_tracked(size_t size, const char* file, int line)` / `AKP_MALLOC(sz)`
- **Description**: Allocates `size` bytes wrapped with an internal 8-byte header tracking live heap metrics (active bytes, total allocations, peak usage).

### `void akp_free_tracked(void* ptr, const char* file, int line)` / `AKP_FREE(p)`
- **Description**: Safely releases tracked allocation and deducts from active heap telemetry.

### `void akp_mem_report(void)`
- **Description**: Renders a complete heap health report. If active bytes == 0, flags emerald green zero-leak certification; if active bytes > 0, triggers red alert with leaked byte count.

---

## 7. Micro-Benchmark Timers

Header: `<akp/timer.h>` or `<akp.h>`

### `uint64_t akp_time_now(void)`
- **Description**: Returns monotonic hardware timestamp in microseconds (`QueryPerformanceCounter` on Win32, `clock_gettime(CLOCK_MONOTONIC)` on POSIX).

### `double akp_time_elapsed_ms(uint64_t start_us)`
- **Description**: Computes elapsed duration in floating-point milliseconds.

### `AKP_BENCHMARK(tag) { ... }`
- **Description**: Scoped macro measuring block execution and printing execution duration with badge styling.

---

## 8. Hardware Audio Sound FX

Header: `<akp/sound.h>` or `<akp.h>`

### `void akp_beep(int freq_hz, int duration_ms)`
- Emits raw frequency tone through hardware speaker (`Beep` on Win32, terminal bell on POSIX).

### `void akp_sound_coin(void)`
- Emits two-tone Mario 8-bit coin chime ($988\text{ Hz} \to 1319\text{ Hz}$).

### `void akp_sound_victory(void)`
- Emits retro victory fanfare ($523\text{ Hz} \to 659\text{ Hz} \to 784\text{ Hz} \to 1047\text{ Hz}$).

### `void akp_sound_alert(void)`
- Emits attention buzzer alert ($300\text{ Hz} \to 150\text{ Hz}$).

---

## 9. DSA Array & Matrix Visualizers

Header: `<akp/dsa.h>` or `<akp.h>`

### `void akp_visualize_array(const int* arr, int n, int highlight_idx, const char* label)`
- **Description**: Renders horizontal Unicode bar chart (`█`) scaled to maximum element value with highlight markers (`★`) on `highlight_idx`.

### `void akp_visualize_matrix(const int* matrix, int rows, int cols, const char* label)`
- **Description**: Renders 2D integer matrix enclosed in color-coded bracketed boundaries.

---

## 10. Sparklines & 2D Curve Plotter

Header: `<akp/plot.h>` or `<akp.h>`

### `void akp_sparkline(const double* data, int count, const char* label)`
- **Description**: Quantizes continuous telemetry values into 8-level Unicode sparkline glyphs (` ▂▃▄▅▆▇█`) with minimum, average, and maximum indicators.

### `void akp_plot_function(double (*func)(double), double x_min, double x_max, int width, int height, const char* title)`
- **Description**: Evaluates mathematical function $f(x)$ over $[x_{min}, x_{max}]$ and rasterizes 2D ASCII/Unicode Cartesian coordinate curve.

---

## 11. Binary Tree Structure Visualizer

Header: `<akp/tree.h>` or `<akp.h>`

### `akp_tree_node_t* akp_tree_create(int val, const char* label)`
- Allocates a binary tree node with integer value and metadata label.

### `void akp_tree_insert(akp_tree_node_t* root, int val, const char* label)`
- Performs binary search tree insertion.

### `void akp_tree_visualize(const akp_tree_node_t* root)`
- Renders hierarchical 2D tree topology with branching connectors (`├──`, `└──`).

### `void akp_tree_free(akp_tree_node_t* root)`
- Recursively frees BST nodes.

---

## 12. Interactive Console Prompts

Header: `<akp/prompt.h>` or `<akp.h>`

### `int akp_prompt_confirm(const char* question, int default_yes)`
- Single-keystroke confirmation prompt returning `1` for Yes and `0` for No.

### `void akp_prompt_password(const char* prompt_text, char* buffer, size_t max_len)`
- Reads keyboard input with asterisks/bullets (`•`) masking sensitive passwords.

### `int akp_prompt_select(const char* title, const char** options, int count)`
- Interactive arrow-key navigation menu with high-contrast highlighted cursor.

---

## 13. Micro Unit-Testing Framework

Header: `<akp/test.h>` or `<akp.h>`

### Macros:
- `AKP_TEST(name) { ... }`: Defines an isolated test case block.
- `AKP_ASSERT_EQ(actual, expected)`: Asserts integer equality with file:line reporting.
- `AKP_ASSERT_STR_EQ(actual, expected)`: Asserts string equality.
- `AKP_ASSERT_TRUE(condition)`: Asserts boolean truth.
- `akp_test_summary()`: Prints final test run summary with pass rate and benchmark duration.

---

## 14. 2D Geometric Vector Canvas

Header: `<akp/canvas.h>` or `<akp.h>`

### `akp_canvas_t* akp_canvas_create(int width, int height)`
- Allocates 2D character canvas buffer.

### `void akp_canvas_draw_line(c, x0, y0, x1, y1, ch)`
- Renders line via Bresenham's line algorithm.

### `void akp_canvas_draw_circle(c, cx, cy, radius, ch)`
- Renders circle via Midpoint Circle algorithm.

### `void akp_canvas_draw_rect(c, x, y, w, h, ch)`
- Draws outline rectangle.

### `void akp_canvas_render(const akp_canvas_t* canvas)`
- Flushes canvas buffer to stdout surrounded by borders.

---

## 15. Interactive Form Wizard

Header: `<akp/form.h>` or `<akp.h>`

### `akp_form_t* akp_form_create(const char* title)`
- Creates multi-field interactive form.

### `void akp_form_add_field(form, key, label, is_secret)`
- Appends input field with optional password masking.

### `int akp_form_execute(form)`
- Interactively prompts user through each field with input validation.

### `const char* akp_form_get(form, key)`
- Retrieves entered value for field `key`.

---

## 16. Live In-Terminal Sorting Animator

Header: `<akp/sort_anim.h>` or `<akp.h>`

### `void akp_sort_anim_bubble(int* arr, int n, int delay_ms)`
- In-place terminal animated Bubble Sort with swap and comparison counters.

### `void akp_sort_anim_selection(int* arr, int n, int delay_ms)`
- In-place animated Selection Sort with minimum index indicators.

### `void akp_sort_anim_insertion(int* arr, int n, int delay_ms)`
- In-place animated Insertion Sort with active key placement visualizer.

---

## 17. Retro Chiptune Synthesizer

Header: `<akp/melody.h>` or `<akp.h>`

### `void akp_melody_tetris(void)`
- Plays classic 8-bit Tetris Type-A Korobeiniki theme.

### `void akp_melody_starwars(void)`
- Plays Star Wars Imperial March score.

### `void akp_melody_nokia(void)`
- Plays nostalgic Nokia ringtone.

---

## 18. Cyberpunk Hardware Telemetry HUD

Header: `<akp/sysinfo.h>` or `<akp.h>`

### `akp_sysinfo_t akp_sysinfo_get(void)`
- Inspects physical and logical system memory and CPU cores.

### `void akp_sysinfo_render_hud(void)`
- Renders double-bordered cyberpunk diagnostic HUD with RAM percentage gauge.

---

## 19. Linear Algebra & Matrix Engine

Header: `<akp/matrix.h>` or `<akp.h>`

### `akp_mat_t* akp_mat_create(int rows, int cols)`
- Allocates heap-managed 2D matrix buffer.

### `akp_mat_t* akp_mat_multiply(const akp_mat_t* A, const akp_mat_t* B)`
- Multiplies matrices ($A \times B$) with dimension compatibility verification.

### `akp_mat_t* akp_mat_transpose(const akp_mat_t* m)`
- Computes matrix transpose ($m^T$).

### `float akp_mat_det3x3(const akp_mat_t* m)`
- Calculates determinant for $3 \times 3$ matrix.

### `void akp_mat_render(const akp_mat_t* m, const char* title)`
- Renders color-bracketed floating-point grid.

---

## 20. Modern C++ STL Wrapper (`akp.hpp`)

Header: `<akp.hpp>`

### Classes & Namespaces:
- `akp::RGB(r, g, b)`: C++ type-safe RGB structure.
- `akp::ScopedTimer timer("Benchmark")`: RAII scoped execution timer.
- `akp::Table table({"Col1", "Col2"})`: STL `std::string` table builder.
- `akp::Canvas canvas(width, height)`: Object-oriented vector drawing canvas.
- `akp::sparkline(std::vector<double>, label)`: STL container sparkline formatter.

---

## 21. Visual LIFO Stack & Circular FIFO Queue

Header: `<akp/stack_queue.h>` or `<akp.h>`

### `akp_stack_t* akp_stack_create(int capacity, const char* name)`
- Allocates heap-managed LIFO stack structure.

### `int akp_stack_push(akp_stack_t* s, int value)`
- Pushes integer onto stack with overflow guard. Returns `1` on success, `0` on overflow.

### `int akp_stack_pop(akp_stack_t* s, int* out_value)`
- Pops top integer with underflow guard.

### `void akp_stack_render(const akp_stack_t* s)`
- Renders vertical graphical stack with pointer indicators (`TOP ->`, `BOT ->`) and load percentage gauge.

### `akp_queue_t* akp_queue_create(int capacity, const char* name)`
- Allocates circular FIFO queue.

### `int akp_queue_enqueue(akp_queue_t* q, int value)`
- Enqueues element with circular modulo index arithmetic.

### `int akp_queue_dequeue(akp_queue_t* q, int* out_value)`
- Dequeues element from front of queue.

### `void akp_queue_render(const akp_queue_t* q)`
- Renders horizontal circular queue buffer with dynamic `F` (front) and `R` (rear) cursor markers.

---

## 22. Visual Linear & Binary Search Visualizer

Header: `<akp/search_anim.h>` or `<akp.h>`

### `int akp_search_linear(const int* arr, int n, int target)`
- Performs step-by-step in-terminal linear search ($O(N)$) with color comparison flags. Returns index or `-1`.

### `int akp_search_binary(const int* arr, int n, int target)`
- Performs animated binary search ($O(\log N)$) rendering active window subarray, `Low`, `Mid`, `High` pointers, and search partition rationale.

---

## 23. Graph Topology & Adjacency Matrix

Header: `<akp/graph.h>` or `<akp.h>`

### `akp_graph_t* akp_graph_create(int vertices, int is_directed)`
- Allocates graph topology container with maximum 32 vertices.

### `void akp_graph_add_edge(akp_graph_t* g, int u, int v, int weight)`
- Adds weighted edge between vertices `u` and `v`.

### `void akp_graph_render_adj_matrix(const akp_graph_t* g, const char* title)`
- Renders 2D adjacency matrix table in terminal with color-highlighted weights.

### `void akp_graph_bfs(const akp_graph_t* g, int start_vertex)`
- Traverses graph via Breadth-First Search and prints traversal sequence.

### `void akp_graph_dfs(const akp_graph_t* g, int start_vertex)`
- Traverses graph via Depth-First Search and prints traversal sequence.

---

## 24. Terminal Color Themes Engine

Header: `<akp/theme.h>` or `<akp.h>`

### `akp_theme_t akp_theme_get(akp_theme_id_t id)`
- Retrieves color scheme struct for `AKP_THEME_CYBERPUNK`, `AKP_THEME_MATRIX`, `AKP_THEME_SYNTHWAVE`, `AKP_THEME_DRACULA`, `AKP_THEME_MONOKAI`.

### `void akp_theme_preview(akp_theme_id_t id)`
- Prints colored swatches for primary, secondary, and accent TrueColors.

---

## 25. Visual Hash Table with Chaining

Header: `<akp/hash_table.h>` or `<akp.h>`

### `akp_ht_t* akp_ht_create(int num_buckets)`
- Allocates a dynamically sized hash table with separate chaining buckets.
- **Parameters**: `num_buckets` (recommended prime number or power of two).
- **Returns**: Pointer to initialized `akp_ht_t`.
- **Complexity**: $O(B)$ where $B$ is number of buckets.

### `bool akp_ht_insert(akp_ht_t* ht, const char* key, int value)`
- Inserts or updates a key-value mapping. Traverses bucket chain to update existing keys or appends a new node.
- **Complexity**: $O(1)$ average, $O(N)$ worst case under severe collision.

### `bool akp_ht_get(const akp_ht_t* ht, const char* key, int* out_val)`
- Lookups `key` in bucket chain, storing result in `*out_val`.
- **Returns**: `true` if found, `false` otherwise.
- **Complexity**: $O(1)$ average.

### `void akp_ht_render(const akp_ht_t* ht, const char* title)`
- Renders full bucket diagram with pointer arrows, element count, collision count, max chain depth, and load factor ($\alpha = N / B$).

### `void akp_ht_destroy(akp_ht_t* ht)`
- Deallocates all node chains and bucket arrays.

---

## 26. Visual Singly & Doubly Linked Lists

Header: `<akp/linked_list.h>` or `<akp.h>`

### `akp_slist_t* akp_slist_create(void)` / `void akp_slist_destroy(akp_slist_t* list)`
- Allocates and frees a singly linked list container.

### `void akp_slist_push_front(akp_slist_t* list, int val)` / `void akp_slist_push_back(akp_slist_t* list, int val)`
- Inserts element at head ($O(1)$) or tail ($O(N)$) of singly linked list.

### `void akp_slist_render(const akp_slist_t* list, const char* title)`
- Renders singly linked list chain: `[HEAD] -> [ 10 | • ] -> [ 25 | • ] -> [NULL]`.

### `akp_dlist_t* akp_dlist_create(void)` / `void akp_dlist_destroy(akp_dlist_t* list)`
- Allocates and frees a doubly linked list container.

### `void akp_dlist_push_front(akp_dlist_t* list, int val)` / `void akp_dlist_push_back(akp_dlist_t* list, int val)`
- Inserts element at head ($O(1)$) or tail ($O(1)$ via tail pointer) of doubly linked list.

### `void akp_dlist_render(const akp_dlist_t* list, const char* title)`
- Renders doubly linked list chain: `[HEAD] <-> [ • | 10 | • ] <-> [ • | 25 | • ] <-> [TAIL]`.

---

## 27. Dijkstra Shortest Path Visualizer

Header: `<akp/dijkstra.h>` or `<akp.h>`

### `akp_dijkstra_res_t akp_dijkstra_solve(const akp_graph_t* g, int source)`
- Computes single-source shortest paths on weighted graph with non-negative edges using greedy relaxation.
- **Returns**: `akp_dijkstra_res_t` struct containing `dist[]`, `parent[]`, and visitation status.
- **Complexity**: $O(V^2)$ (dense matrix).

### `void akp_dijkstra_render(const akp_graph_t* g, const akp_dijkstra_res_t* res, const char* title)`
- Renders routing table with columns: Destination, Cost / Distance, Full Traversed Path (e.g. `0 -> 2 -> 3`), and Status badge.

---

## 28. String Pattern Matching Visualizer

Header: `<akp/pattern_match.h>` or `<akp.h>`

### `akp_pattern_res_t akp_pattern_naive(const char* text, const char* pattern)`
- Brute-force substring search tracking all character comparisons.
- **Complexity**: $O(N \cdot M)$.

### `void akp_kmp_compute_lps(const char* pattern, int* lps)`
- Computes Longest Prefix Suffix ($\pi$) lookup table for Knuth-Morris-Pratt search.
- **Complexity**: $O(M)$.

### `akp_pattern_res_t akp_kmp_search(const char* text, const char* pattern)`
- Performs linear time Knuth-Morris-Pratt pattern search using LPS jump shifts.
- **Complexity**: $O(N + M)$.

### `void akp_kmp_render(const char* text, const char* pattern, const akp_pattern_res_t* res, const char* title)`
- Displays LPS table, text length, pattern length, match occurrences, and total comparison count.

---

## 29. Visual Binary Min-Heap & Priority Queue

Header: `<akp/min_heap.h>` or `<akp.h>`

### `akp_min_heap_t* akp_min_heap_create(int capacity, const char* name)`
- Allocates a dynamically resizable binary min-heap buffer.
- **Complexity**: $O(1)$.

### `bool akp_min_heap_insert(akp_min_heap_t* heap, int val)`
- Inserts `val` and restores heap property via heapify-up.
- **Complexity**: $O(\log N)$.

### `bool akp_min_heap_extract_min(akp_min_heap_t* heap, int* out_val)`
- Extracts root element, relocates tail to root, and restores min-heap property via heapify-down.
- **Complexity**: $O(\log N)$.

### `int akp_min_heap_peek(const akp_min_heap_t* heap)`
- Returns root minimum value without extracting.
- **Complexity**: $O(1)$.

### `void akp_min_heap_render(const akp_min_heap_t* heap, const char* title)`
- Renders linear array representation with parent indices and hierarchical tree level breakdown.

### `void akp_min_heap_destroy(akp_min_heap_t* heap)`
- Deallocates dynamic array and heap structure.

---

## 30. Visual Prefix Tree (Trie) & Autocomplete Engine

Header: `<akp/trie.h>` or `<akp.h>`

### `akp_trie_t* akp_trie_create(void)` / `void akp_trie_destroy(akp_trie_t* trie)`
- Allocates and deallocates 26-way prefix trie.

### `bool akp_trie_insert(akp_trie_t* trie, const char* word)`
- Inserts lowercase alphabetic word into trie, tracking unique nodes and terminal boundaries.
- **Complexity**: $O(L)$ where $L$ is word length.

### `bool akp_trie_search(const akp_trie_t* trie, const char* word)`
- Returns `true` if full word exists in trie.
- **Complexity**: $O(L)$.

### `bool akp_trie_starts_with(const akp_trie_t* trie, const char* prefix)`
- Returns `true` if any word in trie begins with `prefix`.
- **Complexity**: $O(L)$.

### `void akp_trie_render(const akp_trie_t* trie, const char* title)`
- Renders hierarchical Unicode branch diagram with terminal word markers (`★ (WORD)`).

---

## 31. Visual Huffman Coding & Data Compression

Header: `<akp/huffman.h>` or `<akp.h>`

### `bool akp_huffman_encode(const char* input, akp_huffman_result_t* out_res)`
- Computes character frequencies, builds greedy binary merge tree, and generates prefix bit codes.
- **Complexity**: $O(N + U \log U)$ where $N$ is text length and $U$ is unique characters.

### `void akp_huffman_render(const char* input, const akp_huffman_result_t* res, const char* title)`
- Displays frequency and code mapping table, original bits vs compressed bits, and bandwidth savings percentage.

---

## 32. Visual LRU Cache & Buffer Pool Simulator

Header: `<akp/lru_cache.h>` or `<akp.h>`

### `akp_lru_cache_t* akp_lru_create(int capacity)` / `void akp_lru_destroy(akp_lru_cache_t* cache)`
- Allocates and frees fixed-capacity LRU cache structure.

### `int akp_lru_get(akp_lru_cache_t* cache, int key)`
- Lookups key. If present, promotes node to MRU / Head and increments hit counter. Returns value or `-1`.
- **Complexity**: $O(1)$ average.

### `void akp_lru_put(akp_lru_cache_t* cache, int key, int value)`
- Inserts or updates key-value pair at MRU / Head. If capacity exceeded, evicts LRU / Tail node.
- **Complexity**: $O(1)$.

### `void akp_lru_render(const akp_lru_cache_t* cache, const char* title)`
- Renders cache line order: `[MRU / HEAD] -> [K:v] <-> [K:v] -> [LRU / TAIL]` with occupancy and hit ratio telemetry.

---

**Engineered by Akshar Miyani | AKP Studio**  
*Master of Computer Applications (MCA)*
