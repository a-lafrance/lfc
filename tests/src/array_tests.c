#include "array_tests.h"
#include "utils.h"

#include "lfc/collections/array.h"
#include "lfc/utils/mem.h"

// get
    // out of bounds panic test?
// set
    // index 0 works
    // index in middle works
    // last index works
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


size_t alloc_int_data(int** data) {
    size_t len = 5;
    *data = calloc_unwrap(sizeof(int), len, "[array_tests] failed to alloc array during test");

    // TODO: init array as well? it's probably fine to do that here (same goes for below)

    return len;
}

size_t alloc_struct_data(struct something** data) {
    size_t len = 3;
    *data = malloc_unwrap(sizeof(struct something), len, "[array_tests] failed to alloc array during test");

    for (int i = 0; i < len; i++) {
        struct something* thing = *data + i;
        thing->n = calloc_unwrap(sizeof(int), 1, "[array_tests] failed to alloc (struct something).n during test");
    }

    return len;
}


void test_array_init_and_freed_correctly_no_elem_free() {
    start_test();

    int* data;
    size_t len = alloc_int_data(&data);

    array_t array;
    array_init(&array, data, len, sizeof(int));

    assert_eq(array.data, data);
    assert_eq(array.len, len);
    assert_eq(array.elem_size, sizeof(int));

    array_free(&array, NULL);

    end_test();
}


void test_array_init_and_freed_correctly_with_elem_free() {
    start_test();

    struct something* data;
    size_t len = alloc_struct_data(&data);

    array_t array;
    array_init(&array, data, len, sizeof(struct something));

    assert_eq(array.data, data);
    assert_eq(array.len, len);
    assert_eq(array.elem_size, sizeof(struct something));

    array_free(&array, &something_free);

    end_test();
}


void test_first_index_accessed_correctly() {
    start_test();

    int* data;
    size_t len = alloc_int_data(&data);

    array_t array;
    array_init(&array, data, len, sizeof(int));

    int* first = array_get(&array, 0);
    assert_eq(*first, 0);

    array_free(&array, NULL);

    end_test();
}


void test_mid_index_accessed_correctly() {
    start_test();

    size_t len = 5;
    int* data = calloc_unwrap(sizeof(int), len, "[array_tests] failed to alloc array during test");

    array_t array;
    array_init(&array, data, len, sizeof(int));

    int* elem = array_get(&array, len / 2);
    assert_eq(*elem, 0);

    array_free(&array, NULL);

    end_test();
}


void test_last_index_accessed_correctly() {
    start_test();

    size_t len = 5;
    int* data = calloc_unwrap(sizeof(int), len, "[array_tests] failed to alloc array during test");

    array_t array;
    array_init(&array, data, len, sizeof(int));

    int* last = array_get(&array, len - 1);
    assert_eq(*last, 0);

    array_free(&array, NULL);

    end_test();
}


void run_array_tests() {
    start_suite();

    test_array_init_and_freed_correctly_with_elem_free();
    test_array_init_and_freed_correctly_no_elem_free();

    test_first_index_accessed_correctly();
    test_mid_index_accessed_correctly();
    test_last_index_accessed_correctly();

    end_suite();
}
