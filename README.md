# 🚀 AKP Engine: Flashy C & C++ Development Toolkit

<div align="center">

```
  █████╗ ██╗  ██╗██████╗      ███████╗███╗   ██╗ ██████╗ ██╗███╗   ██╗███████╗
 ██╔══██╗██║ ██╔╝██╔══██╗     ██╔════╝████╗  ██║██╔════╝ ██║████╗  ██║██╔════╝
 ███████║█████═╝ ██████╔╝     █████╗  ██╔██╗ ██║██║  ███╗██║██╔██╗ ██║█████╗  
 ██╔══██║██╔═██╗ ██╔═══╝      ██╔══╝  ██║╚██╗██║██║   ██║██║██║╚██╗██║██╔══╝  
 ██║  ██║██║ ╚██╗██║          ███████╗██║ ╚████║╚██████╔╝██║██║ ╚████║███████╗
 ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝          ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝╚═╝  ╚═══╝╚══════╝
```

**Ultra-Flashy Terminal Output & High-Performance C/C++ Toolkit**  
*Engineered by **Akshar Miyani** | AKP Studio*

[![CI](https://github.com/miyaniakshar1234/akp/actions/workflows/ci.yml/badge.svg)](https://github.com/miyaniakshar1234/akp/actions)
[![Language](https://img.shields.io/badge/Language-C99%20%7C%20C11%20%7C%20C%2B%2B17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Author](https://img.shields.io/badge/Author-Akshar%20Miyani-blueviolet.svg)](https://github.com/miyaniakshar1234)
[![Single Header](https://img.shields.io/badge/Drop--in-Single%20Header-brightgreen.svg)](#single-header-drop-in)

</div>

---

Standard C (`<stdio.h>`) outputs plain, black-and-white text. **`AKP`** turns your terminal into a glowing, Cyberpunk-styled development dashboard with zero dependencies. Drop it into your college lab assignments or production systems to instantly impress everyone in the room.

<div align="center">

[📖 **Architectural Manual**](DOCUMENTATION.md) &nbsp;•&nbsp; [🎓 **Lab Flex Guide**](docs/LAB_FLEX_GUIDE.md) &nbsp;•&nbsp; [📚 **API Reference**](docs/API_REFERENCE.md) &nbsp;•&nbsp; [🚀 **Releases**](https://github.com/miyaniakshar1234/akp/releases)

</div>

---

## ✨ Features

- 🌈 **24-Bit TrueColor RGB & Neon Gradients**: Cyberpunk palette (Cyan, Pink, Purple, Acid Green, Gold, Fire Orange) with linear interpolation.
- 👑 **Author Identity Banners**: Neon ASCII art branding by Akshar Miyani with lab evaluation stamps.
- 🏷️ **High-Visibility Badges**: Live-timestamped status tags (`[ ✔ SUCCESS ]`, `[ ℹ INFO ]`, `[ ⚠ WARNING ]`, `[ ✖ ERROR ]`, `[ ⚡ AKP-DEV ]`).
- 📊 **Animated Spinners & Progress Bars**: Smooth gradient progress bars with percentages, steps, and braille spinners.
- 📋 **Auto-Sizing Tables**: Rounded Unicode borders (`╭─┬─╮`, `│ │ │`, `╰─┴─╯`) with alternating row styles.
- 🔍 **Color-Coded Memory Hex-Dump**: Memory offsets, categorized byte colors, and ASCII inspection.
- 🛡️ **Zero-Leak Heap Allocation Auditor**: `AKP_MALLOC` & `AKP_FREE` tracker reporting live allocations, frees, peak memory, and leak detection.
- ⏱️ **Micro-Benchmark Timer**: Microsecond/nanosecond block execution timers (`AKP_BENCHMARK("Quicksort") { ... }`).
- 🔊 **Retro Audio Effects**: Mario 8-bit coin chime, victory fanfare, and alert buzzers using hardware frequencies.
- 📈 **DSA & Matrix Visualizers**: Horizontal in-terminal bar charts with selected element highlights and color-bracketed matrices.
- 🌳 **Hierarchical Binary Tree Visualizer**: Horizontal branch layout (`┌──`, `│`, `└──`) for binary search trees and heaps.
- 📐 **2D Function Plotter & Sparklines**: Rasterizes mathematical functions, complexity curves, and 8-level Unicode sparklines (` ▂▃▄▅▆▇█`).
- 🎨 **2D Geometric Terminal Canvas**: In-terminal vector canvas drawing lines (Bresenham's algorithm), rectangles, circles, and text.
- 🧪 **Micro Unit-Testing Framework**: Macro-based test suite (`AKP_TEST`, `AKP_ASSERT_EQ`) with pass-rate audits and Mario success chimes.
- 🎬 **Real-Time Live Sorting Animator**: Watch Bubble, Selection, and Insertion sorts animate directly in your console with in-place frame redraws!
- 💻 **Hardware Telemetry Dashboard**: Live CPU architecture, core count, total RAM, free RAM, and graphical memory gauge bar (`akp_sysinfo_render`).
- 🎵 **Retro 8-Bit Melody Synthesizer**: Plays Tetris (Korobeiniki), Star Wars Imperial March, and Nokia tunes through motherboard frequencies.
- 📋 **Interactive Form Wizard**: Bordered dialogs capturing multi-type user inputs (text, numbers, confirmation checks).
- 🔢 **Linear Algebra & Matrix Math**: Formatted bracketed matrix operations (multiplication, transpose, 3x3 determinant).
- ❓ **Interactive CLI Prompts**: Arrow-key menu selector (`akp_prompt_select`), single-key confirmations (`[y/N]`), and masked password inputs (`••••••`).

---

## ⚡ Installation & Package Manager Support

### 1. CMake `FetchContent` (Zero Git Clone Required)
Add this to your `CMakeLists.txt`:
```cmake
include(FetchContent)
FetchContent_Declare(
    akp
    GIT_REPOSITORY https://github.com/miyaniakshar1234/akp.git
    GIT_TAG main
)
FetchContent_MakeAvailable(akp)

target_link_libraries(my_lab_project PRIVATE akp)
```

### 2. Universal 1-Line Installers
#### Windows (PowerShell):
```powershell
irm https://raw.githubusercontent.com/miyaniakshar1234/akp/main/install.ps1 | iex
```
*Installs to `%LOCALAPPDATA%\include` and automatically configures `CPATH` & `INCLUDE`.*

#### Linux / macOS (Bash):
```bash
curl -fsSL https://raw.githubusercontent.com/miyaniakshar1234/akp/main/install.sh | bash
```

### 3. vcpkg
```bash
vcpkg install akp
```

### 4. Conan 2.0
```bash
conan create .
```

### 5. Single Header Drop-In
Download `include/akp.h` directly into your project folder:
```c
#include "akp.h"
```

---

## 🚀 Quick Start Example

```c
#include "akp.h"

int main(void) {
    // 1. Splash Banner & Stamp
    akp_banner();
    akp_stamp("Lab Assignment #01");

    // 2. Play Audio FX
    akp_sound_coin();

    // 3. Status Badges
    akp_log_akp("DEMO", "AKP Toolkit running for Akshar Miyani.");

    // 4. Gradient Progress Bar
    for (int i = 1; i <= 30; i++) {
        akp_progress(i, 30, "Sorting Dataset");
        #if AKP_PLATFORM_WINDOWS
            Sleep(20);
        #else
            usleep(20000);
        #endif
    }

    // 5. Memory Hex-Dump & Leak Tracking
    int* buffer = (int*)AKP_MALLOC(16 * sizeof(int));
    for (int i = 0; i < 16; i++) buffer[i] = i * 7;
    akp_hexdump(buffer, 16 * sizeof(int), "Heap Integer Buffer");

    // 6. Benchmarking
    AKP_BENCHMARK("Algorithm Benchmark") {
        akp_visualize_array(buffer, 8, 3, "Visual Bar Chart");
    }

    // 7. Clean Memory Audit
    AKP_FREE(buffer);
    akp_mem_report();

    return 0;
}
```

---

## 👨‍💻 Author

**Akshar Miyani**  
- **GitHub**: [@miyaniakshar1234](https://github.com/miyaniakshar1234)
- **Email**: miyaniakshar1234@gmail.com
- **Role**: MCA Student & Systems Developer

---

## 📄 License

Distributed under the [MIT License](LICENSE). Copyright (c) 2026 Akshar Miyani.
