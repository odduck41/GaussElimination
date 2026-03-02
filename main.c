#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long **matrix;
    size_t size;
} Matrix;

Matrix* create(size_t sz) {
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->matrix = (long long**)malloc(sz * sizeof(long long*));
    for (size_t i = 0; i < sz; ++i) {
        (m->matrix)[i] = (long long*)malloc(sz * sizeof(long long));
	for (size_t j = 0; j < sz; ++j) (m->matrix)[i][j] = 0;
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
