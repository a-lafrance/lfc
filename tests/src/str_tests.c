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
    assert(str_is_empty(&str));

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
    assert_false(str_is_empty(&str));
    assert(strncmp(str.data, text, text_len) == 0);

    str_free(&str);

    end_test();
}

void test_str_pushed_chars_correctly() {
    start_test();

    str_t str;
    str_init(&str);

    char* text = "hello asg acya";
    size_t text_len = strlen(text);

    // loop condition forces expansion
    for (size_t i = 0; i <= STR_DEFAULT_CAPACITY; i++) {
        char c = text[i % text_len];
        str_push(&str, c);

        assert_eq(str.len, i + 1);
        assert_eq(str.capacity, i > STR_DEFAULT_CAPACITY ? 2 * STR_DEFAULT_CAPACITY : STR_DEFAULT_CAPACITY);
        assert_false(str_is_empty(&str));
        assert_eq(str_get(&str, i), c);
    }

    str_free(&str);

    end_test();
}

void test_str_pushed_strs_correctly() {
    start_test();

    str_t str;
    str_init(&str);

    str_t text;
    str_from(&text, "hello asg acya");

    // loop condition forces expansion
    for (size_t i = text.len; str.len < STR_DEFAULT_CAPACITY; i += text.len) {
        str_pushstr(&str, &text);

        assert_eq(str.len, i);
        assert_eq(str.capacity, str.capacity > STR_DEFAULT_CAPACITY ? 2 * STR_DEFAULT_CAPACITY : STR_DEFAULT_CAPACITY);
        assert_false(str_is_empty(&str));
        assert(strncmp(str.data + i, text.data, text.len));
    }

    str_free(&str);

    end_test();
}

void test_str_get_set_correctly() {
    start_test();

    char* text = "hello world";
    str_t str;
    str_from(&str, text);

    char* c = str_at(&str, 0);
    assert_eq(*c, text[0]);

    *c = text[1];
    assert_eq(str_get(&str, 0), text[1]);

    str_free(&str);

    end_test();
}

void test_str_char_prefix_detected_when_present() {
    start_test();

    str_t str;
    char* text = "asg acya";
    str_from(&str, text);

    assert(str_starts_with(&str, text[0]));

    str_free(&str);

    end_test();
}

void test_str_char_prefix_not_detected_when_missing() {
    start_test();

    str_t str;
    char* text = "asg acya";
    str_from(&str, text);

    assert_false(str_starts_with(&str, text[1]));

    str_free(&str);

    end_test();
}
void test_str_char_prefix_not_detected_when_str_empty() {
    start_test();

    str_t str;
    str_init(&str);

    assert_false(str_starts_with(&str, 'a'));

    str_free(&str);

    end_test();
}

void test_str_char_suffix_detected_when_present() {
    start_test();

    str_t str;
    char* text = "asg acya";
    str_from(&str, text);

    assert(str_ends_with(&str, text[strlen(text) - 1]));

    str_free(&str);

    end_test();
}

void test_str_char_suffix_not_detected_when_missing() {
    start_test();

    str_t str;
    char* text = "asg acya";
    str_from(&str, text);

    assert_false(str_ends_with(&str, text[1]));

    str_free(&str);

    end_test();
}
void test_str_char_suffix_not_detected_when_str_empty() {
    start_test();

    str_t str;
    str_init(&str);

    assert_false(str_ends_with(&str, 'a'));

    str_free(&str);

    end_test();
}

void run_str_tests() {
    start_suite();

    test_str_init_correctly();
    test_str_init_from_literal_correctly();

    test_str_pushed_chars_correctly();
    test_str_pushed_strs_correctly();
    test_str_get_set_correctly();

    test_str_char_prefix_detected_when_present();
    test_str_char_prefix_not_detected_when_missing();
    test_str_char_prefix_not_detected_when_str_empty();

    test_str_char_suffix_detected_when_present();
    test_str_char_suffix_not_detected_when_missing();
    test_str_char_suffix_not_detected_when_str_empty();

    end_suite();
}
