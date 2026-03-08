#include <stdio.h>
#include <stdlib.h>

#include "matrix/calc/DetCalculation.h"


int main() {
    size_t sz;
    scanf("%zu", &sz);
    Matrix* m = create(sz);
    scanMatrix(m);
    Matrix* cp = copy(m);

    const Mtype res = calculateWithGaussMethod(m);
    const Mtype res2 = stupidCalculate(cp);
    printf("{\n\"Gauss_method_result\": \"");
    printElementAsDouble(&res);
    printf("\",\n");
    printf("\"Minor_method_result\": \"");
    printElementAsDouble(&res2);
    printf("\"\n}");

    free(destroy(cp));
    free(destroy(m));
}
