#include "assert.h"
#include "setup.h"
#include "utils.h"

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

void run_map_tests() {
    start_suite();

    test_hashmap_init_correctly_no_cleanup();
    test_hashmap_init_correctly_with_cleanup();
    test_hashmap_init_correctly_non_default_buckets();

    end_suite();
}
