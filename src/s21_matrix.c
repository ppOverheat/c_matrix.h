#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = (rows < 1 || columns < 1) ? INCORRECT_MATRIX : OK;
  result->columns = columns;
  result->rows = rows;
  if (res == OK) {
    result->matrix =
        malloc(rows * columns * sizeof(double) + rows * sizeof(double *));
    double *p_matrix = (double *)(rows + result->matrix);
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = p_matrix + columns * i;
    }
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
  } else {
    result->matrix = NULL;
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    free(A->matrix);
    A->matrix = NULL;
  }
  if (A != NULL) free(A);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result =
      (A->columns != B->columns || A->rows != B->rows) ? FAILURE : SUCCESS;
  if (result == SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double diff = fabs(A->matrix[i][j] - B->matrix[i][j]);
        if (diff > EPS) result = FAILURE;
      }
    }
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res =
      (A->columns != B->columns || A->rows != B->rows) ? CALCULATION_ERROR : OK;
  int init_res = s21_create_matrix(A->rows, A->columns, result);
  if (res == OK) res = init_res;
  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res =
      (A->columns != B->columns || A->rows != B->rows) ? CALCULATION_ERROR : OK;
  int init_res = s21_create_matrix(A->rows, A->columns, result);
  if (res == OK) res = init_res;
  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}

void mult_num(matrix_t *A, double number, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = number * A->matrix[i][j];
    }
  }
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = s21_create_matrix(A->rows, A->columns, result);
  if (res == OK) {
    mult_num(A, number, result);
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = (A->columns != B->rows) ? CALCULATION_ERROR : OK;
  if (A->columns < 1 || A->rows < 1 || B->columns < 1 || B->rows < 1) {
    res = INCORRECT_MATRIX;
  }
  int init_res = s21_create_matrix(A->rows, B->columns, result);
  if (res == OK) res = init_res;
  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int k = 0; k < B->columns; k++) {
        double sum = 0;
        for (int j = 0; j < A->columns; j++) {
          sum += A->matrix[i][j] * B->matrix[j][k];
        }
        result->matrix[i][k] = sum;
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = s21_create_matrix(A->columns, A->rows, result);
  if (res == OK) {
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = (A->rows != A->columns) ? CALCULATION_ERROR : OK;
  int init_res = s21_create_matrix(A->columns, A->rows, result);
  int row = A->rows, col = A->columns;
  if (res == OK) res = init_res;
  if (res == OK) {
    int flag = -1;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t *temp = (matrix_t *)malloc(sizeof(matrix_t));
        if (A->columns > 1) {
          row = A->rows - 1;
          col = A->columns - 1;
        }
        s21_create_matrix(row, col, temp);
        int n = 0, m = 0;
        for (int l = 0; l < A->rows; l++) {
          if (m == temp->columns - 1) m = 0;
          for (int k = 0; k < A->columns; k++) {
            if (k != j && l != i) temp->matrix[n][m++] = A->matrix[l][k];
          }
          if (n > temp->rows - 1 && m == temp->columns - 1) n++;
        }
        double r = 0;
        res = s21_determinant(temp, &r);
        result->matrix[i][j] = pow(flag, i + j) * r;
        s21_remove_matrix(temp);
      }
    }
    if (A->columns == 1) {
      result->matrix[0][0] = 1;
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = (A->rows != A->columns) ? CALCULATION_ERROR : OK;
  if (A->rows < 1 || A->columns < 1) res = INCORRECT_MATRIX;
  if (res == OK) {
    *result = s21_get_det(A);
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = (A->rows != A->columns) ? CALCULATION_ERROR : OK;
  int init_res = s21_create_matrix(A->columns, A->rows, result);
  if (res == OK) res = init_res;
  if (res == OK) {
    double det = -1;
    res = s21_determinant(A, &det);
    if (det == 0) res = CALCULATION_ERROR;
    if (res == OK) {
      matrix_t *temp = (matrix_t *)malloc(sizeof(matrix_t));
      res = s21_calc_complements(A, temp);
      if (res == OK) {
        matrix_t *transposed = (matrix_t *)malloc(sizeof(matrix_t));
        res = s21_transpose(temp, transposed);
        if (res == OK) {
          mult_num(transposed, (1 / det), result);
        }
        s21_remove_matrix(transposed);
      }
      s21_remove_matrix(temp);
    }
  }
  return res;
}

double s21_get_det(matrix_t *A) {
  double result = 0;
  if (A->rows > 2) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t *temp = (matrix_t *)malloc(sizeof(matrix_t));
      s21_create_matrix(A->rows - 1, A->columns - 1, temp);
      int n = 0;
      for (int i = 1; i < A->rows; i++) {
        int m = 0;
        for (int k = 0; k < A->columns; k++) {
          if (k != j) temp->matrix[n][m++] = A->matrix[i][k];
        }
        n++;
      }
      result += pow(-1, 0 + j) * A->matrix[0][j] * s21_get_det(temp);
      s21_remove_matrix(temp);
    }
  } else if (A->rows == 2) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    result = A->matrix[0][0];
  }
  return result;
}
