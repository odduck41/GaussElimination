#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    long long numerator;
    long long denominator;
} Mtype;

typedef struct {
    Mtype** matrix_;
    size_t size_;
    Mtype k;
} Matrix;

Mtype* scanElement(Mtype*);

Matrix* create(size_t);
Matrix* scanMatrix(Matrix*);
Matrix* swapLines(Matrix*, size_t, size_t);
Matrix* mulLine(Matrix*, size_t, Mtype);
Matrix* addLineToKline(Matrix*, size_t, Mtype, size_t);
Matrix* destroy(Matrix*);

#endif // MATRIX_H
