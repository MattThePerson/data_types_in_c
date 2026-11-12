#include "helper.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define INCLUDE_MATTSCONTS_MAP
#include "../../src/mattsconts/map.h"

int main() {

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

    printf("calling helper\n");
    test_maps();

    return 0;
}
