#ifndef LFC_MEM_HEADER
#define LFC_MEM_HEADER

#include <stdlib.h>

// TODO: generic free function type?

// Wrapper around malloc that panics on error
void* malloc_unwrap(size_t elem_size, size_t elems, char* error_msg);

// Wrapper around realloc that panics on error
void* realloc_unwrap(void* ptr, size_t elem_size, size_t elems, char* error_msg);

// Wrapper around calloc that panics on error
void* calloc_unwrap(size_t elem_size, size_t elems, char* error_msg);

#endif
