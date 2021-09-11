#include "setup.h"
#include "assert.h"

#include "lfc/utils/hash.h"

// TODO: more tests

void barestr_simple_hash_sanity_check() {
    start_test();

    char* str = "hello";

    // hash = 104
    // hash = 104 + 31 * 101 = 3235
    // hash = 3235 + 31 * 108 = 6583
    // hash = 6583 + 31 * 108 = 9931
    // hash = 9931 + 31 * 111 = 13372
    size_t hash = barestr_simple_hash(str);
    assert_eq(hash, 13372);

    end_test();
}

void run_hash_tests() {
    start_suite();

    barestr_simple_hash_sanity_check();

    end_suite();
}
