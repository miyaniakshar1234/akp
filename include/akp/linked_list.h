/**
 * ============================================================================
 *  AKP ENGINE - LINKED LIST VISUALIZER (akp/linked_list.h)
 *  Author: Akshar Miyani | AKP Studio
 *  Purpose: Visual in-terminal Singly and Doubly Linked Lists for Lab Flexing
 * ============================================================================
 */

#ifndef AKP_LINKED_LIST_H
#define AKP_LINKED_LIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "color.h"
#include "badge.h"

/* ============================================================================
 *  1. SINGLY LINKED LIST
 * ============================================================================
 */

typedef struct akp_snode {
    int data;
    struct akp_snode* next;
} akp_snode_t;

typedef struct {
    akp_snode_t* head;
    int size;
    char name[32];
} akp_slist_t;

static inline akp_slist_t* akp_slist_create(const char* name) {
    akp_init_console();
    akp_slist_t* list = (akp_slist_t*)malloc(sizeof(akp_slist_t));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    strncpy(list->name, name ? name : "SinglyList", sizeof(list->name) - 1);
    list->name[sizeof(list->name) - 1] = '\0';
    return list;
}

static inline void akp_slist_insert_head(akp_slist_t* list, int data) {
    if (!list) return;
    akp_snode_t* node = (akp_snode_t*)malloc(sizeof(akp_snode_t));
    node->data = data;
    node->next = list->head;
    list->head = node;
    list->size++;
}

static inline void akp_slist_insert_tail(akp_slist_t* list, int data) {
    if (!list) return;
    akp_snode_t* node = (akp_snode_t*)malloc(sizeof(akp_snode_t));
    node->data = data;
    node->next = NULL;

    if (!list->head) {
        list->head = node;
    } else {
        akp_snode_t* cur = list->head;
        while (cur->next) cur = cur->next;
        cur->next = node;
    }
    list->size++;
}

static inline int akp_slist_delete(akp_slist_t* list, int data) {
    if (!list || !list->head) return 0;
    akp_snode_t* cur = list->head;
    akp_snode_t* prev = NULL;

    while (cur && cur->data != data) {
        prev = cur;
        cur = cur->next;
    }
    if (!cur) return 0;

    if (!prev) {
        list->head = cur->next;
    } else {
        prev->next = cur->next;
    }
    free(cur);
    list->size--;
    return 1;
}

static inline void akp_slist_render(const akp_slist_t* list) {
    if (!list) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_CYAN "🔗 SINGLY LINKED LIST: %s (Length: %d)\n" AKP_RESET, list->name, list->size);
    printf("   ");
    printf(AKP_BOLD AKP_NEON_YELLOW "[HEAD]" AKP_RESET);

    if (!list->head) {
        printf(" -> " AKP_DIM "NULL\n\n" AKP_RESET);
        return;
    }

    akp_snode_t* cur = list->head;
    while (cur) {
        printf(" -> " AKP_BOLD AKP_NEON_CYAN "[ %4d | • ]" AKP_RESET, cur->data);
        cur = cur->next;
    }
    printf(" -> " AKP_DIM "NULL\n\n" AKP_RESET);
}

static inline void akp_slist_free(akp_slist_t* list) {
    if (!list) return;
    akp_snode_t* cur = list->head;
    while (cur) {
        akp_snode_t* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(list);
}

/* ============================================================================
 *  2. DOUBLY LINKED LIST
 * ============================================================================
 */

typedef struct akp_dnode {
    int data;
    struct akp_dnode* prev;
    struct akp_dnode* next;
} akp_dnode_t;

typedef struct {
    akp_dnode_t* head;
    akp_dnode_t* tail;
    int size;
    char name[32];
} akp_dlist_t;

static inline akp_dlist_t* akp_dlist_create(const char* name) {
    akp_init_console();
    akp_dlist_t* list = (akp_dlist_t*)malloc(sizeof(akp_dlist_t));
    if (!list) return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    strncpy(list->name, name ? name : "DoublyList", sizeof(list->name) - 1);
    list->name[sizeof(list->name) - 1] = '\0';
    return list;
}

static inline void akp_dlist_insert_tail(akp_dlist_t* list, int data) {
    if (!list) return;
    akp_dnode_t* node = (akp_dnode_t*)malloc(sizeof(akp_dnode_t));
    node->data = data;
    node->next = NULL;
    node->prev = list->tail;

    if (!list->head) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

static inline void akp_dlist_render(const akp_dlist_t* list) {
    if (!list) return;
    akp_init_console();

    printf("\n" AKP_BOLD AKP_NEON_PINK "↔️  DOUBLY LINKED LIST: %s (Length: %d)\n" AKP_RESET, list->name, list->size);
    printf("   ");
    printf(AKP_BOLD AKP_NEON_YELLOW "[HEAD]" AKP_RESET);

    if (!list->head) {
        printf(" <-> " AKP_DIM "NULL\n\n" AKP_RESET);
        return;
    }

    akp_dnode_t* cur = list->head;
    while (cur) {
        printf(" <-> " AKP_BOLD AKP_NEON_PINK "[ • | %4d | • ]" AKP_RESET, cur->data);
        cur = cur->next;
    }
    printf(" <-> " AKP_BOLD AKP_NEON_YELLOW "[TAIL]\n\n" AKP_RESET);
}

static inline void akp_dlist_free(akp_dlist_t* list) {
    if (!list) return;
    akp_dnode_t* cur = list->head;
    while (cur) {
        akp_dnode_t* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(list);
}

#ifdef __cplusplus
}
#endif

#endif /* AKP_LINKED_LIST_H */
