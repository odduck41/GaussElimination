#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Mtype calculateWithGaussMethod(Matrix* m) {
    for (size_t i = 0; i < m->size_; ++i) {
        for (size_t j = i + 1; j < m->size_; ++j) {
            const auto a = m->matrix_[i][i].numerator * m->matrix_[j][i].denominator;
            const auto b = m->matrix_[j][i].numerator * m->matrix_[i][i].denominator;
            if (b && a > b) {
                m = swapLines(m, i, j);
            }
        }
        for (size_t j = i + 1; j < m->size_; ++j) {
            if (m->matrix_[j][i].numerator != 0) {
                Mtype k;
                k.numerator = -m->matrix_[i][i].denominator * m->matrix_[j][i].numerator;
                k.denominator = m->matrix_[i][i].numerator * m->matrix_[j][i].denominator;
                addLineToKline(m, j, k, i);
            }
        }
    }
    Mtype res;
    res.numerator = res.denominator = 1;
    for (size_t i = 0; i < m->size_; ++i) {
        res.numerator *= m->matrix_[i][i].numerator;
        res.denominator *= m->matrix_[i][i].denominator;
    }

    simplify(&res);

    return res;
}

Mtype stupidCalculate(Matrix* m) {

}

int main() {
    size_t sz;
    scanf("%llu", &sz);
    Matrix* m = create(sz);
    scanMatrix(m);
    Matrix* cp = copy(m);

    const Mtype res = calculateWithGaussMethod(m);

    printElementAsDouble(&res);

    free(destroy(cp));
    free(destroy(m));
}
