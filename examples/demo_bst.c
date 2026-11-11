#include <stdio.h>

#define INCLUDE_MATTSMAPS_BST
#include "../src/mattsmaps/bst.h"

int main() {
    printf("Hello from demo_bst.c!\n");

    printf("creating store\n");
    Store *s = map_init();

    map_set(s, 5, 9);
    printf("key=5 val=%d\n", map_get(s, 5));

    printf("freeing store\n");
    map_free(s);
    return 0;
}
