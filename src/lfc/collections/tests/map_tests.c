#include <stdlib.h>

#include "lfc/collections/map.h"
#include "lfc/collections/set.h"
#include "lfc/collections/str.h"

#include "lfc/utils/hash.h"

#include "tests/assert.h"
#include "tests/setup.h"
#include "tests/utils.h"


void test_hashmap_init_correctly_no_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    assert_eq(hashmap_n_buckets(&map), DEFAULT_BUCKETS);
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

    assert_eq(hashmap_n_buckets(&map), DEFAULT_BUCKETS);
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

    assert_eq(hashmap_n_buckets(&map), DEFAULT_BUCKETS);
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

void test_hashmap_multiple_distinct_values_inserted_correctly() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    char* str = "hello";
    int str_len = strlen(str);
    int len = DEFAULT_BUCKETS + 1;
    int* keys = malloc_unwrap(sizeof(int), len, "[map_tests] failed to alloc int array");

    for (int i = 0; i < len; i++) {
        keys[i] = i;
        assert(hashmap_insert(&map, keys + i, str + i));

        assert(hashmap_contains(&map, keys + i % str_len));
        assert_eq(map.size, i + 1);
        assert_eq(hashmap_load_factor(&map), (i + 1.0) / hashmap_n_buckets(&map));
        assert_false(hashmap_is_empty(&map));
    }

    hashmap_free(&map, NULL, NULL);
    free(keys);

    end_test();
}

void test_hashmap_value_set_correctly_no_overwrite() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    int x = 5;
    int y = 7;
    assert_false(hashmap_set(&map, &x, &y, NULL));
    assert_eq(*(int*)hashmap_get(&map, &x), y);
    assert(hashmap_contains(&map, &x));
    assert_false(hashmap_is_empty(&map));
    assert_eq(hashmap_load_factor(&map), 1.0 / DEFAULT_BUCKETS);

	hashmap_free(&map, NULL, NULL);

    end_test();
}

void test_hashmap_value_set_correctly_with_overwrite_no_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    int n = 5;
    char* str = "asg";
    hashmap_insert(&map, &n, str);

    char* str2 = "acya";
    assert(hashmap_set(&map, &n, str2, NULL));

    assert_eq(hashmap_get(&map, &n), str2);
    assert(hashmap_contains(&map, &n));
    assert_false(hashmap_is_empty(&map));
    assert_eq(hashmap_load_factor(&map), 1.0 / DEFAULT_BUCKETS);

    hashmap_free(&map, NULL, NULL);

    end_test();
}

void test_hashmap_value_set_correctly_with_overwrite_with_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&str_simple_hash, &str_eq);

    str_t str;
    str_from(&str, "asg");

    struct something thing;
    something_init(&thing, 5);

    hashmap_insert(&map, &str, &thing);

    struct something thing2;
    something_init(&thing2, 5);
    assert(hashmap_set(&map, &str, &thing2, &something_free));

    assert_eq(((struct something*)hashmap_get(&map, &str))->n, thing2.n);
    assert(hashmap_contains(&map, &str));
    assert_false(hashmap_is_empty(&map));
    assert_eq(hashmap_load_factor(&map), 1.0 / DEFAULT_BUCKETS);

    hashmap_free(&map, &str_free, &something_free);

    end_test();
}

void test_hashmap_remove_on_empty_maintains_empty() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    int n = 5;
    hashmap_remove(&map, &n, NULL, NULL);

    assert_eq(hashmap_n_buckets(&map), DEFAULT_BUCKETS);
    assert_eq(map.size, 0);
    assert_eq(hashmap_load_factor(&map), 0.0);
    assert(hashmap_is_empty(&map));

    hashmap_free(&map, NULL, NULL);

    end_test();
}

void test_hashmap_remove_with_one_elem_makes_empty_no_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    int n = 5;
    char* str = "hello world";
    hashmap_insert(&map, &n, str);
    hashmap_remove(&map, &n, NULL, NULL);

    assert_false(hashmap_contains(&map, &n));
    assert_eq(map.size, 0);
    assert_eq(hashmap_load_factor(&map), 0.0);
    assert(hashmap_is_empty(&map));

    hashmap_free(&map, NULL, NULL);

    end_test();
}

