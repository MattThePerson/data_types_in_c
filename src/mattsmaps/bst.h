// Matt's Maps!
// Implemented using Binary Search Tree
// https://en.wikipedia.org/wiki/Binary_search_tree

// ===============================================
// Header
// ===============================================

#ifndef MATTSMAPS_BST_H
#define MATTSMAPS_BST_H

#include "internal/api.h"
#include "internal/lib.h"
#include <stddef.h>

typedef struct BSTNode {
    mkey_t key;
    mval_t val;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

struct Store {
    BSTNode *root;
    size_t size;
};

// Store *map_init();
// void map_free(Store *s);
// void map_set(Store *s, mkey_t k, mval_t v);
// mval_t map_get(Store *s, mkey_t k);
// void map_remove(Store *s, mkey_t k);

#endif // MATTSMAPS_BST_H

// ===============================================
// Library
// ===============================================

#define INCLUDE_MATTSMAPS_BST // NOTE : dev
#ifdef INCLUDE_MATTSMAPS_BST

#include <stdio.h>
#include <stdlib.h>

// =================
// Helpers
// =================

// =================
// API
// =================

Store *map_init() {
    BSTNode *node;
    node = (BSTNode *)calloc(1, sizeof(BSTNode));
    return node;
}

void map_free(Store *node) {
    if (node == NULL) {
        return;
    }
    map_free(node->left);
    map_free(node->right);
    free(node);
}

// TODO: apply hash based equality
void map_set(Store *s, mkey_t k, mval_t v) {
    if (0 == s->key || k == s->key) {
        s->key = k;
        s->val = v;
    } else if (k < s->key) {
        if (s->left == NULL) {
            s->left = map_init();
        }
        map_set(s->left, k, v);
    } else if (k > s->key) {
        if (s->right == NULL) {
            s->right = map_init();
        }
        map_set(s->right, k, v);
    }
}

// TODO: apply hash based equality
mval_t map_get(Store *s, mkey_t k) {
    if (s == NULL) {
        return 0;
    }
    if (k == s->key) {
        return s->val;
    } else if (k < s->key) {
        return map_get(s->left, k);
    } else if (k > s->key) {
        return map_get(s->right, k);
    }
    return 0;
}

// TODO: implement
// void map_remove(Store *s, mkey_t k) {
//     printf("BST map_remove not yet implemented");
//     exit(1);
// }

#endif // INCLUDE_MATTSMAPS_BST
