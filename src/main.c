#include <stdio.h>

// #define VAL_T unsigned long
#define INCLUDE_MATTSMAPS_HASHTABLE
#include "mattsmaps/hashtable.h"

int main() {
    printf("Hello there\n");

    Store *s = map_init();

    map_set(s, 3, 123456);
    mval_t v = map_get(s, 3);
    printf("v=%d\n", v);

    map_free(s);

    return 0;
}
