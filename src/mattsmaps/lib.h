#ifndef MATTSMAPS_LIB_H
#define MATTSMAPS_LIB_H

#ifndef MAP_KEY_T
#define MAP_KEY_T int
#endif
typedef MAP_KEY_T mkey_t;

#ifndef MAP_VAL_T
#define MAP_VAL_T int
#endif
typedef MAP_VAL_T mval_t;

static inline int _hsh(mkey_t k) {
    k *= 3;
    return k;
}

#endif // MATTSMAPS_LIB_H
