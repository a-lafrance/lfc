#ifndef LFC_RESULT_HEADER
#define LFC_RESULT_HEADER

#define RESULT_SUCCESS 0
#define RESULT_FAILURE -1

typedef struct {
    int status;
    void* data;
} result_t;

void result_init(result_t* result, int status, void* data);
int is_success(result_t* result);
int is_failure(result_t* result);

#endif
