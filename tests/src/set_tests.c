#include "hashset_tests.h"

#include "assert.h"
#include "setup.h"
#include "utils.h"

#include "lfc/collections/set.h"

#include "lfc/utils/hash.h"
#include "lfc/utils/mem.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FIXME: some of these tests cause memory leaks i'm almost 100% sure (we'll call that a known issue)

void test_hashset_init_and_freed_correctly_no_cleanup() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &int_simple_hash, &int_eq);

    assert_eq(set.hash_fn, &int_simple_hash);
    assert_eq(set.elem_eq, &int_eq);
    assert_eq(set.buckets.len, DEFAULT_BUCKETS);
    assert_eq(set.size, 0);
    assert_eq(hashset_load_factor(&set), 0);
    assert(hashset_is_empty(&set));

    int* n = calloc_unwrap(sizeof(int), 1, "[hashset_tests] unable to alloc int value");
    assert_false(hashset_contains(&set, n));

    hashset_free(&set, NULL);

    end_test();
}

void test_hashset_init_and_freed_correctly_with_cleanup() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &str_simple_hash, &str_eq);

    assert_eq(set.hash_fn, &str_simple_hash);
    assert_eq(set.elem_eq, &str_eq);
    assert_eq(set.buckets.len, DEFAULT_BUCKETS);
    assert_eq(set.size, 0);
    assert_eq(hashset_load_factor(&set), 0);
    assert(hashset_is_empty(&set));
    assert_false(hashset_contains(&set, "hello world"));

    hashset_free(&set, &str_free);

    end_test();
}

void test_hashset_insert_into_empty_set() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &int_simple_hash, &int_eq);

    int* value = calloc_unwrap(sizeof(int), 1, "[hashset_tests] failed to alloc int value");
    hashset_insert(&set, value);

    assert_eq(set.size, 1);
    assert_eq(hashset_load_factor(&set), 1.0 / DEFAULT_BUCKETS);
    assert(hashset_contains(&set, value));
    assert_false(hashset_is_empty(&set));

    hashset_free(&set, NULL);

    end_test();
}

void test_hashset_insert_into_nonempty_set() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &int_simple_hash, &int_eq);

    int n = DEFAULT_BUCKETS * MAX_LOAD_FACTOR;

    for (int i = 0; i <= n; i++) {
        int* value = malloc_unwrap(sizeof(int), 1, "[hashset_tests] failed to alloc int value");
        *value = i;
        hashset_insert(&set, value);

        assert_eq(set.size, i + 1);
        assert(hashset_contains(&set, value));
        assert_false(hashset_is_empty(&set));

        // Make sure the rehash was successful
        size_t n_buckets = i == n ? DEFAULT_BUCKETS * 2 : DEFAULT_BUCKETS;
        assert_eq(hashset_load_factor(&set), (double)(i + 1) / n_buckets);
    }

    hashset_free(&set, NULL);

    end_test();
}

void test_hashset_remove_from_one_elem_set_no_cleanup() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &int_simple_hash, &int_eq);

    int* elem = malloc_unwrap(sizeof(int), 1, "[hashset_tests] failed to alloc int value");
    *elem = 3;

    hashset_insert(&set, elem);
    hashset_remove(&set, elem, NULL);

    assert_eq(set.size, 0);
    assert(hashset_is_empty(&set));
    assert_eq(hashset_load_factor(&set), 0);

    hashset_free(&set, NULL);
    free(elem);

    end_test();
}

void test_hashset_remove_from_one_elem_set_with_cleanup() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &str_simple_hash, &str_eq);

    char* str = "hello world";
    char* elem = malloc_unwrap(sizeof(char), strlen(str) + 1, "[hashset_tests] failed to alloc str value");
    strcpy(elem, str);

    hashset_insert(&set, elem);
    hashset_remove(&set, elem, &str_free);

    assert_eq(set.size, 0);
    assert(hashset_is_empty(&set));
    assert_eq(hashset_load_factor(&set), 0);

    hashset_free(&set, &str_free);

    end_test();
}

void test_hashset_remove_from_many_elem_set_no_cleanup() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &int_simple_hash, &int_eq);

    int n = 5;
    int* value;

    for (int i = 0; i <= n; i++) {
        value = malloc_unwrap(sizeof(int), 1, "[hashset_tests] failed to alloc int value");
        *value = i;
        hashset_insert(&set, value);
    }

    hashset_remove(&set, value, NULL);
    assert_false(hashset_contains(&set, value));

    hashset_free(&set, NULL);
    free(value);

    end_test();
}

void test_hashset_remove_from_many_elem_set_with_cleanup() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &str_simple_hash, &str_eq);

    char* strs[4] = {"hello", "world", "asg", "acya"};
    int n_strs = 4;

    for (int i = 0; i < n_strs; i++) {
        char* str = strs[i];
        char* elem = malloc_unwrap(sizeof(char), strlen(str) + 1, "[hashset_tests] failed to alloc str value");
        strcpy(elem, str);
        hashset_insert(&set, elem);
    }

    char* to_remove = strs[0];
    hashset_remove(&set, to_remove, &str_free);
    assert_false(hashset_contains(&set, to_remove));

    hashset_free(&set, &str_free);

    end_test();
}

void test_hashset_nonempty_set_doesnt_contain_missing_value() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &int_simple_hash, &int_eq);

    int* value = calloc_unwrap(sizeof(int), 1, "[hashset_tests] failed to alloc int value");
    hashset_insert(&set, value);

    int* missing = malloc_unwrap(sizeof(int), 1, "[hashset_tests] failed to alloc int value");
    *missing = 1;
    assert_false(hashset_contains(&set, missing));

    hashset_free(&set, NULL);
    free(value);
    free(missing);

    end_test();
}


void run_set_tests() {
    start_suite();

    test_hashset_init_and_freed_correctly_no_cleanup();
    test_hashset_init_and_freed_correctly_with_cleanup();

    test_hashset_insert_into_empty_set();
    test_hashset_insert_into_nonempty_set();

    test_hashset_remove_from_one_elem_set_no_cleanup();
    test_hashset_remove_from_one_elem_set_with_cleanup();
    test_hashset_remove_from_many_elem_set_no_cleanup();
    test_hashset_remove_from_many_elem_set_with_cleanup();

    test_hashset_nonempty_set_doesnt_contain_missing_value();

    end_suite();
}
