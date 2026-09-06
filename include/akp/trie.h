/**
 * ============================================================================
 * AKP ENGINE - HIGH PERFORMANCE C/C++ FLASHY TOOLKIT
 * SUBSYSTEM: trie.h (Visual Prefix Tree & Autocomplete Engine)
 * 
 * Engineered & Authored by: Akshar Miyani
 * AKP Studio Systems Architecture | Release v1.6.0
 * ============================================================================
 */

#ifndef AKP_TRIE_H
#define AKP_TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "color.h"
#include "badge.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AKP_TRIE_ALPHABET_SIZE 26

typedef struct akp_trie_node {
    struct akp_trie_node* children[AKP_TRIE_ALPHABET_SIZE];
    bool is_end_of_word;
    char ch;
} akp_trie_node_t;

typedef struct {
    akp_trie_node_t* root;
    int word_count;
    int node_count;
} akp_trie_t;

static inline akp_trie_node_t* akp_trie_node_create(char ch) {
    akp_trie_node_t* node = (akp_trie_node_t*)malloc(sizeof(akp_trie_node_t));
    if (!node) return NULL;
    node->is_end_of_word = false;
    node->ch = ch;
    for (int i = 0; i < AKP_TRIE_ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

static inline akp_trie_t* akp_trie_create(void) {
    akp_trie_t* trie = (akp_trie_t*)malloc(sizeof(akp_trie_t));
    if (!trie) return NULL;
    trie->root = akp_trie_node_create('/');
    trie->word_count = 0;
    trie->node_count = 1;
    return trie;
}

static inline void akp_trie_destroy_nodes(akp_trie_node_t* node) {
    if (!node) return;
    for (int i = 0; i < AKP_TRIE_ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            akp_trie_destroy_nodes(node->children[i]);
        }
    }
    free(node);
}

static inline void akp_trie_destroy(akp_trie_t* trie) {
    if (!trie) return;
    if (trie->root) akp_trie_destroy_nodes(trie->root);
    free(trie);
}

static inline bool akp_trie_insert(akp_trie_t* trie, const char* word) {
    if (!trie || !word || !trie->root) return false;
    akp_trie_node_t* curr = trie->root;
    int len = (int)strlen(word);

    for (int i = 0; i < len; i++) {
        char c = (char)tolower((unsigned char)word[i]);
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';

        if (!curr->children[idx]) {
            curr->children[idx] = akp_trie_node_create(c);
            trie->node_count++;
        }
        curr = curr->children[idx];
    }

    if (!curr->is_end_of_word) {
        curr->is_end_of_word = true;
        trie->word_count++;
        return true;
    }
    return false;
}

static inline bool akp_trie_search(const akp_trie_t* trie, const char* word) {
    if (!trie || !word || !trie->root) return false;
    akp_trie_node_t* curr = trie->root;
    int len = (int)strlen(word);

    for (int i = 0; i < len; i++) {
        char c = (char)tolower((unsigned char)word[i]);
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';
        if (!curr->children[idx]) return false;
        curr = curr->children[idx];
    }
    return curr != NULL && curr->is_end_of_word;
}

static inline bool akp_trie_starts_with(const akp_trie_t* trie, const char* prefix) {
    if (!trie || !prefix || !trie->root) return false;
    akp_trie_node_t* curr = trie->root;
    int len = (int)strlen(prefix);

    for (int i = 0; i < len; i++) {
        char c = (char)tolower((unsigned char)prefix[i]);
        if (c < 'a' || c > 'z') continue;
        int idx = c - 'a';
        if (!curr->children[idx]) return false;
        curr = curr->children[idx];
    }
    return true;
}

static inline void akp_trie_print_recursive(const akp_trie_node_t* node, char* prefix, int depth) {
    if (!node) return;

    for (int i = 0; i < AKP_TRIE_ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            akp_trie_node_t* child = node->children[i];
            
            // Indentation
            for (int d = 0; d < depth; d++) {
                akp_set_fg_rgb(100, 100, 120);
                printf("│  ");
                akp_reset_color();
            }

            akp_set_fg_rgb(0, 255, 200);
            printf("└── [%c]", child->ch);
            akp_reset_color();

            if (child->is_end_of_word) {
                akp_set_fg_rgb(255, 215, 0);
                printf(" ★ (WORD)");
                akp_reset_color();
            }
            printf("\n");

            prefix[depth] = child->ch;
            prefix[depth + 1] = '\0';
            akp_trie_print_recursive(child, prefix, depth + 1);
        }
    }
}

static inline void akp_trie_render(const akp_trie_t* trie, const char* title) {
    akp_init_console();
    printf("\n");
    akp_set_fg_rgb(0, 255, 230);
    printf("╔═══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║  🌳 PREFIX TREE (TRIE) STRUCTURE & VOCABULARY HIERARCHY                       ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════╝\n");
    akp_reset_color();

    if (title) {
        akp_set_fg_rgb(255, 215, 0);
        printf("  ⚡ Vocabulary Group: %s\n", title);
        akp_reset_color();
    }

    if (!trie || !trie->root) {
        akp_set_fg_rgb(255, 70, 85);
        printf("  [ Trie is NULL ]\n\n");
        akp_reset_color();
        return;
    }

    akp_set_fg_rgb(0, 255, 170);
    printf("  Total Words: %d  |  Total Nodes: %d  |  Root: '/'\n\n", trie->word_count, trie->node_count);
    akp_reset_color();

    char buf[128];
    buf[0] = '\0';
    akp_set_fg_rgb(255, 0, 128);
    printf("  [ROOT] (/)\n");
    akp_reset_color();
    akp_trie_print_recursive(trie->root, buf, 0);
    printf("\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_TRIE_H */
