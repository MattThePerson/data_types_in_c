#ifndef MATTSCONTS_MAP_HTSC_H
#define MATTSCONTS_MAP_HTSC_H

#include "api.h"

MapStore *init_map_hashtablesc();

#endif // MATTSCONTS_MAP_HTSC_H

// #define INCLUDE_MATTSCONTS_MAP // NOTE: DEV
#ifdef INCLUDE_MATTSCONTS_MAP

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bucket_ {
    int key;
    struct bucket_ *next;
} Bucket;

typedef struct {
    MapStore base;
    Bucket *array;
    size_t size;
    size_t _len;
    // ...
} HashTableSCStore;

// ===============================================
// Helpers
// ===============================================

// ===============================================
// Methods
// ===============================================

void map_put_hashtablesc(void *s_, mkey_t k, mval_t v) {
    HashTableSCStore *s = s_;
    printf("in map_put_hashtablesc\n");
    return;
}

mval_t map_get_hashtablesc(void *s_, mkey_t k) {
    HashTableSCStore *s = s_;
    printf("in map_get_hashtablesc\n");
    return 0;
}

// ===============================================
// Init
// ===============================================

MapStore *init_map_hashtablesc() {
    static const struct map_interface_ vtable = {
        .put = &map_put_hashtablesc,
        .get = &map_get_hashtablesc,
    };
    static const MapStore base = {
        .vtable = &vtable,
    };
    HashTableSCStore *store = malloc(sizeof(HashTableSCStore));
    if (!store) {
        return NULL;
    }
    store->array = NULL; // TODO: implement
    store->_len = 16;
    memcpy(&store->base, &base, sizeof(base));
    return &store->base;
}

#endif // INCLUDE_MATTSCONTS_MAP
