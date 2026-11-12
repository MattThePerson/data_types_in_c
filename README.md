# Matt's C Data Types

## Notes

## Tests for Maps

- Check how many items they can hold

## Demos

### Array

How basic usage:

```c
// main.c
#define MC_ARR_T double
#define INCLUDE_MATTSCONTS_ARR
#include "mattsconts/array.h"

void main() {
    // init_arr() ->        dynamic array
    // init_arr_bst() ->    BST
    // init_arr_sll() ->    singly linked list
    // init_arr_dll() ->    doubly linked list
    ArrayStore *s = init_arr_ll();

    arr_append(s, 4.0);
    arr_prepend(s, 6.0);
    arr_t x1 = arr_get(s, 2); // get by index (-n to get from end)
    arr_put(s, 0, 3.0);
    arr_remove(s, 4); // remove by idx
    arr_t x2 = arr_pop(s);

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
    mkey_t keys[s->size]; // NOTE: best way to do this?
    map_keys(s, &keys);
    mval_t vals[s->size];
    map_vlas(s, &vals);

    // iterator
    MapIter it = map_iter();
    while (map_iter_next(&it)) {
        it.key;
        it.val;
    }

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
