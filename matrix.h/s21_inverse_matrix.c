#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || (A->rows < 1) || (A->columns < 1) || !result)
    return 1;
  else if (A->rows != A->columns)
    return 2;
  else {
    double det = 0.0;
    s21_determinant(A, &det);
    if (fabs(det) < 1e-6)
      return 2;
    else if (A->rows == 1) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = (1 / det);
    } else {
      matrix_t B;
      s21_calc_complements(A, result);
      s21_transpose(result, &B);
      s21_remove_matrix(result);
      s21_mult_number(&B, (1.0 / det), result);
      s21_remove_matrix(&B);
    }
  }
  return 0;
}