#include "test.h"

void fill_matrix(matrix_t* result, struct struct_matrix* values) {
  int n = 0;
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = values[n++].value;
    }
  }
  printf("\n");
}

START_TEST(create_m_test) {
  matrix_t* result = (matrix_t*)malloc(sizeof(matrix_t));
  int res_1 = s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1,
                                result);
  int res_2 = (test_cases[_i].rows_1 < 1 || test_cases[_i].columns_1 < 1)
                  ? INCORRECT_MATRIX
                  : OK;
  ck_assert_int_eq(test_cases[_i].rows_1, result->rows);
  ck_assert_int_eq(test_cases[_i].columns_1, result->columns);
  ck_assert_int_eq(res_1, res_2);
  s21_remove_matrix(result);
}
END_TEST

Suite* create_matrix_suite() {
  Suite* suite = suite_create("s21_create_matrix_test_suite");
  TCase* tc = tcase_create("create_m_tc");
  tcase_add_loop_test(tc, create_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

START_TEST(eq_m_test_success) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* B = (matrix_t*)malloc(sizeof(matrix_t));
  int init_1 =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  int init_2 =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, B);
  fill_matrix(A, test_cases[_i].values_1);
  fill_matrix(B, test_cases[_i].values_1);
  int res_1 = SUCCESS, res_2 = SUCCESS;
  if (init_1 == OK && init_2 == OK) {
    res_1 = s21_eq_matrix(A, B);
  }
  ck_assert_int_eq(res_1, res_2);
  s21_remove_matrix(A);
  s21_remove_matrix(B);
}
END_TEST

START_TEST(eq_m_test_fail) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* B = (matrix_t*)malloc(sizeof(matrix_t));
  int init_1 =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  int init_2 = s21_create_matrix(test_cases[_i - 1].rows_1,
                                 test_cases[_i - 1].columns_1, B);
  fill_matrix(A, test_cases[_i].values_1);
  fill_matrix(B, test_cases[_i - 1].values_1);
  int res_1 = FAILURE, res_2 = FAILURE;
  if (init_1 == OK && init_2 == OK) {
    res_1 = s21_eq_matrix(A, B);
  }
  ck_assert_int_eq(res_1, res_2);
  s21_remove_matrix(A);
  s21_remove_matrix(B);
}
END_TEST

Suite* eq_matrix_suite() {
  Suite* suite = suite_create("s21_eq_matrix_test_suite");
  TCase* tc = tcase_create("eq_m_success_tc");
  tcase_add_loop_test(tc, eq_m_test_success, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  if (TC_SIZE > 1) {
    TCase* tc1 = tcase_create("eq_m_fail_tc");
    tcase_add_loop_test(tc1, eq_m_test_fail, 1, TC_SIZE);
    tcase_set_timeout(tc1, 10);
    suite_add_tcase(suite, tc1);
  }
  return suite;
}

START_TEST(sum_m_test) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* B = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* result = (matrix_t*)malloc(sizeof(matrix_t));
  int init_1 =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  fill_matrix(A, test_cases[_i].values_1);
  s21_create_matrix(test_cases[_i].rows_2, test_cases[_i].columns_2, B);
  fill_matrix(B, test_cases[_i].values_2);
  int res_1 = s21_sum_matrix(A, B, result);
  int res_2 =
      (A->columns != B->columns || A->rows != B->rows) ? CALCULATION_ERROR : OK;
  if (init_1 != OK) {
    res_2 = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res_1, res_2);
  if (res_2 == OK) {
    ck_assert_int_eq(A->rows, result->rows);
    ck_assert_int_eq(A->columns, result->columns);
    int n = 0;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        ck_assert_double_eq_tol(test_cases[_i].sum[n++].value,
                                result->matrix[i][j], EPS);
      }
    }
  }
  s21_remove_matrix(A);
  s21_remove_matrix(B);
  s21_remove_matrix(result);
}
END_TEST

