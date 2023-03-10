#ifndef SRC_TEST_H_
#define SRC_TEST_H_

#include <check.h>

#include "s21_matrix.h"

#define TC_SIZE 8
#define VALUES_SIZE 1010

struct struct_matrix {
  double value;
};

struct tc_struct {
  int rows_1;
  int columns_1;
  struct struct_matrix values_1[VALUES_SIZE];
  int rows_2;
  int columns_2;
  struct struct_matrix values_2[VALUES_SIZE];
  struct struct_matrix sum[VALUES_SIZE];
  struct struct_matrix sub[VALUES_SIZE];
  int rows_mul;
  int columns_mul;
  struct struct_matrix mul[VALUES_SIZE];
  double mul_num;
  struct struct_matrix mul_num_m[VALUES_SIZE];
  int rows_tr;
  int columns_tr;
  struct struct_matrix tran[VALUES_SIZE];
  double det;
  struct struct_matrix complements[VALUES_SIZE];
  struct struct_matrix inverse[VALUES_SIZE];
};

struct tc_struct test_cases[TC_SIZE] = {
    {3,
     3,
     {{1.0}, {2.0}, {3}, {4}, {5}, {6}, {7}, {8}, {9}},
     3,
     3,
     {{1.0}, {2.0}, {3}, {4}, {5}, {6}, {7}, {8}, {9}},
     {{2.0}, {4.0}, {6}, {8}, {10}, {12}, {14}, {16}, {18}},
     {{0.0}, {0.0}, {0.0}, {0}, {0}, {0}, {0}, {0}, {0}},
     3,
     3,
     {{30}, {36}, {42}, {66}, {81}, {96}, {102}, {126}, {150}},
     2.0,
     {{2.0}, {4.0}, {6}, {8}, {10}, {12}, {14}, {16}, {18}},
     3,
     3,
     {{1.0}, {4.0}, {7}, {2}, {5}, {8}, {3}, {6}, {9}},
     0,
     {{-3}, {6}, {-3}, {6}, {-12}, {6}, {-3}, {6}, {-3}},
     {{0}}},
    {2,
     3,
     {{1.0}, {2.0}, {3.0}, {4}, {5}, {6}},
     3,
     2,
     {{-1.0}, {-2.0}, {-3}, {-4}, {-5}, {-6}},
     {{0}},
     {{0}},
     2,
     2,
     {{-22}, {-28}, {-49}, {-64}},
     0.5,
     {{0.5}, {1}, {1.5}, {2}, {2.5}, {3}},
     3,
     2,
     {{1.0}, {4.0}, {2.0}, {5}, {3}, {6}},
     0,
     {{0}},
     {{0}}},
    {2,
     2,
     {{1}, {2}, {3}, {4}},
     2,
     2,
     {{0.5}, {0.4}, {0.123456}, {1.2}},
     {{1.5}, {2.4}, {3.123456}, {5.2}},
     {{0.5}, {1.6}, {2.876544}, {2.8}},
     2,
     2,
     {{0.746912}, {2.8}, {1.993824}, {6}},
     2,
     {{2}, {4}, {6}, {8}},
     2,
     2,
     {{1}, {3}, {2}, {4}},
     -2.0,
     {{4}, {-3}, {-2}, {1}},
     {{-2}, {1}, {1.5}, {-0.5}}},
    {0,
     0,
     {{1}, {2}, {3}, {4}},
     0,
     0,
     {{2}, {3}, {4}, {5}},
     {{0}},
     {{0}},
     0,
     0,
     {{0}},
     0,
     {{0}},
     0,
     0,
     {{0}},
     0,
     {{0}},
     {{0}}},
    {1,
     1,
     {{10}},
     1,
     1,
     {{0.5}},
     {{10.5}},
     {{9.5}},
     1,
     1,
     {{5}},
     2.0,
     {{20}},
     1,
     1,
     {{10}},
     10.0,
     {{1}},
     {{0.1}}},
    {4,
     4,
     {{1},
      {0},
      {0},
      {0},
      {0},
      {1},
      {0},
      {0},
      {0},
      {0},
      {1},
      {0},
      {0},
      {0},
      {0},
      {1}},
     4,
     1,
     {{1}, {8}, {3}, {4}},
     {{0}},
     {{0}},
     4,
     1,
     {{1}, {8}, {3}, {4}},
     0.01,
     {{0.01},
      {0},
      {0},
      {0},
      {0},
      {0.01},
      {0},
      {0},
      {0},
      {0},
      {0.01},
      {0},
      {0},
      {0},
      {0},
      {0.01}},
     4,
     4,
     {{1},
      {0},
      {0},
      {0},
      {0},
      {1},
      {0},
      {0},
      {0},
      {0},
      {1},
      {0},
      {0},
      {0},
      {0},
      {1}},
     1.0,
     {{1},
      {0},
      {0},
      {0},
      {0},
      {1},
      {0},
      {0},
      {0},
      {0},
      {1},
      {0},
      {0},
      {0},
      {0},
      {1}},
     {{1},
      {0},
      {0},
      {0},
      {0},
      {1},
      {0},
      {0},
      {0},
      {0},
      {1},
      {0},
      {0},
      {0},
      {0},
      {1}}},
    {2,
     1,
     {{5.456781}, {6.999998}},
     1,
     0,
     {{0}},
     {{0}},
     {{0}},
     0,
     0,
     {{0}},
     -2.1234,
     {{-11.5869287754}, {-14.8637957532}},
     1,
     2,
     {{5.456781}, {6.999998}},
     0,
     {{0}},
     {{0}}},
    {5,
     5,
     {{-2}, {0}, {0},  {0}, {0}, {0}, {3}, {0}, {0}, {0}, {0}, {0}, {-6},
      {0},  {0}, {-8}, {0}, {0}, {5}, {0}, {0}, {0}, {0}, {0}, {1}},
     5,
     2,
     {{1}, {2}, {8}, {7}, {3}, {0}, {4}, {0}, {0}, {0}},
     {{0}},
     {{0}},
     5,
     2,
     {{-2}, {-4}, {24}, {21}, {-18}, {0}, {12}, {-16}, {0}, {0}},
     -5.69,
     {{11.38},  {0}, {0}, {0},     {0}, {0}, {-17.07}, {0}, {0},
      {0},      {0}, {0}, {34.14}, {0}, {0}, {45.52},  {0}, {0},
      {-28.45}, {0}, {0}, {0},     {0}, {0}, {-5.69}},
     5,
     5,
     {{-2}, {0}, {0}, {-8}, {0}, {0}, {3}, {0}, {0}, {0}, {0}, {0}, {-6},
      {0},  {0}, {0}, {0},  {0}, {5}, {0}, {0}, {0}, {0}, {0}, {1}},
     180.0,
     {{-90}, {0}, {0}, {-144}, {0}, {0},  {60}, {0}, {0}, {0}, {0}, {0},  {-30},
      {0},   {0}, {0}, {0},    {0}, {36}, {0},  {0}, {0}, {0}, {0}, {180}},
     {{-0.5}, {0}, {0}, {0},           {0}, {0}, {0.3333333}, {0}, {0},
      {0},    {0}, {0}, {-0.16666666}, {0}, {0}, {-0.8},      {0}, {0},
      {0.2},  {0}, {0}, {0},           {0}, {0}, {1}}}};

#endif  // SRC_TEST_H_
