#include "s21_matrix.h"

int comparation(double x, double y) {
  if (fabs(x - y) > 1e-8) {
    return 1;
  }

  return 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL) {
    return FAILURE;
  }

  int status = SUCCESS;

  if ((A->columns != B->columns) || (A->rows != B->rows) ||
      (A->matrix == NULL) || (B->matrix == NULL)) {
    status = FAILURE;
  }

  for (int i = 0; i < A->rows && status == SUCCESS; ++i) {
    for (int j = 0; j < A->columns && status == SUCCESS; ++j) {
      if (comparation(A->matrix[i][j], B->matrix[i][j])) {
        status = FAILURE;
      }
    }
  }

  return status;
}
