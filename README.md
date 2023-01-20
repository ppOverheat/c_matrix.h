# s21_matrix.h
Implementation of the matrix.h library. 

The static library is assembled using a Makefile. The name of the build stage is all.

Command ``` make test ``` runs unit-tests and ```make gcov_report``` makes html-report that shows the coverage of unit-testing.
## Functions
All operations (except matrix comparison) return the resulting code:
- 0 - OK
- 1 - Error, incorrect matrix
- 2 - Calculation error (mismatched matrix sizes; matrix for which calculations cannot be performed, etc.)
__________________
#### Creating matrix
```
int s21_create_matrix(int rows, int columns, matrix_t *result);
```
#### Cleaning of matrices
```
void s21_remove_matrix(matrix_t *A);
```
#### Matrix comparison
```
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```
#### Adding and subtracting matrices
```
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```
#### Matrix multiplication by scalar. Multiplication of two matrices
```
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```
#### Matrix transpose
```
int s21_transpose(matrix_t *A, matrix_t *result);
```
#### Matrix of algebraic complements
```
int s21_calc_complements(matrix_t *A, matrix_t *result);
```
#### Matrix determinant
```
int s21_determinant(matrix_t *A, double *result);
```
#### Inverse of the matrix
```
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```
## Important notes:

- Prepared full coverage of library functions code with unit-tests using the Check library.
- Unit tests cover 100% of each function (checked using gcov).
- The library was developed in C language of C11 standard using gcc compiler.
- The source code folows the Google style.
> The library was written according to the principles of structured programming E. Dijkstra.
