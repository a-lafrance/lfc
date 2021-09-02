#include "lfc/collections/str.h"

#include <stdlib.h>
#include <string.h>

#include "lfc/utils/mem.h"

void str_init(str_t* str) {
    str->capacity = STR_DEFAULT_CAPACITY;
    str->data = malloc_unwrap(sizeof(char), str->capacity, "[str_init] failed to alloc string data");
    str->len = 0;
}

void str_from(str_t* str, char* literal) {
    str->len = strlen(literal);
    str->capacity = str->len + STR_DEFAULT_CAPACITY;
    str->data = malloc_unwrap(sizeof(char), str->capacity, "[str_init] failed to alloc string data");
    memcpy(str->data, literal, str->len);
}

void str_free(str_t* str) {
    free(str->data);
}
