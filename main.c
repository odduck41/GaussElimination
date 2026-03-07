#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Mtype calculateWithGaussMethod(Matrix* m) {
    for (size_t i = 0; i < m->size_; ++i) {
        for (size_t j = i + 1; j < m->size_; ++j) {
        }
    }
}

Mtype stupidCalculate(Matrix* m) {

}

int main() {
    size_t sz;
    scanf("%llu", &sz);
    Matrix* m = create(sz);
    Matrix* cp = copy(m);

    free(destroy(cp));
    free(destroy(m));
}
