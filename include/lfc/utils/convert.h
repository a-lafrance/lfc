#ifndef LFC_CONVERT_HEADER
#define LFC_CONVERT_HEADER

#include <stdint.h>
#include "lfc/collections/str.h"

// itoa and itos convert an integer to its string representation, storing it either in a null-terminated
// character buffer or an lfc owned string
char* itoa(int32_t n);
str_t itos(int32_t n);

// FUTURE: extend this for...
    // different bases
    // long integers
    // unsigned integers?

#endif
