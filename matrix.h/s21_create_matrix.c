#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (!result || rows < 1 || columns < 1) {
    return 1;
  } else {
    result->matrix = (double **)malloc(sizeof(double *) * rows);
    result->rows = rows;
    result->columns = columns;

    for (int i = 0; i < result->rows; ++i) {
      result->matrix[i] = malloc(sizeof(double) * result->columns);
    }
  }
  return 0;
}