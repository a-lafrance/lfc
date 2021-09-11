#ifndef LFC_HASH_HEADER
#define LFC_HASH_HEADER

#include <stdlib.h>

/// A hash "trait" & simple hash functions. By "trait" I just mean general interface
/// for implementing hashing -- it just specifies the contract required for hashing to work.
/// Two hash functions are provided: one for ints and one for strings. Both are very simple,
/// and are more or less the bare minimum in terms of actual functionality.

typedef size_t (*hash_fn_t)(void*);

/// So simple, it just returns the value itself. Note that this operates on anything that will fit
/// in a `size_t`, not specifically the `int` type.
size_t int_simple_hash(size_t* x);

/// Hashes the string according to __strbase_simple_hash for all characters in the string.
size_t barestr_simple_hash(char* str);

/// Hashes the first n characters of the string by calculating a polynomial of based on its characters. If the pointer provided
/// is null, the function panics.
size_t __strbase_simple_hash(char* str, size_t len);

// TODO: more & better hashes

#endif
