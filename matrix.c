#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Mtype* scanElement(Mtype* el) {
    el->numerator = 0;
    el->denominator = 1;
    char now;
    do {
        scanf(" %c", &now);
        el->numerator *= 10;
        el->numerator += now - '0';
    } while ('0' <= now && now <= '9');

    if (now == ' ') return el;

    do {
        scanf("%c", &now);
        el->numerator *= 10;
        el->numerator += now - '0';
        el->denominator *= 10;
    } while ('0' <= now && now <= '9');

    return el;
}

