#ifndef LFC_TESTS_UTILS_HEADER
#define LFC_TESTS_UTILS_HEADER

struct something {
    int* n;
};

void something_init(struct something* thing, int n);
void something_init_zeroed(struct something* thing);
void something_free(/* struct something* */ void* thing);

#endif
