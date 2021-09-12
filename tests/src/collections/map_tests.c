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

void test_hashmap_elem_inserted_correctly_on_empty_no_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    int n = 5;
    char* msg = "hello";

    assert(hashmap_insert(&map, &n, msg));
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

    assert(hashmap_insert(&map, &str, n));
    assert_eq(*(int*)hashmap_get(&map, &str), *n);
    assert(hashmap_contains(&map, &str));
    assert_false(hashmap_is_empty(&map));
    assert_eq(hashmap_load_factor(&map), 1.0 / DEFAULT_BUCKETS);

    hashmap_free(&map, (free_fn_t)&str_free, &free);

    end_test();
}

// test insert until rehash

void test_hashmap_elem_inserted_twice_doesnt_overwrite() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    int x = 5;
    int y = 8;
    assert(hashmap_insert(&map, &x, &y));

    int z = 6;
    assert_false(hashmap_insert(&map, &x, &z));
    assert_eq(*(int*)hashmap_get(&map, &x), y);
    assert(hashmap_contains(&map, &x));
    assert_false(hashmap_is_empty(&map));
    assert_eq(hashmap_load_factor(&map), 1.0 / DEFAULT_BUCKETS);

    hashmap_free(&map, NULL, NULL);

    end_test();
}

void test_hashmap_value_set_correctly_no_overwrite() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, &int_simple_hash, &int_eq);

    int x = 5;
    int y = 7;
    assert_false(hashmap_set(&map, &x, &y, NULL));
    assert_eq(*(int*)hashmap_get(&map, &x), y);
    assert(hashmap_contains(&map, &x));
    assert_false(hashmap_is_empty(&map));
    assert_eq(hashmap_load_factor(&map), 1.0 / DEFAULT_BUCKETS);

    end_test();
}

// test set overwrite
    // no cleanup
    // w/ cleanup
// test remove on empty maintains empty
    // no cleanup
    // w/ cleanup
// test remove w/ one elem makes empty
    // no cleanup
    // w/ cleanup
// test remove w/ many elems not empty but smaller
    // no cleanup
    // w/ cleanup

void run_map_tests() {
    start_suite();

    test_hashmap_init_correctly_no_cleanup();
    test_hashmap_init_correctly_with_cleanup();
    test_hashmap_init_correctly_non_default_buckets();

    test_hashmap_elem_inserted_correctly_on_empty_no_cleanup();
    test_hashmap_elem_inserted_correctly_on_empty_with_cleanup();
    test_hashmap_elem_inserted_twice_doesnt_overwrite();

    test_hashmap_value_set_correctly_no_overwrite();

    end_suite();
}
