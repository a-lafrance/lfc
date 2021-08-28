#include "lfc/utils/hash.h"
#include "lfc/utils/panic.h"

size_t int_simple_hash(size_t* x) {
    return *(size_t*)x;
}

size_t str_simple_hash(char* str) {
    if (str == NULL) {
        panic(1, "[str_simple_hash] str value must be non-null");
    }

    size_t hash = *str;

    while (*str != '\0') {
        str++;
        char c = *str;

        hash += 31 * c; // choose 31 as coefficient because it's a relatively large prime number
    }

    return hash;
}
