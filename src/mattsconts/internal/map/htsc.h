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

// _bucket_put will return 1 if malloc failed
// NOTE: leaves first bucket unused, unless k==0
int _bucket_put(Bucket *b, mkey_t k, mval_t v, int *added_flag) {
    assert(b != NULL && "Bucket* cannot be NULL in _bucket_put");
    if (b->key == k) {
        b->val = 0;
        return 0;
    }
    Bucket *bn = b->next;
    if (bn == NULL) {
        bn = calloc(1, sizeof(Bucket));
        bn->key = k;
        bn->val = v;
        b->next = bn;
        *added_flag = 1;
        return 0;
    }
    return _bucket_put(bn, k, v, added_flag);
}

// NOTE: consider using ptr to v
mval_t _bucket_get(Bucket *b, mkey_t k) {
    if (b == NULL) {
        return 0;
    }
    if (b->key == k) {
        return b->val;
    }
    return _bucket_get(b->next, k);
}

bool _bucket_has(Bucket *b, mkey_t k) {
    if (b == NULL) {
        return false;
    }
    if (b->key == k) {
        return true;
    }
    return _bucket_has(b->next, k);
}

int _bucket_remove(Bucket *b, mkey_t k) {
    Bucket *bn = b->next;
    if (bn == NULL) {
        return 0;
    }
    if (bn->key == k) {
        b->next = bn->next;
        free(bn);
        return 1;
    }
    return _bucket_remove(bn, k);
}

size_t _get_idx(size_t len, mkey_t k) {
    size_t hsh = (size_t)hsh_(k);
    return hsh % len;
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

// map_put_hashtablesc returns 1 if allocation failed
int map_put_hashtablesc(void *s_, mkey_t k, mval_t v) {
    HashTableSCMapStore *s = s_;
    size_t idx = _get_idx(s->_len, k);
    Bucket *b = s->array[idx];
    if (b == NULL) {
        b = calloc(1, sizeof(Bucket));
        if (b == NULL) {
            return 1;
        }
        s->array[idx] = b;
    }
    int added = 0;
    if (_bucket_put(b, k, v, &added) == 1) {
        return 1;
    }
    s->size += added;
    return 0;
}

mval_t map_get_hashtablesc(void *s_, mkey_t k) {
    HashTableSCMapStore *s = s_;
    size_t idx = _get_idx(s->_len, k);
    Bucket *b = s->array[idx];
    return _bucket_get(b, k);
}

bool map_has_hashtablesc(void *s_, mkey_t k) {
    HashTableSCMapStore *s = s_;
    size_t idx = _get_idx(s->_len, k);
    Bucket *b = s->array[idx];
    return _bucket_has(b, k);
}

void map_remove_hashtablesc(void *s_, mkey_t k) {
    HashTableSCMapStore *s = s_;
    size_t idx = _get_idx(s->_len, k);
    Bucket *b = s->array[idx];
    if (b == NULL) {
        return;
    }
    if (b->key == k) {
        s->array[idx] = b->next;
        free(b);
        s->size--;
        return;
    }
    if (_bucket_remove(b, k) == 1) {
        s->size--;
    }
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
        .has = &map_has_hashtablesc,
        .remove = &map_remove_hashtablesc,
    };
    HashTableSCMapStore *store = calloc(1, sizeof(HashTableSCMapStore));
    store->base.vtable = &vtable;
    store->array = calloc(len, sizeof(Bucket));
    store->_len = len;
    return &store->base;
}

#endif // INCLUDE_MATTSCONTS_MAP
