#include "lfc/collections/array.h"

#include "lfc/utils/optional.h"
#include "lfc/utils/panic.h"

#include <stdlib.h>

void array_new(array_t* array) {
    array->len = 0;
    array->data = NULL;
}

void array_init(array_t* array, void* data, size_t len) {
    array->data = data;
    array->len = len;
}

void* array_get(array_t* array, size_t index) {
    if (index >= array->len) {
        panic(EXIT_FAILURE, "index %li out of bounds of array of length %li", index, array->len);
    }

    return array->data + index;
}

option_t array_find(array_t* array, void* elem, int (*elem_eq)(void*, void*)) {
    for (int i = 0; i < array->len; i++) {
        if (elem_eq(array + i, elem)) {
            return option_new(i);
        }
    }

    return option_null();
}
