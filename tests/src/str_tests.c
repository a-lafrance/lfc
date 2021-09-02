#include <string.h>

#include "lfc/collections/str.h"

#include "assert.h"
#include "setup.h"

void test_str_init_correctly() {
    start_test();

    str_t str;
    str_init(&str);

    assert_eq(str.len, 0);
    assert_eq(str.capacity, STR_DEFAULT_CAPACITY);

    str_free(&str);

    end_test();
}

void test_str_init_from_literal_correctly() {
    start_test();

    char* text = "hello world";
    size_t text_len = strlen(text);

    str_t str;
    str_from(&str, text);

    assert_eq(str.len, text_len);
    assert_eq(str.capacity, STR_DEFAULT_CAPACITY + text_len); // impl detail?
    assert(strncmp(str.data, text, text_len) == 0);

    str_free(&str);

    end_test();
}

void run_str_tests() {
    start_suite();

    test_str_init_correctly();
    test_str_init_from_literal_correctly();

    end_suite();
}
