#include "lfc/utils/convert.h"

#include <math.h>

#include "lfc/collections/str.h"
#include "lfc/utils/mem.h"

// Because the max number of digits in an int is 10, it can be stored in an unsigned char
// This function also takes into account whether or not a negative sign is required
unsigned char __n_chars_required(int n) {
    return ceil(log10(n)) + (n < 0 ? 1 : 0);
}

// NOTE: this function assumes the buffer has enough space to store the
// contents of the number's string repr inside of it. Violating this assumption
// leads to buffer overflow, which obviously is undefined behavior.
void __fill_buf(int n, char* buf) {
    unsigned char buflen = __n_chars_required(n);

    // If n is negative, add the sign at the front of the buffer
    if (n < 0) {
        buf[0] = '-';
    }

    unsigned char i = 0;

    while (n > 0) {
        // Grab each digit and insert it in the back of the buffer
        unsigned char digit = n % 10;

        // NOTE: a bit of unsafety here: there's overflow if buflen is 0, but I think
        // that's not possible because of the range of log
        unsigned char index = buflen - 1 - i;
        buf[index] = '0' + digit;

        n /= 10;
        i++;
    }
}

char* itoa(int n) {
    // Allocate a buffer that can hold the number's string repr,
    // _and_ a null terminator
    unsigned char buflen = __n_chars_required(n) + 1;
    char* buf = malloc_unwrap(sizeof(char), buflen, "[itoa] failed to alloc buffer");

    // Fill the buffer and add a null terminator
    __fill_buf(n, buf);
    buf[buflen - 1] = '\0';

    return buf;
}

str_t itos(int n) {
    // Allocate a buffer that can hold the number's string repr,
    // without a null terminator
    unsigned char buflen = __n_chars_required(n);
    char* buf = malloc_unwrap(sizeof(char), buflen, "[itoa] failed to alloc buffer");

    // Fill the buffer
    __fill_buf(n, buf);

    // Initialize the string from the buffer
    str_t str;
    str_frombuf(&str, buf, buflen);
    return str;
}
