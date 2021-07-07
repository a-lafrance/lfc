#include "lfc/utils/result.h"

void result_init(result_t* result, int status, void* data) {
    result->status = status;
    result->data = data;
}

int is_success(result_t* result) {
    return result->status == RESULT_SUCCESS;
}

int is_failure(result_t* result) {
    return result->status == RESULT_FAILURE;
}
