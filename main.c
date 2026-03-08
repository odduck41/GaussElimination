#include <stdio.h>
#include <stdlib.h>

#include "DetCalculation.h"


int main() {
    size_t sz;
    scanf("%zu", &sz);
    Matrix* m = create(sz);
    scanMatrix(m);
    Matrix* cp = copy(m);

    const Mtype res = calculateWithGaussMethod(m);
    const Mtype res2 = stupidCalculate(cp);
    printf("Gauss method result: ");
    printElementAsDouble(&res);
    printf("\n");
    printf("Minor method result: ");
    printElementAsDouble(&res2);

    free(destroy(cp));
    free(destroy(m));
}
