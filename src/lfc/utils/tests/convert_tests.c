#include "lfc/utils/convert.h"

#include <stdint.h>
#include <string.h>

#include "tests/assert.h"
#include "tests/setup.h"

#define RUN_ITOA_TEST(n) start_test(); itoa_test_body(n, #n); end_test();

#include <stdio.h>

void itoa_test_body(int32_t n, char* exp_lit) {
    str_t exp_str;
    str_from(&exp_str, exp_lit);

    char* result_buf = itoa(n);
    assert(strcmp(exp_lit, result_buf) == 0);

    str_t result_str = itos(n);
    assert(str_eq(&exp_str, &result_str));
}

void test_itoa_zero_converted_correctly() {
    RUN_ITOA_TEST(0);
}

void test_itoa_small_positive_converted_correctly() {
    RUN_ITOA_TEST(150);
}

void test_itoa_large_positive_converted_correctly() {
    RUN_ITOA_TEST(12500000);
}

void test_itoa_small_negative_converted_correctly() {
    RUN_ITOA_TEST(-225);
}

void test_itoa_large_negative_converted_correctly() {
    RUN_ITOA_TEST(-7500000);
}

void test_itoa_max_value_converted_correctly() {
    // hardcode INT32_MAX to get the test to run w/ the macro
    RUN_ITOA_TEST(2147483647);
}

void test_itoa_min_value_converted_correctly() {
    // hardcode INT32_MIN to get the test to run w/ the macro
    RUN_ITOA_TEST(-2147483648);
}

void run_convert_tests() {
    start_suite();

    test_itoa_zero_converted_correctly();
    test_itoa_small_positive_converted_correctly();
    test_itoa_large_positive_converted_correctly();
    test_itoa_small_negative_converted_correctly();
    test_itoa_large_negative_converted_correctly();
    test_itoa_max_value_converted_correctly();
    test_itoa_min_value_converted_correctly();

    end_suite();
}
