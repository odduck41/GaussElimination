#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"



int main() {
    long long size;
    Mtype el;
    el = *scanElement(&el);
    printf("%lld/%lld\n", el.numerator, el.denominator);
}
