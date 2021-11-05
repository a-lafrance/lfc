#ifndef LFC_STR_HEADER
#define LFC_STR_HEADER

// is str really a collection? i mean kind of

#include <stdint.h>
#include <stdlib.h>

#define STR_DEFAULT_CAPACITY (size_t)32

// FUTURE: better string encoding that doesn't rely on char and ascii (like utf-8 or something)

/// An ASCII-encoded string wrapper around char* that provides additional safety & error-handling guarantees.
/// Much like Rust's `String`, `str_t` is an owned, mutable string type that manages its own internal string "buffer",
/// which is growable like `vector_t`. It provides basic string manipulation methods that, again, mutate the string directly.
/// Also, `str_t` is not null-terminated because it tracks length & capacity separately, so that would be a waste of a character.

typedef struct {
    char* buffer;
    size_t len;
    size_t capacity;
} str_t;

// Initialize a new, empty string.
void str_init(str_t* str);

// Initialize a string from the string literal, copying it into the buffer.
void str_from(str_t* str, char* literal);

// Free the string & its contents.
void str_free(str_t* str);

// Push the character onto the end of the string, expanding if necessary. Note that,
// much like vector's push, its runtime is O(1) amortized over many operations.
void str_push(str_t* str, char c);

// Push the contents of the string onto the end of the string.
void str_pushstr(str_t* str, str_t* to_push);

// TODO: push string literal
    // could change str_pushstr to str_push_str so that this can be str_push_strlit
    // could also call it str_pushlit
    // also rename str_push to str_pushc for clarity

// Pop the last character off of the string, or panic if the string is empty. Like vector,
// string never deallocates on pop.
char str_poplast(str_t* str);

// Retrieve the character at the given index in the string. Panics if the index is out of bounds.
char str_get(str_t* str, size_t index);

// Retrieve a pointer to the character at the given index in the string. Panics if the index is
// out of bounds.
char* str_at(str_t* str, size_t index);

// Checks whether or not the two strings are lexicographically equivalent. Note that this checks string
// equality, and does _not_ perform a full string comparison.
uint8_t str_eq(str_t* str, str_t* other);

// Returns whether or not the string is empty.
uint8_t str_is_empty(str_t* str);

// Check whether or not the string starts with the given character. Returns false if the string is
// empty, rather than panicking.
uint8_t str_starts_with(str_t* str, char c);

// Check whether or not the string starts with the given character. Returns false if the string is
// empty, rather than panicking.
uint8_t str_ends_with(str_t* str, char c);

size_t str_simple_hash(str_t* str);

// pending slicing:
    // trim
    // split
    // starts with str prefix
    // ends with str prefix
    // strip
        // strip_prefix
        // strip_suffix

#endif