Suite* sum_matrix_suite() {
  Suite* suite = suite_create("s21_sum_matrix_test_suite");
  TCase* tc = tcase_create("sum_m_tc");
  tcase_add_loop_test(tc, sum_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

START_TEST(sub_m_test) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* B = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* result = (matrix_t*)malloc(sizeof(matrix_t));
  int init_1 =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  fill_matrix(A, test_cases[_i].values_1);
  s21_create_matrix(test_cases[_i].rows_2, test_cases[_i].columns_2, B);
  fill_matrix(B, test_cases[_i].values_2);
  int res_1 = s21_sub_matrix(A, B, result);
  int res_2 =
      (A->columns != B->columns || A->rows != B->rows) ? CALCULATION_ERROR : OK;
  if (init_1 != OK) {
    res_2 = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res_1, res_2);
  if (res_2 == OK) {
    ck_assert_int_eq(A->rows, result->rows);
    ck_assert_int_eq(A->columns, result->columns);
    int n = 0;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        ck_assert_double_eq_tol(test_cases[_i].sub[n++].value,
                                result->matrix[i][j], EPS);
      }
    }
  }
  s21_remove_matrix(A);
  s21_remove_matrix(B);
  s21_remove_matrix(result);
}
END_TEST

Suite* sub_matrix_suite() {
  Suite* suite = suite_create("s21_sub_matrix_test_suite");
  TCase* tc = tcase_create("sub_m_tc");
  tcase_add_loop_test(tc, sub_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

START_TEST(mul_m_test) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* B = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* result = (matrix_t*)malloc(sizeof(matrix_t));
  int init_1 =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  fill_matrix(A, test_cases[_i].values_1);
  int init_2 =
      s21_create_matrix(test_cases[_i].rows_2, test_cases[_i].columns_2, B);
  fill_matrix(B, test_cases[_i].values_2);
  int res_1 = s21_mult_matrix(A, B, result);
  int res_2 = (A->columns != B->rows) ? CALCULATION_ERROR : OK;
  if (init_1 != OK || init_2 != OK) {
    res_2 = INCORRECT_MATRIX;
  }
  ck_assert_int_eq(res_1, res_2);
  if (res_2 == OK) {
    ck_assert_int_eq(test_cases[_i].rows_mul, result->rows);
    ck_assert_int_eq(test_cases[_i].columns_mul, result->columns);
    int n = 0;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        ck_assert_double_eq_tol(test_cases[_i].mul[n++].value,
                                result->matrix[i][j], EPS);
      }
    }
  }
  s21_remove_matrix(A);
  s21_remove_matrix(B);
  s21_remove_matrix(result);
}
END_TEST

Suite* mul_matrix_suite() {
  Suite* suite = suite_create("s21_mul_matrix_test_suite");
  TCase* tc = tcase_create("mul_m_tc");
  tcase_add_loop_test(tc, mul_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

START_TEST(mul_num_m_test) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* result = (matrix_t*)malloc(sizeof(matrix_t));
  int init =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  fill_matrix(A, test_cases[_i].values_1);
  int res_1 = s21_mult_number(A, test_cases[_i].mul_num, result);
  int res_2 = init;
  ck_assert_int_eq(res_1, res_2);
  if (res_2 == OK) {
    ck_assert_int_eq(A->rows, result->rows);
    ck_assert_int_eq(A->columns, result->columns);
    int n = 0;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        ck_assert_double_eq_tol(test_cases[_i].mul_num_m[n++].value,
                                result->matrix[i][j], EPS);
      }
    }
  }
  s21_remove_matrix(A);
  s21_remove_matrix(result);
}
END_TEST

Suite* mul_num_matrix_suite() {
  Suite* suite = suite_create("s21_mul_num_matrix_test_suite");
  TCase* tc = tcase_create("mul_num_m_tc");
  tcase_add_loop_test(tc, mul_num_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

START_TEST(tr_m_test) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* result = (matrix_t*)malloc(sizeof(matrix_t));
  int init =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  fill_matrix(A, test_cases[_i].values_1);
  int res_1 = s21_transpose(A, result);
  int res_2 = init;
  ck_assert_int_eq(res_1, res_2);
  if (res_2 == OK) {
    ck_assert_int_eq(test_cases[_i].rows_tr, result->rows);
    ck_assert_int_eq(test_cases[_i].columns_tr, result->columns);
    int n = 0;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        ck_assert_double_eq_tol(test_cases[_i].tran[n++].value,
                                result->matrix[i][j], EPS);
      }
    }
  }
  s21_remove_matrix(A);
  s21_remove_matrix(result);
}
END_TEST

