#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (!A || (A->rows < 1) || (A->columns < 1) || !result) {
    return 1;
  } else if (A->columns != A->rows) {
    return 2;
  } else {
    *result = find_determinant(A, A->rows);
  }
  return 0;
}

double find_determinant(matrix_t *A, int size) {
  double det = 0;
  if (size == 1)
    det = A->matrix[0][0];
  else if (size > 1) {
    matrix_t temp;
    s21_create_matrix(size, size, &temp);
    for (int sign = 1, i = 0; i < size; i++, sign *= (-1)) {
      find_minor(A->matrix, temp.matrix, 0, i, size);
      det += sign * A->matrix[0][i] * find_determinant(&temp, size - 1);
    }
    s21_remove_matrix(&temp);
  }
  return det;
}

void find_minor(double **A, double **B, int row_limit, int column_limit,
                int size) {
  for (int row = 0, i = 0; row < size; row++) {
    for (int column = 0, j = 0; column < size; column++) {
      if (row != row_limit && column != column_limit) {
        B[i][j++] = A[row][column];
        if (j == (size - 1)) {
          j = 0;
          i++;
        }
      }
    }
  }
}
