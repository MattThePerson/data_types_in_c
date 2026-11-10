#include <stddef.h>
#include <stdio.h>

#define INCLUDE_MATTSMAPS_HASHTABLE
#include "../src/mattsmaps/hashtable.h"

int main() {
    printf("running tests ...\n");
    Store *s = map_init();
    // empty map should be empty
    for (size_t k = 0; k < s->_len; k++) {
        Bucket b = s->start[k];
        if (b.key != 0 || b.val != 0) {
            printf("NOT EMPTY k=%zu key=%d val=%d\n", k, b.key, b.val);
        }
    }
    map_free(s);
    return 0;
}
