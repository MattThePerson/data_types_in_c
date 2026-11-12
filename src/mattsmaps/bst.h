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

#endif // MATTSMAPS_BST_H

// ===============================================
// Library
// ===============================================

// #define INCLUDE_MATTSMAPS_BST // NOTE : dev
#ifdef INCLUDE_MATTSMAPS_BST

#include <stdio.h>
#include <stdlib.h>

struct _store {
    BSTNode *root;
    size_t size;
};

// =================
// Helpers
// =================

BSTNode *_node_init() {
    BSTNode *n;
    n = (BSTNode *)calloc(1, sizeof(BSTNode));
    return n;
}

void _bst_free(BSTNode *n) {
    if (n == NULL) {
        return;
    }
    _bst_free(n->left);
    _bst_free(n->right);
    free(n);
}

// _bst_set will set set a key-value pair into a BST given a node, returns 1 if
// new pair added, 0 if pair updated
int _bst_set(BSTNode *node, mkey_t k, mval_t v) {
    if (0 == node->key) {
        node->key = k;
        node->val = v;
        return 1;
    }
    if (k == node->key) {
        node->val = v;
        return 0;
    }
    if (k < node->key) {
        if (node->left == NULL) {
            node->left = _node_init();
        }
        return _bst_set(node->left, k, v);
    }
    if (k > node->key) {
        if (node->right == NULL) {
            node->right = _node_init();
        }
        return _bst_set(node->right, k, v);
    }
    return 0;
}

mval_t _bst_get(BSTNode *node, mkey_t k) {
    if (node == NULL) {
        return 0;
    }
    if (k == node->key) {
        return node->val;
    } else if (k < node->key) {
        return _bst_get(node->left, k);
    } else if (k > node->key) {
        return _bst_get(node->right, k);
    }
    return 0;
}

int _bst_has(BSTNode *node, mkey_t k) { return (_bst_get(node, k) != 0); }

// TODO: implement
// void _bst_remove(BSTNode *n, mkey_t k) {}

// =================
// API
// =================

Store *map_init() {
    Store *s;
    s = (Store *)calloc(1, sizeof(Store));
    s->root = NULL;
    return s;
}

void map_free(Store *s) {
    if (s == NULL) {
        return;
    }
    _bst_free(s->root);
    free(s);
}

void map_set(Store *s, mkey_t k, mval_t v) {
    if (s->root == NULL) {
        s->root = _node_init();
    }
    if (_bst_set(s->root, k, v)) {
        s->size++;
    }
}

mval_t map_get(Store *s, mkey_t k) { return _bst_get(s->root, k); }

int map_has(Store *s, mkey_t k) { return _bst_has(s->root, k); }

// TODO: implement
// void map_remove(Store *s, mkey_t k) {
//     printf("BST map_remove not yet implemented");
//     exit(1);
// }

#endif // INCLUDE_MATTSMAPS_BST
