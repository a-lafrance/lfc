#include "lfc/collections/array.h"
#include "lfc/utils/optional.h"

void array_new(array_t* array) {

}

void array_init(array_t* array, void* data, size_t len) {

}

void* array_get(array_t* array, size_t index) {
    return array->data; // TODO
}

void array_set(array_t* array, size_t index, void* value) {

}

option_t array_find(array_t* array, void* elem) {
    return option_null();
}
