#include "assert.h"

int main() {
    int x = 0;
    // assert(x > 0);
    assert_or(x == 1, "x isn't 1");
    return 0;
}
