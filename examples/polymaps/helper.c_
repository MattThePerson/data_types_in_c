#include "../../src/mattsconts/map.h"
#include <stdio.h>

int test_maps() {

    printf("IN helper.c\n");

    printf("initializing\n");
    MapStore *bst = init_map_bst();
    MapStore *ht = init_map_hashtablesc();

    // bst
    map_put(bst, 4, 45);
    printf("map_get=%d\n", map_get(bst, 4));

    // ht
    map_put(ht, 4, 45);
    printf("map_get=%d\n", map_get(ht, 4));

    // map_free(s);

    return 0;
}
