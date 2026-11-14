#ifndef MATTSCONTS_MAP_BST_H
#define MATTSCONTS_MAP_BST_H

#include "api.h"

MapStore *init_map_bst();

#endif // MATTSCONTS_MAP_BST_H

#define INCLUDE_MATTSCONTS_MAP // NOTE: DEV
#ifdef INCLUDE_MATTSCONTS_MAP

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bst_node_ {
    int key;
    struct bst_node_ *next;
} BSTNode;

typedef struct {
    MapStore base;
    size_t size;
    BSTNode *root;
} BSTMapStore;

// ===============================================
// Helpers
// ===============================================

// ===============================================
// Methods
// ===============================================

int map_put_bst(void *s_, mkey_t k, mval_t v) {
    BSTMapStore *s = s_;
    printf("in map_put_bst\n");
    return 0;
}

mval_t map_get_bst(void *s_, mkey_t k) {
    BSTMapStore *s = s_;
    printf("in map_get_bst\n");
    return 0;
}

// ===============================================
// Init
// ===============================================

MapStore *init_map_bst() {
    static const struct map_interface_ vtable = {
        .put = &map_put_bst,
        .get = &map_get_bst,
    };
    BSTMapStore *store = calloc(1, sizeof(BSTMapStore));
    store->base.vtable = &vtable;
    return &store->base;
}

#endif // INCLUDE_MATTSCONTS_MAP
