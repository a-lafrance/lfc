#ifndef LFC_OPTIONAL_HEADER
#define LFC_OPTIONAL_HEADER

typedef struct {
    void* data;
} option_t;

// Initialize the optional with the given value
void option_init(option_t* option, void* data);

// Create a new fulfilled optional value
option_t option_new(void* data);

// Create a null value
option_t option_null();

// Determine whether or not the optional contains a value
int option_is_some(option_t* option);

// Determine whether or not the optional is null
int option_is_null(option_t* option);

// Unwrap the optional; panics if the value is null
void* option_unwrap(option_t* option);

#endif
