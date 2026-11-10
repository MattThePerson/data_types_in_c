// Matt's Maps!
// HashTable implemented using Open Addressing
// https://en.wikipedia.org/wiki/Hash_table#Open_addressing

// ===============================================
// Header
// ===============================================

#ifndef MATTSMAPS_HASHTABLE_H
#define MATTSMAPS_HASHTABLE_H

#include "internal/api.h"
#include "internal/lib.h"
#include <stddef.h>
#include <stdio.h>

typedef struct {
    mkey_t key;
    mval_t val;
} Bucket;

struct Store {
    Bucket *start;
    size_t size;
    size_t _len;
    float _upsize_perc;
    int _is_impure; // when removing from OA HT, need to then check all buckets
                    // with map_get
};

typedef Store HashTable;

// TODO: implement
typedef struct MapIterator {
    mkey_t key;
    mval_t val;
    struct MapIterator *next;
    int _curr_idx;
} MapIterator;

MapIterator map_iter();
int map_iter_next(MapIterator *i);

#endif // MATTSMAPS_HASHTABLE_H

// ===============================================
// Library
// ===============================================

#define INCLUDE_MATTSMAPS_HASHTABLE // NOTE: dev
#ifdef INCLUDE_MATTSMAPS_HASHTABLE

#include <stdlib.h>

// =================
// Helpers
// =================

HashTable *_ht_init(int len, float upsize_perc) {
    HashTable *ht = (HashTable *)calloc(1, sizeof(HashTable));
    if (ht == NULL) {
        return NULL;
    }
    Bucket *b = (Bucket *)calloc(len, sizeof(Bucket));
    if (b == NULL) {
        return NULL;
    }
    ht->start = b;
    ht->_len = len;
    ht->_upsize_perc = upsize_perc;
    return ht;
}

// _ht_get_bucket_with_key will attempt to get a bucket with a key using hash
// indexing
// NOTE: currently, need to check all Buckets bucause HT might become impure
// with item removal. Can be optimized, but need to add condition for pure vs.
// impure table.
Bucket *_ht_get_bucket_with_key(HashTable *ht, mkey_t k) {
    Bucket *b;
    size_t idx = (size_t)_hsh(k) % ht->_len;
    size_t count = 0;
    b = &ht->start[idx];
    while (b->key != k) {
        b = &ht->start[idx];
        if (++idx >= ht->_len) {
            idx = 0;
        }
        if (++count >= ht->_len) {
            return NULL;
        }
    }
    return b;
}

// _ht_get_empty_bucket will get the first empty bucket at or after hash
// indexing
Bucket *_ht_get_empty_bucket(HashTable *ht, mkey_t k) {
    Bucket *b;
    size_t idx = (size_t)_hsh(k) % ht->_len;
    b = &ht->start[idx];
    while (b->key != 0) {
        b = &ht->start[idx++];
        if (idx >= ht->_len) {
            idx = 0;
        }
    }
    return b;
}

// _ht_realloc reallocates memory for the HashTable when it gets fuller than 70%
void _ht_resize(HashTable *ht, float mult) {
    // TODO: implement
}

// =================
// API
// =================

Store *map_init() {
    int len = 16;
    float perc = 0.7;
    return _ht_init(len, perc);
}

void map_free(Store *s) {
    free(s->start);
    s->start = NULL;
    free(s);
}

// map_set will add a key-value pair to the Store. If a key already exists, it's
// value will be updated.
void map_set(Store *s, mkey_t k, mval_t v) {
    Bucket *b;
    // find existing bucket
    b = _ht_get_bucket_with_key(s, k);
    if (b != NULL) {
        b->val = v;
        return;
    }
    // add new bucket
    b = _ht_get_empty_bucket(s, k);
    b->key = k;
    b->val = v;
    (s->size)++;
    // check fill
    float fill_perc = (float)s->size / (float)s->_len;
    if (fill_perc >= s->_upsize_perc) {
        _ht_resize(s, 2.0);
    }
}

mval_t map_get(Store *s, mkey_t k) {
    Bucket *b = _ht_get_bucket_with_key(s, k);
    if (b == NULL) {
        return 0;
    }
    return b->val;
}

void map_remove(Store *s, mkey_t k) {
    Bucket *b = _ht_get_bucket_with_key(s, k);
    b->key = 0;
    b->val = 0;
}

// int map_has(Store *s, mkey_t k) {
//     // TODO: implement
//     return 0;
// }

MapIterator map_iter() {
    MapIterator i = {0, 0, NULL, 0};
    return i;
}

// int map_iter_next(MapIterator *i) {
//     // TODO: implement
//     return 0;
// }

#endif // INCLUDE_MATTSMAPS_HASHTABLE
