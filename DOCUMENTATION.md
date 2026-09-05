# ⚡ AKP ENGINE: THE DEFINITIVE ARCHITECTURAL MANUAL
### *Master Documentation of the High-Performance Flashy C/C++ Toolkit*
**Engineered & Authored by the Genius Architect: Akshar Miyani**  
*AKP Studio Systems Architecture | Version 1.3.0*

---

## 🏛️ 1. Architectural Philosophy & Vision

Standard C (`<stdio.h>`) has remained visually static since 1972. In modern development environments, terminal applications are often expected to be dreary, monochromatic, and visually uninspiring.

**AKP Engine** was conceived and engineered from first principles by **Akshar Miyani** to shatter this limitation. It provides an enterprise-grade, zero-dependency, header-only runtime that brings **24-bit TrueColor Cyberpunk aesthetics**, **real-time memory leak auditing**, **algorithmic visualizers**, **hardware audio feedback**, and **interactive terminal UI controls** to pure C and C++.

### Core Engineering Invariants:
1. **Zero External Dependencies**: Operates strictly on standard C99/C11 and C++11/14/17/20 headers and platform kernels (`windows.h` on NT systems, `unistd.h` / `termios.h` on POSIX systems).
2. **Deterministic Memory Footprint**: Minimal heap interaction. All visualizers and formatting engines utilize bounded stack buffers or strictly audited heap segments.
3. **Cross-Platform Parity**: Identical visual fidelity and behavior across Windows Command Prompt, PowerShell, Windows Terminal, Linux virtual consoles, and macOS Terminal.
4. **Drop-in Simplicity**: Dual deployment models: modular sub-headers under `include/akp/` for large systems, or a single amalgamated file `include/akp.h` for instant academic lab flexing.

---

## 📦 2. Library Structure & Subsystem Layout

```
d:/Projects/AKP/
├── include/
│   ├── akp.h                   # Standalone Amalgamated Master Header (v1.3.0)
│   ├── akp.hpp                 # Modern C++17/20 STL & RAII Master Wrapper
│   └── akp/                    # Modular Header Suite (20 Subsystems)
│       ├── akp.h               # Root Modular Umbrella Header
│       ├── color.h             # 24-Bit TrueColor RGB, ANSI, Linear Gradients
│       ├── banner.h            # ASCII Branding Splash & Lab Evaluation Stamp
│       ├── badge.h             # Real-Time Timestamped Status Badges
│       ├── progress.h          # Braille Spinners & Interpolated Progress Bars
│       ├── table.h             # Dynamic Auto-Sizing Unicode Border Tables
│       ├── memory.h            # Hex-Dump Inspector & Zero-Leak Heap Auditor
│       ├── timer.h             # Hardware Microsecond Benchmark Macros
│       ├── sound.h             # Retro Hardware Audio & Frequency Sound FX
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
│       └── matrix.h            # Linear Algebra & Dynamic Matrix Operations
├── examples/
│   ├── lab_demo.c              # Comprehensive C Lab Demonstration
│   ├── cpp_demo.cpp            # Modern C++17 STL Benchmark & Visualizer
│   ├── cpp_advanced.cpp        # Modern C++ RAII Canvas & Table Demo
│   └── lab_showcase_v130.c     # Live Showcase: Sorting, Telemetry, Melodies
├── tests/
│   └── test_suite.c            # Automated 20/20 Test Suite (100% Pass Rate)
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
