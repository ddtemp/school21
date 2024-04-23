#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!A || (A->rows < 1) || (A->columns < 1) || !B || (B->rows < 1) ||
      (B->columns < 1) || !result) {
    return 1;
  } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
    return 2;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return 0;
}