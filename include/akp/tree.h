/**
 * ============================================================================
 *  AKP ENGINE - BINARY TREE VISUALIZER (akp/tree.h)
 *  Author: Akshar Miyani | AKP Studio
 * ============================================================================
 */

#ifndef AKP_TREE_H
#define AKP_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "color.h"

typedef struct akp_tree_node {
    int value;
    const char* label;
    struct akp_tree_node* left;
    struct akp_tree_node* right;
} akp_tree_node_t;

static inline akp_tree_node_t* akp_tree_create_node(int val, const char* label) {
    akp_tree_node_t* n = (akp_tree_node_t*)malloc(sizeof(akp_tree_node_t));
    if (!n) return NULL;
    n->value = val;
    n->label = label;
    n->left = NULL;
    n->right = NULL;
    return n;
}

static inline void akp_tree_print_internal(const akp_tree_node_t* node, const char* prefix, bool is_left, bool is_root) {
    if (!node) return;

    /* Print right child first (top in horizontal view) */
    char right_prefix[256];
    snprintf(right_prefix, sizeof(right_prefix), "%s%s", prefix, is_left ? "│   " : "    ");
    akp_tree_print_internal(node->right, right_prefix, false, false);

    /* Print current node */
    printf("%s", prefix);
    if (!is_root) {
        printf(AKP_NEON_CYAN "%s" AKP_RESET, is_left ? "└── " : "┌── ");
    }
    if (node->label) {
        printf(AKP_BOLD AKP_NEON_YELLOW "[%d: %s]" AKP_RESET "\n", node->value, node->label);
    } else {
        printf(AKP_BOLD AKP_NEON_GREEN "[%d]" AKP_RESET "\n", node->value);
    }

    /* Print left child */
    char left_prefix[256];
    snprintf(left_prefix, sizeof(left_prefix), "%s%s", prefix, is_left ? "    " : "│   ");
    akp_tree_print_internal(node->left, left_prefix, true, false);
}

static inline void akp_tree_print(const akp_tree_node_t* root, const char* title) {
    akp_init_console();
    printf("\n" AKP_BOLD AKP_NEON_PURPLE "🌳 [ Binary Tree Hierarchy: %s ]" AKP_RESET "\n\n", title ? title : "Root");
    if (!root) {
        printf(AKP_DIM "    (Empty Tree)\n" AKP_RESET);
        return;
    }
    akp_tree_print_internal(root, "    ", false, true);
    printf("\n");
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_TREE_H */
