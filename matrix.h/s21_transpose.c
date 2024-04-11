#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!A || (A->rows < 1) || (A->columns < 1) || !result) {
    return 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return 0;
}