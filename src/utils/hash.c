#include "lfc/utils/hash.h"

size_t int_simple_hash(void* x) {
    return *(size_t*)x;
}

size_t int_linear_hash(void* x, size_t a, size_t b) { /* h(x) = ax + b */
    return a * *(size_t*)x + b;
}