Suite* tr_matrix_suite() {
  Suite* suite = suite_create("s21_tr_matrix_test_suite");
  TCase* tc = tcase_create("tr_m_tc");
  tcase_add_loop_test(tc, tr_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

START_TEST(det_m_test) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  int init =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  fill_matrix(A, test_cases[_i].values_1);
  double result = 0;
  int res_1 = s21_determinant(A, &result);
  int res_2 = (A->rows != A->columns) ? CALCULATION_ERROR : OK;
  if (res_2 == OK) res_2 = init;
  ck_assert_int_eq(res_1, res_2);
  if (res_2 == OK) ck_assert_double_eq_tol(test_cases[_i].det, result, EPS);
  s21_remove_matrix(A);
}
END_TEST

Suite* det_matrix_suite() {
  Suite* suite = suite_create("s21_det_matrix_test_suite");
  TCase* tc = tcase_create("det_m_tc");
  tcase_add_loop_test(tc, det_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

START_TEST(compl_m_test) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* result = (matrix_t*)malloc(sizeof(matrix_t));
  int init =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  fill_matrix(A, test_cases[_i].values_1);
  int res_1 = s21_calc_complements(A, result);
  int res_2 = (A->rows != A->columns) ? CALCULATION_ERROR : OK;
  if (res_2 == OK) res_2 = init;
  ck_assert_int_eq(res_1, res_2);
  if (res_2 == OK) {
    ck_assert_int_eq(A->rows, result->rows);
    ck_assert_int_eq(A->columns, result->columns);
    int n = 0;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        ck_assert_double_eq_tol(test_cases[_i].complements[n++].value,
                                result->matrix[i][j], EPS);
      }
    }
  }
  s21_remove_matrix(A);
  s21_remove_matrix(result);
}
END_TEST

Suite* compl_matrix_suite() {
  Suite* suite = suite_create("s21_compl_matrix_test_suite");
  TCase* tc = tcase_create("compl_m_tc");
  tcase_add_loop_test(tc, compl_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

START_TEST(inv_m_test) {
  matrix_t* A = (matrix_t*)malloc(sizeof(matrix_t));
  matrix_t* result = (matrix_t*)malloc(sizeof(matrix_t));
  int init =
      s21_create_matrix(test_cases[_i].rows_1, test_cases[_i].columns_1, A);
  fill_matrix(A, test_cases[_i].values_1);
  int res_1 = s21_inverse_matrix(A, result);
  int res_2 = (A->rows != A->columns || test_cases[_i].det == 0)
                  ? CALCULATION_ERROR
                  : OK;
  if (init != OK) res_2 = init;
  ck_assert_int_eq(res_1, res_2);
  if (res_2 == OK) {
    ck_assert_int_eq(A->rows, result->rows);
    ck_assert_int_eq(A->columns, result->columns);
    int n = 0;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        ck_assert_double_eq_tol(test_cases[_i].inverse[n++].value,
                                result->matrix[i][j], EPS);
      }
    }
  }
  s21_remove_matrix(A);
  s21_remove_matrix(result);
}
END_TEST

Suite* inv_matrix_suite() {
  Suite* suite = suite_create("s21_inv_matrix_test_suite");
  TCase* tc = tcase_create("inv_m_tc");
  tcase_add_loop_test(tc, inv_m_test, 0, TC_SIZE);
  tcase_set_timeout(tc, 10);
  suite_add_tcase(suite, tc);
  return suite;
}

int main(void) {
  Suite* create_m_suite = create_matrix_suite();
  Suite* eq_m_suite = eq_matrix_suite();
  Suite* sum_m_suite = sum_matrix_suite();
  Suite* sub_m_suite = sub_matrix_suite();
  Suite* mul_num_m_suite = mul_num_matrix_suite();
  Suite* mul_m_suite = mul_matrix_suite();
  Suite* tr_m_suite = tr_matrix_suite();
  Suite* det_m_suite = det_matrix_suite();
  Suite* com_m_suite = compl_matrix_suite();
  Suite* inv_m_suite = inv_matrix_suite();
  SRunner* suite_runner = srunner_create(create_m_suite);
  srunner_add_suite(suite_runner, eq_m_suite);
  srunner_add_suite(suite_runner, sum_m_suite);
  srunner_add_suite(suite_runner, sub_m_suite);
  srunner_add_suite(suite_runner, mul_num_m_suite);
  srunner_add_suite(suite_runner, mul_m_suite);
  srunner_add_suite(suite_runner, tr_m_suite);
  srunner_add_suite(suite_runner, det_m_suite);
  srunner_add_suite(suite_runner, com_m_suite);
  srunner_add_suite(suite_runner, inv_m_suite);
  srunner_set_fork_status(suite_runner, CK_NOFORK);
  srunner_set_xml(suite_runner, "log.xml");
  srunner_run_all(suite_runner, CK_NORMAL);
  srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  return EXIT_SUCCESS;
}
