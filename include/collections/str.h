#ifndef LFC_STR_HEADER
#define LFC_STR_HEADER

// is str really a collection? i mean kind of

#include <stdint.h>

#define STR_DEFAULT_CAPACITY (size_t)32

// FUTURE: better string encoding that doesn't rely on char and ascii (like utf-8 or something)

// Not guaranteed to be null-terminated -- that's a waste of a character
typedef struct {
    char* data;
    size_t len;
    size_t capacity;
} str_t;

void str_init(str_t* str);
void str_from(str_t* str, char* literal); // init from string literal
void str_free(str_t* str);

void str_push(str_t* str, char c);
void str_pushstr(str_t* str, str_t* to_push);
char str_pop(str_t* str, char c);

char str_get(str_t* str, size_t index);
char* str_at(str_t* str, size_t index);

uint8_t str_is_empty(str_t* str);

uint8_t str_starts_with(str_t* str, char c);
uint8_t str_ends_with(str_t* str, char c);

// pending slicing:
    // trim
    // split
    // starts with str prefix
    // ends with str prefix
    // strip
        // strip_prefix
        // strip_suffix

#endif
