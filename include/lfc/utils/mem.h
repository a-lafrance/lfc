#ifndef LFC_MEM_HEADER
#define LFC_MEM_HEADER

#include <stdlib.h>

// NOTE: maybe for any destructor parameters, they should be stored on init so that there's less repeated code
typedef void (*free_fn_t)(void*);

// Wrapper around malloc that panics on error
void* malloc_unwrap(size_t elem_size, size_t elems, char* error_msg);

// Wrapper around realloc that panics on error
void* realloc_unwrap(void* ptr, size_t elem_size, size_t elems, char* error_msg);

// Wrapper around calloc that panics on error
void* calloc_unwrap(size_t elem_size, size_t elems, char* error_msg);

#endif
