#ifndef MATTSCONTS_MAP_HTSC_H
#define MATTSCONTS_MAP_HTSC_H

#include "api.h"

MapStore *init_map_hashtablesc();

#endif // MATTSCONTS_MAP_HTSC_H

#define INCLUDE_MATTSCONTS_MAP // NOTE: DEV
#ifdef INCLUDE_MATTSCONTS_MAP

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bucket_ {
    mkey_t key;
    mval_t val;
    struct bucket_ *next;
} Bucket;

typedef struct {
    MapStore base;
    Bucket **array;
    size_t size;
    size_t _len;
    // NOTE: add upsize
} HashTableSCMapStore;

// ===============================================
// Helpers
// ===============================================

void _bucket_free(Bucket *b) {
    if (b == NULL) {
        return;
    }
    _bucket_free(b->next);
    free(b);
}

// _bucket_put will return 1 if new bucket created, 0 if bucket updated
int _bucket_put(Bucket *b, mkey_t k, mval_t v) {
    if (b->key == k) {
        b->val = v;
        return 0;
    }
    if (b->next) {
        return _bucket_put(b->next, k, v);
    }
    Bucket *bnew = calloc(1, sizeof(Bucket));
    bnew->key = k;
    bnew->val = v;
    b->next = bnew;
    return 1;
}

mval_t _bucket_get(Bucket *b, mkey_t k) {
    if (b == NULL) {
        return 0;
    }
    if (b->key == k) {
        return b->val;
    }
    return _bucket_get(b->next, k);
}

// ===============================================
// Methods
// ===============================================

void map_free_hashtablesc(void *s_) {
    HashTableSCMapStore *s = s_;
    for (size_t i = 0; i < s->_len; i++) {
        _bucket_free(s->array[i]);
    }
    free(s->array);
    free(s);
}

size_t map_size_hashtablesc(void *s_) {
    HashTableSCMapStore *s = s_;
    return s->size;
}

int map_put_hashtablesc(void *s_, mkey_t k, mval_t v) {
    HashTableSCMapStore *s = s_;
    size_t hsh = (size_t)hsh_(k);
    size_t idx = hsh % s->_len;
    Bucket *b = s->array[idx];
    if (b == NULL) {
        b = (Bucket *)calloc(1, sizeof(Bucket));
        if (b == NULL) {
            return 1;
        }
        s->array[idx] = b;
    }
    if (_bucket_put(b, k, v) == 1) {
        s->size++;
    }
    return 0;
}

mval_t map_get_hashtablesc(void *s_, mkey_t k) {
    HashTableSCMapStore *s = s_;
    size_t hsh = (size_t)hsh_(k);
    size_t idx = hsh % s->_len;
    Bucket *b = s->array[idx];
    return _bucket_get(b, k);
}

// ===============================================
// Init
// ===============================================

MapStore *init_map_hashtablesc() {
    size_t len = 16;
    static const struct map_interface_ vtable = {
        .free = &map_free_hashtablesc,
        .size = &map_size_hashtablesc,
        .put = &map_put_hashtablesc,
        .get = &map_get_hashtablesc,
    };
    HashTableSCMapStore *store = calloc(1, sizeof(HashTableSCMapStore));
    store->base.vtable = &vtable;
    store->array = calloc(len, sizeof(Bucket));
    store->_len = len;
    return &store->base;
}

#endif // INCLUDE_MATTSCONTS_MAP
