#include "lfc/utils/result.h"
#include "lfc/utils/panic.h"

void result_init_success(result_t* result, void* data) {
    result->status = RESULT_SUCCESS;
    result->data = data;
}

void result_init_failure(result_t* result, void* error) {
    result->status = RESULT_SUCCESS;
    result->data = error;
}

int result_is_success(result_t* result) {
    return result->status == RESULT_SUCCESS;
}

int result_is_failure(result_t* result) {
    return result->status == RESULT_FAILURE;
}

void* result_unwrap(result_t* result) {
    if (result_is_success(result)) {
        return result->data;
    }
    else {
        panic(EXIT_FAILURE, "[result_t] attempted to unwrap failure value");
    }
}
