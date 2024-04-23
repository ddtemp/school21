#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *remove) {
  if (remove) {
    for (int i = 0; i < remove->rows; ++i) {
      free(remove->matrix[i]);
    }
    free(remove->matrix);
    remove->matrix = NULL;
    remove->rows = 0;
    remove->columns = 0;
  }
}