#include <stdio.h>
#include <string.h>

void run_array_tests();
void run_hash_tests();
void run_linkedlist_tests();
void run_set_tests();
void run_vector_tests();

// TODO: fancier interface

int main(int argc, char** argv) {
    if (argc == 1) {
        run_array_tests();
        run_hash_tests();
        run_linkedlist_tests();
        run_set_tests();
        run_vector_tests();
    } else {
        for (int i = 1; i < argc; i++) {
            char* suite = argv[i];

            if (strcmp(suite, "array") == 0) {
                run_array_tests();
            } else if (strcmp(suite, "linkedlist") == 0) {
                run_linkedlist_tests();
            } else if (strcmp(suite, "set") == 0) {
                run_set_tests();
            } else if (strcmp(suite, "hash") == 0) {
                run_hash_tests();
            } else if (strcmp(suite, "vector") == 0) {
                run_vector_tests();
            } else {
                fprintf(stderr, "error: test suite '%s' not found\n", suite);
                return 2;
            }
        }
    }

    return 0;
}
