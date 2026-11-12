#ifndef MATTSMAPS_API_H
#define MATTSMAPS_API_H

#include "lib.h"

typedef struct _store Store;

Store *map_init();
void map_free(Store *s);
void map_set(Store *s, mkey_t k, mval_t v);
int map_has(Store *s, mkey_t k);
mval_t map_get(Store *s, mkey_t k);
void map_remove(Store *s, mkey_t k);

#endif // MATTSMAPS_API_H
