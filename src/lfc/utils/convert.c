#include "lfc/utils/convert.h"

#include <math.h>
#include <stdint.h>

#include "lfc/collections/str.h"
#include "lfc/utils/mem.h"

// Because the max number of digits in an int is 10, it can be stored in an unsigned char
// This function also takes into account whether or not a negative sign is required
uint8_t __n_chars_required(int32_t n) {
    uint8_t sign = 0;
    uint32_t magnitude = n;

    if (n < 0) {
        sign = 1;
        magnitude = (int64_t)n * -1;
    } else if (n == 0) {
        return 1;
    }

    return ceil(log10(magnitude)) + sign;
}

// NOTE: this function assumes the buffer has enough space to store the
// contents of the number's string repr inside of it. Violating this assumption
// leads to buffer overflow, which obviously is undefined behavior.
void __fill_buf(int32_t n, char* buf) {
    uint8_t buflen = __n_chars_required(n);
    uint32_t magnitude = n;

    if (n < 0) {
        // If n is negative, add the sign at the front of the buffer and revert to positive
        buf[0] = '-';
        magnitude = (int64_t)n * -1;
    } else if (n == 0) {
        buf[0] = '0';
        return;
    }

    uint8_t i = 0;

    while (magnitude > 0) {
        // Grab each digit and insert it in the back of the buffer
        uint8_t digit = magnitude % 10;

        // NOTE: a bit of unsafety here: there's overflow if buflen is 0, but I think
        // that's not possible because of the range of log
        uint8_t index = buflen - 1 - i;
        buf[index] = '0' + digit;

        magnitude /= 10;
        i++;
    }
}

char* itoa(int32_t n) {
    // Allocate a buffer that can hold the number's string repr,
    // _and_ a null terminator
    uint8_t buflen = __n_chars_required(n) + 1;
    char* buf = malloc_unwrap(sizeof(char), buflen, "[itoa] failed to alloc buffer");

    // Fill the buffer and add a null terminator
    __fill_buf(n, buf);
    buf[buflen - 1] = '\0';

    return buf;
}

str_t itos(int32_t n) {
    // Allocate a buffer that can hold the number's string repr,
    // without a null terminator
    uint8_t buflen = __n_chars_required(n);
    char* buf = malloc_unwrap(sizeof(char), buflen, "[itoa] failed to alloc buffer");

    // Fill the buffer
    __fill_buf(n, buf);

    // Initialize the string from the buffer
    str_t str;
    str_frombuf(&str, buf, buflen);
    return str;
}
