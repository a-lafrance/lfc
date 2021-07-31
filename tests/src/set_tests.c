#include "set_tests.h"

#include "assert.h"
#include "setup.h"
#include "utils.h"

#include "lfc/collections/set.h"
#include "lfc/utils/hash.h"

// init: init correctly
    // without cleanup
void test_hashset_init_and_freed_correctly_no_cleanup() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &int_simple_hash, &int_eq);

    assert_eq(set.hash_fn, &int_simple_hash);
    assert_eq(set.elem_eq, &int_eq);
    assert_eq(set.buckets.len, DEFAULT_BUCKETS);
    assert_eq(set.size, 0);
    assert_eq(hashset_load_factor(&set), 0);

    hashset_free(&set, NULL);

    end_test();
}
    // with cleanup
void test_hashset_init_and_freed_correctly_with_cleanup() {
    start_test();

    hashset_t set;
    hashset_init(&set, DEFAULT_BUCKETS, &str_simple_hash, &str_eq);

    assert_eq(set.hash_fn, &str_simple_hash);
    assert_eq(set.elem_eq, &str_eq);
    assert_eq(set.buckets.len, DEFAULT_BUCKETS);
    assert_eq(set.size, 0);
    assert_eq(hashset_load_factor(&set), 0);

    hashset_free(&set, &str_free);

    end_test();
}
// insert
    // insert into empty set
    // insert into non-empty set, no rehash
    // insert into non-empty set, w/ rehash
// remove
    // removal from empty set
    // removal from one-elem set
        // without cleanup
        // with cleanup
    // removal from many elem set
        // without cleanup
        // with cleanup
// contains
    // empty set, doesn't contain
    // non-empty set, doesn't contain
    // non-empty set, does contain
// empty
    // empty
    // one elem
    // many elem
// load factor
    // empty (init test)
    // non-empty (sanity check, also check @ rehash)

void run_set_tests() {
    start_suite();

    test_hashset_init_and_freed_correctly_no_cleanup();
    test_hashset_init_and_freed_correctly_with_cleanup();

    end_suite();
}
