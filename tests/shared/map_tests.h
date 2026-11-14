#define INCLUDE_MATTSCONTS_MAP
#include "../../src/mattsconts/map.h"

#if MAP_TEST_BACKEND == htsc
#define INIT_MAP init_map_hashtablesc
#elif MAP_TEST_BACKEND == bst
#define INIT_MAP = init_map_bst
#else
#error "Unknown TEST_TYPE"
#endif

#include "../../lib/utest.h"

// TEST: single put
UTEST(map, single_put) {
    MapStore *s = INIT_MAP();

    map_put(s, 4, 10);

    EXPECT_EQ(map_get(s, 4), 10);
    EXPECT_EQ(map_get(s, 5), 0);
    EXPECT_EQ(map_size(s), 1);

    map_free(s);
}

// TEST: multiple put
UTEST(map, multi_put) {
    MapStore *s = INIT_MAP();

    size_t N = 16;

    // fill map
    for (size_t i = 0; i < N; i++) {
        mkey_t k = (mkey_t)i + 1;
        map_put(s, k, i + 1);
        EXPECT_EQ(map_size(s), i + 1);
    }

    // query map
    for (size_t i = 0; i < N; i++) {
        mkey_t k = (mkey_t)i + 1;
        ASSERT_EQ(map_get(s, k), i + 1);
    }

    map_free(s);
}

UTEST(map, many_null) {
    MapStore *s = INIT_MAP();
    for (int i = 0; i < 10000; i++) {
        ASSERT_EQ(map_get(s, i), 0);
    }
    map_free(s);
}
