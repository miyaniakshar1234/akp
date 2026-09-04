#!/usr/bin/env bash
# ============================================================================
#  AKP ENGINE - 1-CLICK UNIVERSAL INSTALLER FOR LINUX / MACOS (install.sh)
#  Author: Akshar Miyani | AKP Studio
#  Usage: curl -fsSL https://raw.githubusercontent.com/miyaniakshar1234/akp/main/install.sh | bash
# ============================================================================

set -e

echo -e "\033[1;36m🚀 Installing AKP Flashy Development Toolkit (Author: Akshar Miyani)...\033[0m"

TARGET_DIR="/usr/local/include"
if [ ! -w "$TARGET_DIR" ]; then
    TARGET_DIR="$HOME/.local/include"
    mkdir -p "$TARGET_DIR"
fi

REPO_BASE="https://raw.githubusercontent.com/miyaniakshar1234/akp/main"

mkdir -p "$TARGET_DIR/akp"
curl -fsSL "$REPO_BASE/include/akp.h" -o "$TARGET_DIR/akp.h"
curl -fsSL "$REPO_BASE/include/akp.h" -o "$TARGET_DIR/akp/akp.h"

echo -e "\033[1;32m✔ AKP Engine successfully installed to: $TARGET_DIR/akp.h\033[0m"
echo -e "\033[1;33m⚡ You can now use: #include <akp.h> in any C/C++ project!\033[0m"
echo -e "\033[1;36m   Engineered by Akshar Miyani.\033[0m"
