#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = 0;
  if (!A || (A->rows < 1) || (A->columns < 1) || !result)
    status = 1;
  else if (A->columns != A->rows)
    status = 2;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    if (A->rows != 1) {
      matrix_t B;
      s21_create_matrix(A->rows, A->rows, &B);
      for (int sign = 0, i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          find_minor(A->matrix, B.matrix, i, j, A->rows);
          sign = ((i + j) % 2 == 0) ? 1 : (-1);
          result->matrix[i][j] = sign * find_determinant(&B, A->rows - 1);
        }
      }
      s21_remove_matrix(&B);
    } else
      result->matrix[0][0] = A->matrix[0][0];
  }
  return status;
}