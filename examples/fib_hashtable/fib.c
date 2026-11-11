#include "types.h"

// #define MAP_KEY_T u32
#define MAP_VAL_T u64
#define INCLUDE_MATTSMAPS_HASHTABLE_OA
#include "../../src/mattsmaps/hashtable_oa.h"

u64 calc(u32 n, Store *s) {
    if (n <= 2) {
        return 1;
    }
    u64 num;
    if ((num = map_get(s, n)) != 0) {
        return num;
    }
    u64 a = calc(n - 1, s);
    u64 b = calc(n - 2, s);
    num = a + b;
    map_set(s, n, num);
    return num;
}

u64 fib(u32 n) {
    if (n < 1) {
        return 0;
    }
    Store *s = map_init();
    u64 num = calc(n, s);
    map_free(s);
    return num;
}
