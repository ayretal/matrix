#include "s21_matrix.h"

int s21_isNotCorrect(matrix_t A) {
  int res = 1;
  if (A.rows > 0 && A.columns > 0 && A.matrix) res = 0;
  return res;
}

matrix_t s21_matrixCutCopy(matrix_t A, int row, int column) {
  matrix_t result;
  s21_create_matrix(A.rows - 1, A.columns - 1, &result);

  int i_new = 0;
  int j_new = 0;

  for (int i = 0; i < A.rows; i++) {
    if (i == row) continue;
    j_new = 0;
    for (int j = 0; j < A.columns; j++) {
      if (j == column) continue;
      result.matrix[i_new][j_new++] = A.matrix[i][j];
    }
    i_new++;
  }

  return result;
}

void s21_print_matrix(matrix_t* A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      printf("%.8f ", A->matrix[i][j]);
    }
    printf("\n");
  }
}

bool s21_is_valid_matrix(const matrix_t* A) {
  return A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0;
}

int s21_get_minor(matrix_t* A, int row, int column, matrix_t* result) {
  int status = OK;
  if (A == NULL || !s21_is_valid_matrix(A)) return INCORRECT_MATRIX;

  if (A == result || result == NULL || row < 0 || row > (A->rows - 1) ||
      column < 0 || column > (A->columns - 1))
    return CALCULATION_ERROR;

  status = s21_create_matrix(A->rows - 1, A->columns - 1, result);

  if (status == OK) {
    int i = 0, j = 0;
    for (int k = 0; k < A->rows; ++k) {
      if (k == row) continue;
      for (int l = 0; l < A->columns; ++l) {
        if (l == column) continue;
        result->matrix[i][j] = A->matrix[k][l];
        j++;
      }
      i++;
      j = 0;
    }
  }

  if (status != OK) s21_remove_matrix(result);

  return status;
}