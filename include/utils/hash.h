#ifndef LFC_HASH_HEADER
#define LFC_HASH_HEADER

#include <stdlib.h>

typedef size_t (*hash_fn_t)(void*);

// Not literally only operating on ints -- these hashes operate on anything that fits into a `size_t`
size_t int_simple_hash(void* x);

size_t str_simple_hash(void* val);

// TODO: more & better hashes

#endif
