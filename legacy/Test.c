#include "Test.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

#include "../matrix/calc/DetCalculation.h"

// This tests don't work, because overflow
inline Matrix* generate(const size_t sz) {
    Matrix* m = create(sz);
    for (size_t i = 0; i < sz; ++i) {
        for (size_t j = 0; j < sz; ++j) {
            m->matrix_[i][j].numerator = random() % 100;
            m->matrix_[i][j].denominator = 1 + random() % 100;
            simplify(m->matrix_[i] + j);
        }
    }
    return m;
}


inline void test() {
    srand(time(NULL));

    for (size_t i = 0; i < 30; ++i) {
        Matrix* m = generate(random() % 10);
        printMatrix(m);
        Matrix* cp = copy(m);
        Mtype gauss = calculateWithGaussMethod(m); simplify(&gauss);
        Mtype stupid = stupidCalculate(cp); simplify(&stupid);
        // assert((gauss.numerator * stupid.denominator == gauss.denominator * stupid.numerator));
        if (gauss.numerator * stupid.denominator != gauss.denominator * stupid.numerator) {
            printf("Gauss=");
            printElement(&gauss);
            printf("\nMinor=");
            printElement(&stupid);
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

