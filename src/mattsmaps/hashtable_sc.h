// Matt's Maps!
// HashTable implemented using Separate Chaining
// https://en.wikipedia.org/wiki/Hash_table#Separate_chaining

// ===============================================
// Header
// ===============================================

#ifndef MATTSMAPS_HASHTABLESC_H
#define MATTSMAPS_HASHTABLESC_H

#include "lib.h"

typedef struct Node {
    mkey_t key;
    mval_t val;
    struct Node *next;
} Node;

typedef struct {
    Node *start;
    int len;
    int size;
    float resize_perc;
} HashTableSC;

typedef HashTableSC Store;

Store *map_init();
void map_free(Store *s);
void map_set(Store *s, mkey_t k, mval_t v);
mval_t map_get(Store *s, mkey_t k);
void map_remove(Store *s, mkey_t k);

#endif // MATTSMAPS_HASHTABLESC_H

// ===============================================
// Library
// ===============================================

#define INCLUDE_MATTSMAPS_HASHTABLESC // NOTE: dev
#ifdef INCLUDE_MATTSMAPS_HASHTABLESC

// =================
// Helpers
// =================

// =================
// API
// =================

// TODO: implement
Store *map_init();
void map_free(Store *s);
void map_set(Store *s, mkey_t k, mval_t v);
mval_t map_get(Store *s, mkey_t k);
void map_remove(Store *s, mkey_t k);

#endif // INCLUDE_MATTSMAPS_HASHTABLESC
