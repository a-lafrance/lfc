#include "lfc/utils/hash.h"

#include <string.h>
#include "lfc/utils/panic.h"

size_t int_simple_hash(int* x) {
    return (size_t)*x;
}

size_t barestr_simple_hash(char* str) {
    return __strbase_simple_hash(str, strlen(str));
}

size_t __strbase_simple_hash(char* str, size_t len) {
    if (str == NULL) {
        panic(1, "str value must be non-null");
    }

    size_t hash = 0;

    for (size_t i = 0; i < len; i++) {
        hash += i > 0 ? 31 * str[i] : str[i]; // choose 31 as coefficient because it's a relatively large prime number
    }

    return hash;
}
