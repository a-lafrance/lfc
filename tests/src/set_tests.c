#include "set_tests.h"

#include "assert.h"
#include "setup.h"
#include "utils.h"

#include "lfc/collections/set.h"

#include "lfc/utils/hash.h"
#include "lfc/utils/mem.h"

#include <stdio.h>


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

    hashset_free(&set, NULL);

    end_test();
}

void test_hashset_remove_from_one_elem_set_with_cleanup() {

}
    // removal from many elem set
        // without cleanup
        // with cleanup
// contains
    // empty set, doesn't contain
    // non-empty set, doesn't contain
// empty
    // empty
    // one elem
    // many elem
// load factor
    // empty (init test)
    // non-empty (sanity check, also check @ rehash & insert & remove)

void run_set_tests() {
    start_suite();

    test_hashset_init_and_freed_correctly_no_cleanup();
    test_hashset_init_and_freed_correctly_with_cleanup();

    test_hashset_insert_into_empty_set();
    test_hashset_insert_into_nonempty_set();

    test_hashset_remove_from_one_elem_set_no_cleanup();
    test_hashset_remove_from_one_elem_set_with_cleanup();

    end_suite();
}
