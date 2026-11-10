// Matt's Maps!
// HashTable implemented using Open Addressing
// https://en.wikipedia.org/wiki/Hash_table#Open_addressing

// ===============================================
// Header
// ===============================================

#ifndef MATTSMAPS_HASHTABLE_H
#define MATTSMAPS_HASHTABLE_H

// #include "api.h"
#include "lib.h"

typedef struct {
    mkey_t key;
    mval_t val;
} Bucket;

typedef struct {
    Bucket *start;
    int len;
    int size;
    float resize_perc;
} HashTable;

// typedef Store HashTable;
typedef HashTable Store;

Store *map_init();
void map_free(Store *s);
void map_set(Store *s, mkey_t k, mval_t v);
int map_has(Store *s, mkey_t k); // TODO: implement
mval_t map_get(Store *s, mkey_t k);
void map_remove(Store *s, mkey_t k);

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

// #define INCLUDE_MATTSMAPS_HASHTABLE // NOTE: dev
#ifdef INCLUDE_MATTSMAPS_HASHTABLE

#include <stdlib.h>

// =================
// Helpers
// =================

HashTable *_ht_init(int len, float resize_perc) {
    HashTable *ht = (HashTable *)calloc(1, sizeof(HashTable));
    if (ht == NULL) {
        return NULL;
    }
    Bucket *b = (Bucket *)calloc(len, sizeof(Bucket));
    if (b == NULL) {
        return NULL;
    }
    ht->start = b;
    ht->len = len;
    ht->resize_perc = resize_perc;
    return ht;
}

Bucket *_ht_get_bucket(HashTable *ht, mkey_t k) {
    Bucket *b;
    size_t idx = ht->len % _hsh(k);
    b = &ht->start[idx];
    while (b->key != k) {
        if (b->key == 0) {
            return b;
        }
        b = &ht->start[idx++];
        if (idx >= ht->len) {
            idx = 0;
        }
    }
    return b;
}

Bucket *_ht_get_empty_bucket(HashTable *ht, mkey_t k) {
    Bucket *b;
    size_t idx = ht->len % _hsh(k);
    b = &ht->start[idx];
    while (b->key != 0) {
        b = &ht->start[idx++];
        if (idx >= ht->len) {
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

void map_set(Store *s, mkey_t k, mval_t v) {
    Bucket *b = _ht_get_empty_bucket(s, k);
    b->key = k;
    b->val = v;
    // check fill
    float fill_perc = (float)s->size / (float)s->len;
    if (fill_perc >= s->resize_perc) {
        _ht_resize(s, 2.0);
    }
}

mval_t map_get(Store *s, mkey_t k) {
    Bucket *b = _ht_get_bucket(s, k);
    return b->val;
}

void map_remove(Store *s, mkey_t k) {
    Bucket *b = _ht_get_bucket(s, k);
    b->key = 0;
    b->val = 0;
}

int map_has(Store *s, mkey_t k) {
    // TODO: implement
    return 0;
}

MapIterator map_iter() {
    MapIterator i = {0, 0, NULL, 0};
    return i;
}

int map_iter_next(MapIterator *i) {
    // TODO: implement
    return 0;
}

#endif // INCLUDE_MATTSMAPS_HASHTABLE
