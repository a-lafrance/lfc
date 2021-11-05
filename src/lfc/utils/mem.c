#include "lfc/utils/mem.h"

#include <stdlib.h>
#include "lfc/utils/panic.h"

void* malloc_unwrap(size_t elem_size, size_t elems, char* error_msg) {
    void* ptr = malloc(elems * elem_size);

    if (ptr == NULL) {
        panic(1, "[malloc] operation failed: %s", error_msg);
    }

    return ptr;
}

void* realloc_unwrap(void* ptr, size_t elem_size, size_t elems, char* error_msg) {
    void* new_ptr = realloc(ptr, elems * elem_size);

    if (new_ptr == NULL) {
        panic(1, "[realloc] operation failed: %s", error_msg);
    }

    return new_ptr;
}

void* calloc_unwrap(size_t elem_size, size_t elems, char* error_msg) {
    void* ptr = calloc(elems, elem_size);

    if (ptr == NULL) {
        panic(1, "[calloc] operation failed: %s", error_msg);
    }

    return ptr;
}
