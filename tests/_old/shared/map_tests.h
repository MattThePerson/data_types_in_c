#include "../../lib/utest.h"

#if !defined(INCLUDE_MATTSMAPS_HASHTABLE_OA) &&                                \
    !defined(INCLUDE_MATTSMAPS_HASHTABLE_SC) &&                                \
    !defined(INCLUDE_MATTSMAPS_BST)
#define INCLUDE_MATTSMAPS_HASHTABLE_OA
#endif

#define MAP_KEY_T unsigned long
#define MAP_VAL_T float

// HashTable OA
#ifdef INCLUDE_MATTSMAPS_HASHTABLE_OA
#include "../../src/mattsmaps/hashtable_oa.h"
#endif

// HashTable SC
#ifdef INCLUDE_MATTSMAPS_HASHTABLE_SC
#include "../../src/mattsmaps/hashtable_sc.h"
#endif

// BST
#ifdef INCLUDE_MATTSMAPS_BST
#include "../../src/mattsmaps/bst.h"
#endif

// TEST: basic_tests
UTEST(maps, basic_tests) {
    Store *s = map_init();

    ASSERT_EQ(s->size, 0);

    map_set(s, 4, 10.0);
    map_set(s, 6, 30.0);

    ASSERT_EQ(map_get(s, 4), 10.0);
    ASSERT_EQ(map_get(s, 5), 0.0);
    ASSERT_EQ_MSG(s->size, 2, "size should be 2");

    ASSERT_EQ(map_has(s, 4), 1);
    ASSERT_EQ(map_has(s, 7), 0);

    map_free(s);
}

// TEST: stress_tests
UTEST(maps, insert_1000) {
    Store *s = map_init();

    float PI = 3.1415926;
    unsigned int len = 1000;

    for (unsigned int i = 1; i < len + 1; i++) {
        map_set(s, i, PI * (float)i);
    }

    ASSERT_EQ(s->size, len);
    map_free(s);
}

// TEST: stress_tests
// UTEST(maps, insert_10000) {
//     Store *s = map_init();
//
//     float PI = 3.1415926;
//     unsigned int len = 10000;
//
//     for (unsigned int i = 1; i < len + 1; i++) {
//         map_set(s, i, PI * (float)i);
//     }
//
//     ASSERT_EQ(s->size, len);
//     map_free(s);
// }
