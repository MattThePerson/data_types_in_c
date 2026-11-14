# Matt's C Data Types

## Notes

## Tests for Maps

- Check how many items they can hold

### Running tests

```sh
# To run a single test file and filter tests
ARGS="--filter=<suite>.<test_name_pattern>" make cleanrun/tests/<test_target>

# eg:
ARGS="--filter=map.put*" make cleanrun/tests/map_htsc_tests
```

## Example usage

<!-- TODO: test demos in code -->

### Sequence

How basic usage:

```c
// main.c
#define MC_ARR_T double
#define INCLUDE_MATTSCONTS_ARR
#include "mattsconts/sequence.h"

/*
C++ sequence containers API

c.size(); c.empty(); c.clear();
c.begin(); c.end();              // iterators (also cbegin/rbegin/...)
c.front();                       // first element (all)
c.back();                        // last element (all except forward_list)
c.insert(pos, x); c.erase(pos);  // by iterator
c.emplace(pos, args...);         // construct in place
c.swap(other);

NOTE: add in warning when using non performant method on data type
*/

void main() {
    // init_seq_arr() ->    dynamic array
    // init_seq_bst() ->    BST
    // init_seq_sll() ->    singly linked list
    // init_seq_dll() ->    doubly linked list
    SeqStore *s = init_seq_arr();

    seq_append(s, 4.0);
    seq_prepend(s, 6.0);
    seq_t x1 = arr_get(s, 2); // get by index (-n to get from end)
    seq_put(s, 0, 3.0);
    seq_remove(s, 4); // remove by idx
    seq_t x2 = arr_pop(s);

    // seq_from
    int numbers[] = {1, 2, 3, 4};
    SeqStore *s2 = init_seq_from(&numbers, 4);

    arr_free(s2);
    arr_free(s);
    return 0;
}

/* EOF */
```

### Map

Basic usage:

```c
// main.c
#define MC_MKEY_T unsigned long
#define MC_MVAL_T double
#define INCLUDE_MATTSCONTS_MAP
#include "mattsconts/map.h"

int main() {
    // init_map_bst() ->            BST
    // init_map_hashtableoa() ->    HashTable (open addressing)
    // init_map_hashtablesc() ->    HashTable (separate chaining)
    MapStore *s = init_map_bst();

    // common
    map_put(s, 4, 10.0);
    mkey_t k = map_get(s, 4);
    bool x = map_has(s, 4);
    map_remove(s, 4);

    // get keys or values
    size_t N = map_size(s);
    mkey_t keys[N]; // NOTE: best way?
    map_keys(s, &keys);
    mval_t vals[N];
    map_vlas(s, &vals);

    // iterator
    MapIter it = map_iter();
    while (map_iter_next(&it)) {
        it.key;
        it.val;
    }

    unsigned long keys[] = {1, 2, 3, 4};
    double values[] = {11.0, 9.0, 7.0, 5.0};
    MapStore *s2 = init_map_from(&keys, &values, 4);

    map_free(s2);
    map_free(s);
    return 0;
}

/* EOF */
```

### Set

Basic usage:

```c
// main.c
#define MC_SET_T unsigned long
#define INCLUDE_MATTSCONTS_SET
#include "mattsconts/set.h"

int main() {
    SetStore *s = init_set();

    // ...

    set_free(s);
    return 0;
}

/* EOF */
```
