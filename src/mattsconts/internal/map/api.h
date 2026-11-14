#ifndef MATTSCONTS_MAP_API_H
#define MATTSCONTS_MAP_API_H

#include <stdbool.h>
#include <stddef.h>

#ifndef MC_MKEY_T
#define MC_MKEY_T int
#endif // MC_MKEY_T
typedef MC_MKEY_T mkey_t;

#ifndef MC_MVAL_T
#define MC_MVAL_T int
#endif // MC_MVAL_T
typedef MC_MVAL_T mval_t;

// MapStore is an interface to allow other structs to have their 'methods' be
// dispatched while using a single Store type.
// - vtable -> struct containing function handles
// - store -> void* to specific Store type
typedef struct {
    const struct map_interface_ *vtable;
} MapStore;

struct map_interface_ {
    void (*free)(void *s);

    size_t (*size)(void *s);
    int (*put)(void *s, mkey_t k, mval_t v);
    mval_t (*get)(void *s, mkey_t k);
    bool (*has)(void *s, mkey_t k);
    void (*remove)(void *s);

    void (*keys)(void *s);   // TODO: implement
    void (*values)(void *s); // TODO: implement
};

unsigned long hsh_(mkey_t);

void map_free(MapStore *s);
size_t map_size(MapStore *s);
int map_put(MapStore *s, mkey_t k, mval_t v);
mval_t map_get(MapStore *s, mkey_t k);

// #define INCLUDE_MATTSCONTS_MAP // NOTE: DEV
#ifdef INCLUDE_MATTSCONTS_MAP

unsigned long hsh_(mkey_t k) {
    // TODO: improve
    return (unsigned long)(k + 3) * 3142;
}

// API

void map_free(MapStore *s) { s->vtable->free(s); }
size_t map_size(MapStore *s) { return s->vtable->size(s); }
int map_put(MapStore *s, mkey_t k, mval_t v) { return s->vtable->put(s, k, v); }
mval_t map_get(MapStore *s, mkey_t k) { return s->vtable->get(s, k); }
// ...

#endif // INCLUDE_MATTSCONTS_MAP
#endif // MATTSCONTS_MAP_API_H
