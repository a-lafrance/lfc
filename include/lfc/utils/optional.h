#ifndef LFC_OPTIONAL_HEADER
#define LFC_OPTIONAL_HEADER

typedef struct {
    void* data;
} option_t;

void option_init(option_t* option, void* data);

int option_is_some(option_t* option);
int option_is_null(option_t* option);

void* option_unwrap(option_t* option);

#endif
