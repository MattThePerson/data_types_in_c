#include "types.h"
#include <stdio.h>

#define INCLUDE_MATTSMAPS_HASHTABLE
#include "../../src/mattsmaps/hashtable.h"

int main() {
    printf("Hello from demo_hashtable/main.c\n");

    Store *s = map_init();

    Cell a = {1, 1, "bobby"};

    map_set(s, 4, &a);

    int k;
    Cell *b;

    k = 4;
    b = map_get(s, k);
    printf("key=%d x=%d name=%s\n", k, b->x, b->name);

    k = 2;
    b = map_get(s, k);
    if (b != NULL) {
        printf("key=%d x=%d name=%s\n", k, b->x, b->name);
    } else {
        printf("b is NULL\n");
    }

    map_free(s);
    return 0;
}
