#ifndef LFC_PANIC_HEADER
#define LFC_PANIC_HEADER

#include <stdio.h>
#include <stdlib.h>

/// A simple error-handling system. Although there is no stack-unwinding, this system is just a simple
/// way to print an error message to the user before exiting. It prints a message to stderr, along with
/// some basic debug data that specifies where the error occurred.

#define panic(estatus, fmt_str, ...) fprintf(stderr, "[%s:%d @ %s] program panicked due to error:\n\t" fmt_str "\n", \
                                            __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__); \
                                    exit(estatus);

#define guard(estatus, condition) if (!(condition)) { panic(estatus, "guard failed: %s", #condition) } // "panic if false"
#define unwrap(estatus, ptr) if (ptr == NULL) { panic(estatus, "failed to unwrap '%s'", #ptr) }

#endif
