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
    Mtype res = m->k;
    for (size_t i = 0; i < m->size_; ++i) {
        res.numerator *= m->matrix_[i][i].numerator;
        res.denominator *= m->matrix_[i][i].denominator;
    }

    simplify(&res);

    return res;
}

Mtype stupidCalculate(const Matrix* m) {
    if (m->size_ == 1) {
        return m->matrix_[0][0];
    }
    Mtype res;
    res.numerator = 0;
    res.denominator = 1;
    for (size_t i = 0; i < m->size_; ++i) {
        Mtype now;
        now.numerator = 1 - 2 * ((long long)i % 2);
        now.denominator = 1;
        now.numerator *= m->matrix_[0][i].numerator;
        now.denominator *= m->matrix_[0][i].denominator;
        simplify(&now);

        Matrix* nw = create(m->size_ - 1);

        for (size_t j = 0; j < nw->size_; ++j) {
            for (size_t k = 0; k < m->size_; ++k) {
                if (k != i)
                    nw->matrix_[j][k > i ? k - 1 : k] = m->matrix_[j + 1][k];
            }
        }
        Mtype M = stupidCalculate(nw);
        now.numerator *= M.numerator;
        now.denominator *= M.denominator;
        simplify(&now);
        free(destroy(nw));

        res.numerator *= now.denominator;
        now.numerator *= res.denominator;
        res.numerator += now.numerator;
        res.denominator *= now.denominator;
        simplify(&res);
    }
    return res;
}

int main() {
    size_t sz;
    scanf("%llu", &sz);
    Matrix* m = create(sz);
    scanMatrix(m);
    Matrix* cp = copy(m);

    const Mtype res = calculateWithGaussMethod(m);
    const Mtype res2 = stupidCalculate(cp);

    printElementAsDouble(&res);
    printf("\n");
    printElementAsDouble(&res2);

    free(destroy(cp));
    free(destroy(m));
}
