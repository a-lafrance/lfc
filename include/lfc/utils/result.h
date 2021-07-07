#ifndef LFC_RESULT_HEADER
#define LFC_RESULT_HEADER

#define RESULT_SUCCESS 0
#define RESULT_FAILURE -1

typedef struct {
    int status;
    void* data; // TODO: error type
} result_t;

void result_init(result_t* result, int status, void* data);
int result_is_success(result_t* result);
int result_is_failure(result_t* result);
void* result_unwrap(result_t* result);

#endif
