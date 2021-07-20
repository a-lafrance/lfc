#include "array_tests.h"
#include "utils.h"

#include "lfc/collections/array.h"
#include "lfc/utils/mem.h"

#include <stdlib.h>

// get
    // out of bounds panic test?
// set
    // index 0 works
        // with cleanup
        // without cleanup
    // index in middle works
        // with cleanup
        // without cleanup
    // last index works
        // with cleanup
        // without cleanup
    // ^ all with and without cleanup
// find
    // elem is found
    // elem not found
    // null elem_eq panic test?

struct something {
    int* n;
};

void something_free(void* thing) {
    struct something* something = thing;
    free(something->n);
}


array_t alloc_int_data(size_t len) {
    int* data = calloc_unwrap(sizeof(int), len, "[array_tests] failed to alloc array during test");

    array_t array;
    array_init(&array, data, len, sizeof(int));

    return array;
}

array_t alloc_struct_data(size_t len) {
    struct something* data = malloc_unwrap(sizeof(struct something), len, "[array_tests] failed to alloc array during test");

    for (int i = 0; i < len; i++) {
        struct something* thing = data + i;
        thing->n = calloc_unwrap(sizeof(int), 1, "[array_tests] failed to alloc (struct something).n during test");
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


void test_first_index_modified_correctly() {
    start_test();

    array_t int_array = alloc_int_data(3);

    int* new = malloc_unwrap(sizeof(int), 1, "[array_t] failed to alloc int");
    *new = 3;
    array_set(&int_array, 0, new, NULL);

    int* first = array_get(&int_array, 0);
    assert_eq(*first, *new);

    array_free(&int_array, NULL);
    free(new);

    end_test();
}


void test_mid_index_modified_correctly() {
    start_test();

    array_t int_array = alloc_int_data(3);

    int* new = malloc_unwrap(sizeof(int), 1, "[array_t] failed to alloc int");
    *new = 3;
    size_t index = int_array.len / 2;
    array_set(&int_array, index, new, NULL);

    int* elem = array_get(&int_array, index);
    assert_eq(*elem, *new);

    array_free(&int_array, NULL);
    free(new);

    end_test();
}


void test_last_index_modified_correctly() {
    start_test();

    array_t int_array = alloc_int_data(3);

    int* new = malloc_unwrap(sizeof(int), 1, "[array_t] failed to alloc int");
    *new = 3;
    size_t index = int_array.len - 1;
    array_set(&int_array, index, new, NULL);

    int* elem = array_get(&int_array, index);
    assert_eq(*elem, *new);

    array_free(&int_array, NULL);
    free(new);

    end_test();
}


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

    end_suite();
}
