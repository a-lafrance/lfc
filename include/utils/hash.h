#ifndef LFC_HASH_HEADER
#define LFC_HASH_HEADER

typedef size_t (*hash_fn_t)(void*);

// Not literally only operating on ints -- these hashes operate on anything that fits into a `size_t`
size_t int_simple_hash(void* x);
size_t int_linear_hash(void* x, size_t a, size_t b);

// TODO: string hashes
// TODO: better hashes

#endif
