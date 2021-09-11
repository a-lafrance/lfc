#include "assert.h"
#include "setup.h"
#include "utils.h"

#include <stdlib.h>

#include "lfc/collections/map.h"
#include "lfc/collections/set.h"
#include "lfc/collections/str.h"

#include "lfc/utils/hash.h"

void test_hashmap_init_correctly_no_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    assert_eq(map.buckets.len, DEFAULT_BUCKETS);
    assert_eq(map.size, 0);
    assert_eq(hashmap_load_factor(&map), 0.0);
    assert(hashmap_is_empty(&map));

    hashmap_free(&map, NULL, NULL);

    end_test();
}

void test_hashmap_init_correctly_with_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&str_simple_hash, &str_eq);

    assert_eq(map.buckets.len, DEFAULT_BUCKETS);
    assert_eq(map.size, 0);
    assert_eq(hashmap_load_factor(&map), 0.0);
    assert(hashmap_is_empty(&map));

    hashmap_free(&map, (free_fn_t)&str_free, (free_fn_t)&something_free);

    end_test();
}

void test_hashmap_init_correctly_non_default_buckets() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    assert_eq(map.buckets.len, DEFAULT_BUCKETS);
    assert_eq(map.size, 0);
    assert_eq(hashmap_load_factor(&map), 0.0);
    assert(hashmap_is_empty(&map));

    hashmap_free(&map, NULL, NULL);

    end_test();
}

// make sure single insert works:
    // insert -> get returns item
    // insert -> contains item
    // insert -> not empty
    // insert -> load factor up
    // with/without cleanup
// make sure insert doesn't overwrite
void test_hashmap_elem_inserted_correctly_on_empty_no_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    int n = 5;
    char* msg = "hello";
    hashmap_insert(&map, &n, msg);

    assert(strcmp(hashmap_get(&map, &n), msg) == 0);
    assert(hashmap_contains(&map, &n));
    assert_false(hashmap_is_empty(&map));
    assert_eq(hashmap_load_factor(&map), 1.0 / DEFAULT_BUCKETS);

    hashmap_free(&map, NULL, NULL);

    end_test();
}

void test_hashmap_elem_inserted_correctly_on_empty_with_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&str_simple_hash, &str_eq);

    str_t str;
    str_from(&str, "hello world");
    int* n = calloc_unwrap(sizeof(int), 1, "[map_tests] failed to alloc int value");
    hashmap_insert(&map, &str, n);

    assert_eq(*(int*)hashmap_get(&map, &str), *n);
    assert(hashmap_contains(&map, &str));
    assert_false(hashmap_is_empty(&map));
    assert_eq(hashmap_load_factor(&map), 1.0 / DEFAULT_BUCKETS);

    hashmap_free(&map, (free_fn_t)&str_free, &free);

    end_test();
}

void run_map_tests() {
    start_suite();

    test_hashmap_init_correctly_no_cleanup();
    test_hashmap_init_correctly_with_cleanup();
    test_hashmap_init_correctly_non_default_buckets();

    test_hashmap_elem_inserted_correctly_on_empty_no_cleanup();
    test_hashmap_elem_inserted_correctly_on_empty_with_cleanup();

    end_suite();
}
