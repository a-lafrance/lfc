#include "lfc/collections/array.h"
#include "lfc/utils/panic.h"

#include <stdlib.h>

void array_new(array_t* array, size_t elem_size) {
    array->len = 0;
    array->data = NULL;
    array->elem_size = elem_size;
}

void array_init(array_t* array, void* data, size_t len, size_t elem_size) {
    array->data = data;
    array->len = len;
    array->elem_size = elem_size;
}

void array_free(array_t* array, void (*elem_free)(void*)) {
    if (elem_free != NULL) {
        for (int i = 0; i < array->len; i++) {
            void* elem = array_get(array, i);
            (*elem_free)(elem)l;
        }
    }

    free(array->data); // FIXME: but what if data is stack-allocated and doesn't need to be freed? Unlikely enough to ignore?
}

void* array_get(array_t* array, size_t index) {
    if (index >= array->len) {
        panic(EXIT_FAILURE, "index %li out of bounds of array of length %li", index, array->len);
    }

    return array->data + index * elem_size;
}

size_t array_find(array_t* array, void* target, int (*elem_eq)(void*, void*)) {
    for (size_t i = 0; i < array->len; i++) {
        void* elem = array_get(array, i);

        if (elem_eq(elem, target)) {
            return i;
        }
    }

    return -1;
}
