#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

Mtype* scanElement(Mtype* el) {
    el->numerator = 0;
    el->denominator = 1;
    char now;
    scanf(" %c", &now);
    while ('0' <= now && now <= '9') {
        el->numerator *= 10;
        el->numerator += now - '0';
        scanf(" %c", &now);
    }

    if (now != '.') return el;

    scanf("%c", &now);
    while ('0' <= now && now <= '9') {
        el->numerator *= 10;
        el->numerator += now - '0';
        el->denominator *= 10;
        scanf("%c", &now);
    }

    return el;
}

void printElement(const Mtype* el) {
    printf("%lld/%lld", el->numerator, el->denominator);
}

void printElementAsDouble(const Mtype* el) {
    double res = (double)el->numerator;
    res /= (double)el->denominator;
    printf("%.4lf", res);
}

Matrix* create(const size_t sz) {
    Matrix* matrix = malloc(sizeof(Matrix));

    matrix->k.numerator = 1;
    matrix->k.denominator = 1;

    matrix->size_ = sz;

    matrix->matrix_ = (Mtype**)malloc(sz * sizeof(Mtype*));
    for (size_t i = 0; i < sz; ++i) {
        matrix->matrix_[i] = (Mtype*)malloc(sz * sizeof(Mtype));
        for (size_t j = 0; j < sz; ++j) {
            matrix->matrix_[i][j].numerator = 0;
            matrix->matrix_[i][j].denominator = 1;
        }
    }

    return matrix;
}
