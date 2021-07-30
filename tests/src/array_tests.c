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

    array_free(&array, &something_free);

    end_test();
}


void test_first_index_accessed_correctly() {
    start_test();

    array_t array = alloc_int_data(3);
    int* first = array_get(&array, 0);
    assert_eq(*first, 0);

    array_free(&array, NULL);

    end_test();
}


void test_mid_index_accessed_correctly() {
    start_test();

    array_t array = alloc_int_data(3);
    int* elem = array_get(&array, array.len / 2);
    assert_eq(*elem, 0);

    array_free(&array, NULL);

    end_test();
}


void test_last_index_accessed_correctly() {
    start_test();

    array_t array = alloc_int_data(3);
    int* last = array_get(&array, array.len - 1);
    assert_eq(*last, 0);

    array_free(&array, NULL);

    end_test();
}

// array_get: out of bounds panic test?


void test_first_index_modified_correctly() {
    start_test();

    /* --- Without cleanup --- */
    array_t int_array = alloc_int_data(3);

    int* new_int = malloc_unwrap(sizeof(int), 1, "[array_tests] failed to alloc int");
    *new_int = 3;
    array_set(&int_array, 0, new_int, NULL);

    int* first_int = array_get(&int_array, 0);
    assert_eq(*first_int, *new_int);

    array_free(&int_array, NULL);
    free(new_int);

    /* --- With cleanup --- */
    array_t struct_array = alloc_struct_data(3);

    struct something* new_struct = malloc_unwrap(sizeof(struct something), 1, "[array_tests] failed to alloc struct");
    something_init(new_struct, 5);

    array_set(&struct_array, 0, new_struct, &something_free);

    struct something* first_struct = array_get(&struct_array, 0);
    assert_eq(*(first_struct->n), *(new_struct->n));

    array_free(&struct_array, NULL);
    free(new_struct);

    end_test();
}


void test_mid_index_modified_correctly() {
    start_test();

    /* --- Without cleanup --- */
    array_t int_array = alloc_int_data(3);

    int* new = malloc_unwrap(sizeof(int), 1, "[array_tests] failed to alloc int");
    *new = 3;
    size_t index = int_array.len / 2;
    array_set(&int_array, index, new, NULL);

    int* elem = array_get(&int_array, index);
    assert_eq(*elem, *new);

    array_free(&int_array, NULL);
    free(new);

    /* --- With cleanup --- */
    array_t struct_array = alloc_struct_data(5);

    struct something* new_struct = malloc_unwrap(sizeof(struct something), 1, "[array_tests] failed to alloc struct");
    something_init(new_struct, 5);

    size_t struct_index = 2;
    array_set(&struct_array, struct_index, new_struct, &something_free);

    struct something* struct_elem = array_get(&struct_array, struct_index);
    assert_eq(*(struct_elem->n), *(new_struct->n));

    array_free(&struct_array, NULL);
    free(new_struct);

    end_test();
}


void test_last_index_modified_correctly() {
    start_test();

    /* --- Without cleanup --- */
    array_t int_array = alloc_int_data(3);

    int* new = malloc_unwrap(sizeof(int), 1, "[array_tests] failed to alloc int");
    *new = 3;
    size_t index = int_array.len - 1;
    array_set(&int_array, index, new, NULL);

    int* elem = array_get(&int_array, index);
    assert_eq(*elem, *new);

    array_free(&int_array, NULL);
    free(new);

    /* --- With cleanup --- */
    array_t struct_array = alloc_struct_data(5);

    struct something* new_struct = malloc_unwrap(sizeof(struct something), 1, "[array_tests] failed to alloc struct");
    something_init(new_struct, 5);

    size_t struct_index = struct_array.len - 1;
    array_set(&struct_array, struct_index, new_struct, &something_free);

    struct something* last_struct = array_get(&struct_array, struct_index);
    assert_eq(*(last_struct->n), *(new_struct->n));

    array_free(&struct_array, NULL);
    free(new_struct);

    end_test();
}


void test_find_elem_found_when_present() {
    start_test();

    array_t array = alloc_int_data(5);

    for (size_t i = 0; i < array.len; i++) {
        int* val = array_get(&array, i);
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
        int* val = array_get(&array, i);
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
