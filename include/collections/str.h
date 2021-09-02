#ifndef LFC_STR_HEADER
#define LFC_STR_HEADER

// is str really a collection? i mean kind of

#include <stdlib.h>

#define STR_DEFAULT_CAPACITY (size_t)32

// Not guaranteed to be null-terminated -- that's a waste of a character
typedef struct {
    char* data;
    size_t len;
    size_t capacity;
} str_t;

void str_init(str_t* str);
void str_from(str_t* str, char* literal); // init from string literal
void str_free(str_t* str);

#endif
