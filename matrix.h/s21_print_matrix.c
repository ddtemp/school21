#include "s21_matrix.h"

void print_matrix(matrix_t *matrix) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      printf("%f ", matrix->matrix[i][j]);
    }
    printf("\n");
  }
}