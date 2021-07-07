#ifndef LFC_RESULT_HEADER
#define LFC_RESULT_HEADER

#define RESULT_SUCCESS 0
#define RESULT_FAILURE -1

typedef struct {
    int status;
    void* data; // TODO: error type
} result_t;

// Initialize the result as a success with the given data
void result_init_success(result_t* result, void* data);

// Initialize the result as a failure with the given error
void result_init_failure(result_t* result, void* error);

// Determine whether or not the result is a success
int result_is_success(result_t* result);

// Determine whether or not the result is a failure
int result_is_failure(result_t* result);

// Unwrap the result to retrieve the value; panics if the value is a failure
void* result_unwrap(result_t* result);

#endif
