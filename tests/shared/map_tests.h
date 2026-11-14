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
UTEST(map, put_single) {
    MapStore *s = INIT_MAP();

    map_put(s, 4, 10);

    EXPECT_TRUE(map_has(s, 4));
    EXPECT_EQ(map_get(s, 4), 10);
    EXPECT_EQ(map_size(s), 1);

    map_free(s);
}

// TEST: multiple put
UTEST(map, put_many) {
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
        EXPECT_TRUE(map_has(s, k));
        ASSERT_EQ(map_get(s, k), i + 1);
    }

    map_free(s);
}

UTEST(map, get_many_null) {
    MapStore *s = INIT_MAP();
    for (int i = 0; i < 10000; i++) {
        ASSERT_EQ(map_get(s, i), 0);
        ASSERT_FALSE(map_has(s, i));
    }
    map_free(s);
}

UTEST(map, remove_one) {
    MapStore *s = INIT_MAP();

    mkey_t KEY = 4;
    mval_t VAL = 10;

    map_put(s, KEY, VAL);
    EXPECT_TRUE(map_has(s, KEY));
    EXPECT_EQ(map_size(s), 1);

    map_remove(s, 5);
    EXPECT_EQ(map_size(s), 1);
    EXPECT_TRUE(map_has(s, KEY));

    map_remove(s, KEY);
    EXPECT_EQ(map_size(s), 0);
    EXPECT_FALSE(map_has(s, KEY));
    EXPECT_EQ(map_get(s, KEY), 0);

    map_free(s);
}
