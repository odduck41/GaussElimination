#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

long long gcd(const long long a, const long long b) {
    return b ? gcd(b, a % b) : a;
}

Mtype* simplify(Mtype* m) {
    if (m->numerator == 0 && m->denominator == 0) {
        m->numerator = m->denominator = 1;
        return m;
    }
    if (m->numerator == 0) {
        m->denominator = 1;
        return m;
    }
    if (m->denominator == 0) {
        m->numerator = 1;
        return m;
    }
    long long gcd_ = gcd(m->numerator, m->denominator);
    m->numerator /= gcd_;
    m->denominator /= gcd_;
    return m;
}

Mtype* scanElement(Mtype* el) {
    el->numerator = 0;
    el->denominator = 1;
    char now;
    scanf(" %c", &now);
    while ('0' <= now && now <= '9') {
        el->numerator *= 10;
        el->numerator += now - '0';
        scanf("%c", &now);
    }

    if (now != '.') return el;

    scanf("%c", &now);
    while ('0' <= now && now <= '9') {
        el->numerator *= 10;
        el->numerator += now - '0';
        el->denominator *= 10;
        scanf("%c", &now);
    }

    return simplify(el);
}

void printElement(const Mtype* el) {
    printf("%lld/%lld", el->numerator, el->denominator);
}

void printElementAsDouble(const Mtype* el) {
    double res = (double)el->numerator;
    res /= (double)el->denominator;
    printf("%.7lf", res);
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

Matrix* copy(const Matrix* m) {
    Matrix* matrix = malloc(sizeof(Matrix));

    matrix->k = m->k;

    matrix->size_ = m->size_;
    const size_t sz = matrix->size_;

    matrix->matrix_ = (Mtype**)malloc(sz * sizeof(Mtype*));
    for (size_t i = 0; i < sz; ++i) {
        matrix->matrix_[i] = (Mtype*)malloc(sz * sizeof(Mtype));
        for (size_t j = 0; j < sz; ++j) {
            matrix->matrix_[i][j].numerator = m->matrix_[i][j].numerator;
            matrix->matrix_[i][j].denominator = m->matrix_[i][j].denominator;
        }
    }

    return matrix;
}

Matrix* scanMatrix(Matrix* m) {
    for (size_t i = 0; i < m->size_; ++i) {
        for (size_t j = 0; j < m->size_; ++j) {
            scanElement(m->matrix_[i] + j);
            simplify(m->matrix_[i] + j);
        }
    }
    return m;
}

void printMatrix(const Matrix* m) {
    for (size_t i = 0; i < m->size_; ++i) {
        for (size_t j = 0; j < m->size_; ++j) {
            printElement(m->matrix_[i] + j);
            printf(" ");
        }
        printf("\n");
    }
}

void printMatrixDoubles(const Matrix* m) {
    for (size_t i = 0; i < m->size_; ++i) {
        for (size_t j = 0; j < m->size_; ++j) {
            printElementAsDouble(m->matrix_[i] + j);
            printf(" ");
        }
        printf("\n");
    }
}

Matrix* swapLines(Matrix* m, const size_t line1, const size_t line2) {
    m->k.numerator *= -1;
    Mtype* tmp = m->matrix_[line1];
    m->matrix_[line1] = m->matrix_[line2];
    m->matrix_[line2] = tmp;
    return m;
}

Matrix* mulLine(Matrix* m, const size_t line, const Mtype k) {
    m->k.numerator *= k.numerator;
    m->k.denominator *= k.denominator;
    for (size_t i = 0; i < m->size_; ++i) {
        m->matrix_[line][i].numerator *= k.numerator;
        m->matrix_[line][i].denominator *= k.denominator;
        simplify(m->matrix_[line] + i);
    }
    return m;
}

Matrix* addLineToKline(Matrix* m, const size_t line1, const Mtype k, const size_t line2) {
    for (size_t i = 0; i < m->size_; ++i) {
        m->matrix_[line2][i].numerator *= k.numerator;
        m->matrix_[line2][i].denominator *= k.denominator;
    }

    for (size_t i = 0; i < m->size_; ++i) {
        m->matrix_[line1][i].numerator *= m->matrix_[line2][i].denominator;
        m->matrix_[line1][i].numerator +=
            m->matrix_[line2][i].numerator * m->matrix_[line1][i].denominator;
        m->matrix_[line1][i].denominator *= m->matrix_[line2][i].denominator;
        simplify(m->matrix_[line1] + i);
    }

    for (size_t i = 0; i < m->size_; ++i) {
        m->matrix_[line2][i].numerator /= k.numerator;
        m->matrix_[line2][i].denominator /= k.denominator;
        simplify(m->matrix_[line2] + i);
    }
    return m;
}

Matrix* destroy(Matrix* m) {
    for (size_t i = 0; i < m->size_; ++i) free(m->matrix_[i]);
    free(m->matrix_);

    return m;
}

