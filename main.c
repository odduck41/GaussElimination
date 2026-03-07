#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"



int main() {
    long long size;
    scanf("%lld", &size);
    Matrix* m = create(size);
    scanMatrix(m);
    printMatrixDoubles(m);
}