void test_hashmap_remove_with_one_elem_makes_empty_with_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&str_simple_hash, &str_eq);

    str_t str;
	char* lit = "hello world";
    str_from(&str, lit);

    struct something thing;
    something_init(&thing, 5);

    hashmap_insert(&map, &str, &thing);
    hashmap_remove(&map, &str, (free_fn_t)&str_free, (free_fn_t)&something_free);

	str_t exp;
	str_from(&exp, lit);

    assert_false(hashmap_contains(&map, &exp));
    assert_eq(map.size, 0);
    assert_eq(hashmap_load_factor(&map), 0.0);
    assert(hashmap_is_empty(&map));

    hashmap_free(&map, (free_fn_t)&str_free, (free_fn_t)&something_free);
	str_free(&exp);

    end_test();
}

void test_hashmap_value_removed_from_many_elems_no_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    char* str = "hello";
    int len = strlen(str);
    int* keys = malloc_unwrap(sizeof(int), len, "[map_tests] failed to alloc int array");

    for (int i = 0; i < len; i++) {
        keys[i] = i;
        hashmap_insert(&map, keys + i, str + i);
    }

    hashmap_remove(&map, keys, NULL, NULL);

    assert_false(hashmap_contains(&map, keys));
    assert_eq(map.size, len - 1);
    assert_eq(hashmap_load_factor(&map), (len - 1.0) / DEFAULT_BUCKETS);
    assert_false(hashmap_is_empty(&map));

    hashmap_free(&map, NULL, NULL);
    free(keys);

    end_test();
}

void test_hashmap_value_removed_from_many_elems_with_cleanup() {
    start_test();

    hashmap_t map;
    hashmap_init(&map, DEFAULT_BUCKETS, (hash_fn_t)&int_simple_hash, &int_eq);

    size_t len = 5;
    str_t* strs = malloc_unwrap(sizeof(str_t), len, "[map_tests] failed to alloc str array");

    for (size_t i = 0; i < len; i++) {
        int* n = malloc_unwrap(sizeof(int), 1, "[map_tests] failed to alloc int value");
        *n = (int)i;

        str_from(strs + i, "hello");

        hashmap_insert(&map, n, strs + i);
    }

    int n = 0;
    hashmap_remove(&map, &n, &free, &str_free);

    assert_false(hashmap_contains(&map, &n));
    assert_eq(map.size, len - 1);
    assert_eq(hashmap_load_factor(&map), (len - 1.0) / DEFAULT_BUCKETS);
    assert_false(hashmap_is_empty(&map));

    hashmap_free(&map, &free, &str_free);
    free(strs);

    end_test();
}

void run_map_tests() {
    start_suite();

    test_hashmap_init_correctly_no_cleanup();
    test_hashmap_init_correctly_with_cleanup();
    test_hashmap_init_correctly_non_default_buckets();

    test_hashmap_elem_inserted_correctly_on_empty_no_cleanup();
    test_hashmap_elem_inserted_correctly_on_empty_with_cleanup();
    test_hashmap_elem_inserted_twice_doesnt_overwrite();
    test_hashmap_multiple_distinct_values_inserted_correctly();

    test_hashmap_value_set_correctly_no_overwrite();
    test_hashmap_value_set_correctly_with_overwrite_no_cleanup();
    test_hashmap_value_set_correctly_with_overwrite_with_cleanup();

    test_hashmap_remove_on_empty_maintains_empty();
    test_hashmap_remove_with_one_elem_makes_empty_no_cleanup();
    test_hashmap_remove_with_one_elem_makes_empty_with_cleanup();
    test_hashmap_value_removed_from_many_elems_no_cleanup();
    test_hashmap_value_removed_from_many_elems_with_cleanup();

    end_suite();
}
