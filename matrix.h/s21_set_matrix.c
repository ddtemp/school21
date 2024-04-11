#include "s21_matrix.h"

void set_matrix(double *nums, matrix_t *result) {
  int count = 0;
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = nums[count];
      count++;
    }
  }
}