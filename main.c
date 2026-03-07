#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"



int main() {
    long long size;
    scanf("%lld", &size);
    Matrix* m = create(size);
    scanMatrix(m);
    printMatrixDoubles(m);
    printf("---\n");
    m = swapLines(m, size - 2, size - 1);
    printMatrixDoubles(m);
    printf("---\n");
    Mtype x;
    x.numerator = 1000;
    x.denominator = 1;
    m = mulLine(m, 0, x);
    printMatrixDoubles(m);
    printf("---\n");
    x.numerator = 1;
    m = addLineToKline(m, 0, x, 1);
    printMatrixDoubles(m);
    printf("---\n");

    free(destroy(m));
}
