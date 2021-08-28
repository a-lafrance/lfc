#include "array_tests.h"

#include "assert.h"
#include "setup.h"
#include "utils.h"

#include "lfc/collections/array.h"
#include "lfc/utils/mem.h"

#include <stdlib.h>
#include <stdio.h>


array_t alloc_int_data(size_t len) {
    int* data = calloc_unwrap(sizeof(int), len, "[array_tests] failed to alloc int array during test");

    array_t array;
    array_init(&array, data, len, sizeof(int));

    return array;
}

array_t alloc_struct_data(size_t len) {
    struct something* data = malloc_unwrap(sizeof(struct something), len, "[array_tests] failed to alloc struct array during test");

    for (int i = 0; i < len; i++) {
        something_init_zeroed(data + i);
    }

    array_t array;
    array_init(&array, data, len, sizeof(struct something));

    return array;
}


void test_array_init_and_freed_correctly_no_elem_free() {
    start_test();

    size_t len = 5;
    array_t array = alloc_int_data(len);

    assert_eq(array.len, len);
    assert_eq(array.elem_size, sizeof(int));

    array_free(&array, NULL);

    end_test();
}


void test_array_init_and_freed_correctly_with_elem_free() {
    start_test();

    size_t len = 3;
    array_t array = alloc_struct_data(len);

    assert_eq(array.len, len);
    assert_eq(array.elem_size, sizeof(struct something));

    array_free(&array, (free_fn_t)(&something_free));

    end_test();
}


void test_first_index_accessed_correctly() {
    start_test();

    array_t array = alloc_int_data(3);
    int* first = array_at(&array, 0);
    assert_eq(*first, 0);

    array_free(&array, NULL);

    end_test();
}


void test_mid_index_accessed_correctly() {
    start_test();

    array_t array = alloc_int_data(3);
    int* elem = array_at(&array, array.len / 2);
    assert_eq(*elem, 0);

    array_free(&array, NULL);

    end_test();
}


void test_last_index_accessed_correctly() {
    start_test();

    array_t array = alloc_int_data(3);
    int* last = array_at(&array, array.len - 1);
    assert_eq(*last, 0);

    array_free(&array, NULL);

    end_test();
}

// array_at: out of bounds panic test?


void test_first_index_modified_correctly() {
    start_test();

    /* --- Without cleanup --- */
    array_t int_array = alloc_int_data(3);
    int new_int = 3;
    *(int*)array_at(&int_array, 0) = new_int;

    int* first_int = array_at(&int_array, 0);
    assert_eq(*first_int, new_int);

    array_free(&int_array, NULL);

    /* --- With cleanup --- */
    array_t struct_array = alloc_struct_data(3);

    struct something new_struct;
    something_init(&new_struct, 5);

    struct something* elem = array_at(&struct_array, 0);
    something_free(elem);
    *elem = new_struct;

    struct something* first_struct = array_at(&struct_array, 0);
    assert_eq(*(first_struct->n), *(new_struct.n));

    array_free(&struct_array, (free_fn_t)&something_free);

    end_test();
}


void test_mid_index_modified_correctly() {
    start_test();

    /* --- Without cleanup --- */
    array_t int_array = alloc_int_data(3);

    int new = 3;
    size_t index = int_array.len / 2;
    *(int*)array_at(&int_array, index) = new;

    int* int_elem = array_at(&int_array, index);
    assert_eq(*int_elem, new);

    array_free(&int_array, NULL);

    /* --- With cleanup --- */
    array_t struct_array = alloc_struct_data(5);

    struct something new_struct;
    something_init(&new_struct, 5);

    size_t struct_index = 2;
    struct something* elem = array_at(&struct_array, struct_index);
    something_free(elem);
    *elem = new_struct;

    struct something* struct_elem = array_at(&struct_array, struct_index);
    assert_eq(*(struct_elem->n), *(new_struct.n));

    array_free(&struct_array, (free_fn_t)&something_free);

    end_test();
}


void test_last_index_modified_correctly() {
    start_test();

    /* --- Without cleanup --- */
    array_t int_array = alloc_int_data(3);

    int new = 3;
    size_t index = int_array.len - 1;
    *(int*)array_at(&int_array, index) = new;

    int* int_elem = array_at(&int_array, index);
    assert_eq(*int_elem, new);

    array_free(&int_array, NULL);

    /* --- With cleanup --- */
    array_t struct_array = alloc_struct_data(5);

    struct something new_struct;
    something_init(&new_struct, 5);

    size_t struct_index = struct_array.len - 1;
    struct something* struct_elem = array_at(&struct_array, struct_index);
    something_free(struct_elem);
    *struct_elem = new_struct;

    struct something* last_struct = array_at(&struct_array, struct_index);
    assert_eq(*(last_struct->n), *(new_struct.n));

    array_free(&struct_array, (free_fn_t)&something_free);

    end_test();
}


void test_find_elem_found_when_present() {
    start_test();

    array_t array = alloc_int_data(5);

    for (size_t i = 0; i < array.len; i++) {
        int* val = array_at(&array, i);
        *val = i;
    }

    int* target = malloc_unwrap(sizeof(int), 1, "[array_tests] failed to alloc int value");
    *target = array.len / 2;

    size_t target_index = array_find(&array, target, &int_eq);
    assert_eq(target_index, (size_t)*target);

    array_free(&array, NULL);
    free(target);

    end_test();
}


void test_find_elem_not_found_when_missing() {
    start_test();

    array_t array = alloc_int_data(3);

    for (size_t i = 0; i < array.len; i++) {
        int* val = array_at(&array, i);
        *val = i;
    }

    int* target = malloc_unwrap(sizeof(int), 1, "[array_tests] failed to alloc int value");
    *target = array.len + 1;

    size_t target_index = array_find(&array, target, &int_eq);
    assert_eq(target_index, (size_t)-1);

    array_free(&array, NULL);
    free(target);

    end_test();
}

// array_find: null elem_eq panic test?


void run_array_tests() {
    start_suite();

    test_array_init_and_freed_correctly_with_elem_free();
    test_array_init_and_freed_correctly_no_elem_free();

    test_first_index_accessed_correctly();
    test_mid_index_accessed_correctly();
    test_last_index_accessed_correctly();

    test_first_index_modified_correctly();
    test_mid_index_modified_correctly();
    test_last_index_modified_correctly();

    test_find_elem_found_when_present();
    test_find_elem_not_found_when_missing();

    end_suite();
}
