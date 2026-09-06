/**
 * ============================================================================
 * AKP ENGINE - HIGH PERFORMANCE C/C++ FLASHY TOOLKIT
 * SUBSYSTEM: huffman.h (Visual Huffman Coding & Data Compression Visualizer)
 * 
 * Engineered & Authored by: Akshar Miyani
 * AKP Studio Systems Architecture | Release v1.6.0
 * ============================================================================
 */

#ifndef AKP_HUFFMAN_H
#define AKP_HUFFMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "color.h"
#include "badge.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct akp_huffman_node {
    char ch;
    int freq;
    struct akp_huffman_node* left;
    struct akp_huffman_node* right;
} akp_huffman_node_t;

typedef struct {
    char ch;
    char code[32];
    int freq;
} akp_huffman_code_t;

typedef struct {
    akp_huffman_code_t codes[256];
    int unique_chars;
    int original_bits;
    int compressed_bits;
    double compression_ratio;
    double savings_percent;
} akp_huffman_result_t;

static inline akp_huffman_node_t* akp_huffman_create_node(char ch, int freq) {
    akp_huffman_node_t* node = (akp_huffman_node_t*)malloc(sizeof(akp_huffman_node_t));
    if (!node) return NULL;
    node->ch = ch;
    node->freq = freq;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static inline void akp_huffman_free_tree(akp_huffman_node_t* root) {
    if (!root) return;
    akp_huffman_free_tree(root->left);
    akp_huffman_free_tree(root->right);
    free(root);
}

static inline void akp_huffman_generate_codes(akp_huffman_node_t* root, char* prefix, int depth, akp_huffman_result_t* res) {
    if (!root) return;

    if (!root->left && !root->right) {
        prefix[depth] = '\0';
        for (int i = 0; i < res->unique_chars; i++) {
            if (res->codes[i].ch == root->ch) {
                if (depth == 0) {
                    strcpy(res->codes[i].code, "0");
                } else {
                    strcpy(res->codes[i].code, prefix);
                }
                break;
            }
        }
        return;
    }

    if (root->left) {
        prefix[depth] = '0';
        akp_huffman_generate_codes(root->left, prefix, depth + 1, res);
    }
    if (root->right) {
        prefix[depth] = '1';
        akp_huffman_generate_codes(root->right, prefix, depth + 1, res);
    }
}

static inline bool akp_huffman_encode(const char* input, akp_huffman_result_t* out_res) {
    if (!input || !out_res) return false;
    memset(out_res, 0, sizeof(akp_huffman_result_t));

    int len = (int)strlen(input);
    if (len == 0) return false;

    // 1. Calculate frequencies
    int freqs[256] = {0};
    for (int i = 0; i < len; i++) {
        freqs[(unsigned char)input[i]]++;
    }

    akp_huffman_node_t* forest[256];
    int forest_size = 0;

    for (int i = 0; i < 256; i++) {
        if (freqs[i] > 0) {
            forest[forest_size] = akp_huffman_create_node((char)i, freqs[i]);
            out_res->codes[forest_size].ch = (char)i;
            out_res->codes[forest_size].freq = freqs[i];
            forest_size++;
        }
    }
    out_res->unique_chars = forest_size;

    // 2. Build Tree iteratively using min pairs
    while (forest_size > 1) {
        // Find two smallest nodes
        int min1 = 0, min2 = 1;
        if (forest[min1]->freq > forest[min2]->freq) {
            int t = min1; min1 = min2; min2 = t;
        }
        for (int i = 2; i < forest_size; i++) {
            if (forest[i]->freq < forest[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (forest[i]->freq < forest[min2]->freq) {
                min2 = i;
            }
        }

        akp_huffman_node_t* parent = akp_huffman_create_node('$', forest[min1]->freq + forest[min2]->freq);
        parent->left = forest[min1];
        parent->right = forest[min2];

        // Replace min1 with parent and remove min2
        forest[min1] = parent;
        forest[min2] = forest[forest_size - 1];
        forest_size--;
    }

    akp_huffman_node_t* root = forest[0];
    char prefix[64];
    akp_huffman_generate_codes(root, prefix, 0, out_res);
    akp_huffman_free_tree(root);

    // 3. Compute Metrics
    out_res->original_bits = len * 8;
    out_res->compressed_bits = 0;
    for (int i = 0; i < out_res->unique_chars; i++) {
        out_res->compressed_bits += out_res->codes[i].freq * (int)strlen(out_res->codes[i].code);
    }

    if (out_res->original_bits > 0) {
        out_res->compression_ratio = (double)out_res->original_bits / (double)out_res->compressed_bits;
        out_res->savings_percent = ((double)(out_res->original_bits - out_res->compressed_bits) / (double)out_res->original_bits) * 100.0;
    }

    return true;
}

static inline void akp_huffman_render(const char* input, const akp_huffman_result_t* res, const char* title) {
    akp_init_console();
    printf("\n");
    akp_set_fg_rgb(0, 255, 230);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  📦 HUFFMAN OPTIMAL PREFIX CODING & DATA COMPRESSION ENGINE                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    akp_reset_color();

    if (title) {
        akp_set_fg_rgb(255, 215, 0);
        printf("  ⚡ Dataset: %s\n", title);
        akp_reset_color();
    }

    if (!res || res->unique_chars == 0) {
        akp_set_fg_rgb(255, 70, 85);
        printf("  [ Empty dataset for Huffman encoding ]\n\n");
        akp_reset_color();
        return;
    }

    akp_set_fg_rgb(0, 255, 170);
    printf("  Original Text: \"%s\" (Length: %zu chars)\n", input ? input : "N/A", input ? strlen(input) : 0);
    printf("  Original Size:   %d bits (%d bytes)\n", res->original_bits, res->original_bits / 8);
    printf("  Compressed Size: %d bits (%.1f bytes)\n", res->compressed_bits, (double)res->compressed_bits / 8.0);
    printf("  Bandwidth Savings: %.2f%%  |  Ratio: %.2f:1\n\n", res->savings_percent, res->compression_ratio);
    akp_reset_color();

    // Table of character codes
    akp_set_fg_rgb(255, 0, 128);
    printf("  ┌───────────┬─────────────┬───────────────────────────┐\n");
    printf("  │ Character │  Frequency  │  Generated Variable Code  │\n");
    printf("  ├───────────┼─────────────┼───────────────────────────┤\n");
    akp_reset_color();

    for (int i = 0; i < res->unique_chars; i++) {
        char display_c = res->codes[i].ch;
        if (display_c == ' ') {
            printf("  │  [SPACE]  │ %11d │  ", res->codes[i].freq);
        } else if (display_c == '\n') {
            printf("  │  [NEWL]   │ %11d │  ", res->codes[i].freq);
        } else {
            printf("  │     '%c'   │ %11d │  ", display_c, res->codes[i].freq);
        }
        akp_set_fg_rgb(0, 200, 255);
        printf("%-25s", res->codes[i].code);
        akp_reset_color();
        printf("│\n");
    }

    akp_set_fg_rgb(255, 0, 128);
    printf("  └───────────┴─────────────┴───────────────────────────┘\n\n");
    akp_reset_color();
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_HUFFMAN_H */
