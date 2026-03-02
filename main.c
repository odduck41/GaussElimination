#include <stdio.h>

struct Matrix {
    long long **matrix;
    size_t size = 0;
}

Matrix* create(size_t sz = 0) {
    Matrix* m = malloc(sizeof(Matrix));
    m->matrix = malloc(sz * sizeof(long long*));
    for (size_t i = 0; i < sz; ++i) {
        (m->matrix)[i] = malloc(sz * sizeof(long long));
	(m->matrix)[i][j] = 0;
    }
    return m;
}

void destroy(Matrix** mat) {
    auto m = *mat;
    for (size_t i = 0; i < m->size; ++i) {
        free((m->matrix)[i]);
    }
    free(m->matrix);
    free(m);
    *mat = nullptr;
}


int main() {
    
}
