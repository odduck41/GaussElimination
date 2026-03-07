#include "Test.h"

#include <stdio.h>

inline Matrix* generate(const size_t sz) {
    Matrix* m = create(sz);
    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < sz; ++j) {
            long long x = random() % 2000;
            m->matrix_[i][j].numerator = random();
            m->matrix_[i][j].denominator = 1 + (m->matrix_[i][j].numerator + random()) / x
                + random() % 100
                + random() % 10;
        }
    }
    return m;
}


inline void test() {
    srand(time(NULL));
    for (size_t i = 0; i < 30; ++i) {
        Matrix* m = generate(random() % 10);
        printMatrix(m);
        Mtype gauss = calculateWithGaussMethod(m);
        Mtype stupid = stupidCalculate(m);
        // assert((gauss.numerator * stupid.denominator == gauss.denominator * stupid.numerator));
        if (gauss.numerator * stupid.denominator != gauss.denominator * stupid.numerator) {
            printf("Gauss=");
            printElementAsDouble(&gauss);
            printf("\nMinor=");
            printElementAsDouble(&stupid);
            printf("\n");
            assert(0);
        }
        printf("OK: Gauss calculated equal to minor calculated:\n");
        printElementAsDouble(&gauss);
        printf("==");
        printElementAsDouble(&stupid);
        printf("\n---\n\n");
        free(destroy(m));
    }
}

