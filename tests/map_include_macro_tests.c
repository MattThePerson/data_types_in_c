#include "../lib/utest.h"

#include "../src/mattsmaps/bst.h"
UTEST(config, macro_bst_not_set) {
#ifdef INCLUDE_MATTSMAPS_BST
    ASSERT_TRUE_MSG(0, "INCLUDE_MATTSMAPS_BST should not be defined in header");
#else
    ASSERT_TRUE(1);
#endif
}

#include "../src/mattsmaps/hashtable_oa.h"
UTEST(config, macro_htoa_not_set) {
#ifdef INCLUDE_MATTSMAPS_HASHTABLE_OA
    ASSERT_TRUE_MSG(
        0, "INCLUDE_MATTSMAPS_HASHTABLE_OA should not be defined in header");
#else
    ASSERT_TRUE(1);
#endif
}

#include "../src/mattsmaps/hashtable_sc.h"
UTEST(config, macro_htsc_not_set) {
#ifdef INCLUDE_MATTSMAPS_HASHTABLE_SC
    ASSERT_TRUE_MSG(
        0, "INCLUDE_MATTSMAPS_HASHTABLE_SC should not be defined in header");
#else
    ASSERT_TRUE(1);
#endif
}

UTEST_MAIN();
