#include <gtest/gtest.h>

#include "../matrix.h"

TEST(sum, common) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 5;
  matrix2(0, 1) = 6;
  matrix2(1, 0) = 7;
  matrix2(1, 1) = 8;

  matrix1.SumMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 6);
  EXPECT_EQ(matrix1(0, 1), 8);
  EXPECT_EQ(matrix1(1, 0), 10);
  EXPECT_EQ(matrix1(1, 1), 12);
}

TEST(sum, diff_size) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(3, 3);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), const char*);
}

TEST(sum, to_zero) {
  S21Matrix matrix1(2, 2), matrix2(2, 2), matrix3(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = -1;
  matrix2(0, 1) = -2;
  matrix2(1, 0) = -3;
  matrix2(1, 1) = -4;

  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(matrix1.EqMatrix(matrix3), true);
}

TEST(sum, empty) {
  S21Matrix matrix1, matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  EXPECT_THROW(matrix1.SumMatrix(matrix2), const char*);
}

TEST(equal, empty) {
  S21Matrix matrix1, matrix2;
  EXPECT_THROW(matrix1.EqMatrix(matrix2), const char*);
}

TEST(equal, same) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(equal, diff_size) {
  S21Matrix matrix1(2, 2), matrix2(3, 3);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(equal, diff) {
  S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(matrix1);
  matrix2(1, 1) = 5;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(equal, one_empty) {
  S21Matrix matrix1, matrix2(2, 2);
  EXPECT_THROW(matrix1.EqMatrix(matrix2), const char*);
}

TEST(mul_number, null_exception) {
  S21Matrix matrix;
  EXPECT_THROW(matrix.MulNumber(5), const char*);
}

TEST(mul_number, common) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  matrix.MulNumber(2);

  EXPECT_EQ(matrix(0, 0), 2);
  EXPECT_EQ(matrix(0, 1), 4);
  EXPECT_EQ(matrix(1, 0), 6);
  EXPECT_EQ(matrix(1, 1), 8);
}

TEST(mul_number, neg_mul_neg) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = -1;
  matrix(0, 1) = -2;
  matrix(1, 0) = -3;
  matrix(1, 1) = -4;

  matrix.MulNumber(-3);
  EXPECT_EQ(matrix(0, 0), 3);
  EXPECT_EQ(matrix(0, 1), 6);
  EXPECT_EQ(matrix(1, 0), 9);
  EXPECT_EQ(matrix(1, 1), 12);
}

TEST(mul_number, zero_matrix) {
  S21Matrix matrix(3, 3), matrix2(3, 3);
  matrix.MulNumber(10);
  EXPECT_EQ(matrix.EqMatrix(matrix2), true);
}

TEST(mul_number, mul_zero) {
  S21Matrix matrix(2, 2), matrix2(2, 2);

  matrix(0, 0) = 5;
  matrix(0, 1) = 6;
  matrix(1, 0) = 7;
  matrix(1, 1) = 8;

  matrix.MulNumber(0);
  EXPECT_EQ(matrix.EqMatrix(matrix2), true);
}

TEST(mul_number, mul_1) {
  S21Matrix matrix(2, 3);

  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  S21Matrix matrix2(matrix);
  matrix.MulNumber(1);

  EXPECT_EQ(matrix.EqMatrix(matrix2), true);
}

TEST(mul_matrix, both_empty) {
  S21Matrix matrix1, matrix2;
  EXPECT_THROW(matrix1.MulMatrix(matrix2), const char*);
}

TEST(mul_matrix, 1st_empty) {
  S21Matrix matrix1, matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  EXPECT_THROW(matrix1.MulMatrix(matrix2), const char*);
}

TEST(mul_matrix, 2nd_empty) {
  S21Matrix matrix1(2, 2), matrix2;

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;
  EXPECT_THROW(matrix1.MulMatrix(matrix2), const char*);
}

TEST(mul_matrix, wrong_size) {
  S21Matrix matrix1(2, 3), matrix2(4, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 7;
  matrix2(0, 1) = 8;
  matrix2(1, 0) = 9;
  matrix2(1, 1) = 10;
  matrix2(2, 0) = 11;
  matrix2(2, 1) = 12;
  matrix2(3, 0) = 13;
  matrix2(3, 1) = 14;

  EXPECT_THROW(matrix1.MulMatrix(matrix2), const char*);
}

TEST(mul_matrix, common) {
  S21Matrix matrix1(2, 3), matrix2(3, 2);

  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 7;
  matrix2(0, 1) = 8;
  matrix2(1, 0) = 9;
  matrix2(1, 1) = 10;
  matrix2(2, 0) = 11;
  matrix2(2, 1) = 12;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 1 * 7 + 2 * 9 + 3 * 11);
  EXPECT_EQ(matrix1(0, 1), 1 * 8 + 2 * 10 + 3 * 12);
  EXPECT_EQ(matrix1(1, 0), 4 * 7 + 5 * 9 + 6 * 11);
  EXPECT_EQ(matrix1(1, 1), 4 * 8 + 5 * 10 + 6 * 12);
}

TEST(mul_matrix, to_zero) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);  // 2x2 матрица

  matrix1(0, 0) = 0;
  matrix1(0, 1) = 0;
  matrix1(1, 0) = 0;
  matrix1(1, 1) = 1;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  matrix1.MulMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 0);
  EXPECT_EQ(matrix1(0, 1), 0);
  EXPECT_EQ(matrix1(1, 0), 1 * 3);
  EXPECT_EQ(matrix1(1, 1), 1 * 4);
}

TEST(sub, diff_size) {
  S21Matrix matrix1(2, 2), matrix2(1, 1);

  matrix1(0, 0) = 5;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 2;

  matrix2(0, 0) = 1;
  EXPECT_THROW(matrix1.SubMatrix(matrix2), const char*);
}

TEST(sub, both_empty) {
  S21Matrix matrix1, matrix2;
  EXPECT_THROW(matrix1.SubMatrix(matrix2), const char*);
}

TEST(sub, one_empty) {
  S21Matrix matrix1(2, 2), matrix2;

  matrix1(0, 0) = 5;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 2;
  EXPECT_THROW(matrix1.SubMatrix(matrix2), const char*);
}

TEST(sub, common) {
  S21Matrix matrix1(2, 2), matrix2(2, 2);

  matrix1(0, 0) = 5;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 2;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 1;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 1;

  matrix1.SubMatrix(matrix2);

  EXPECT_EQ(matrix1(0, 0), 4);
  EXPECT_EQ(matrix1(0, 1), 2);
  EXPECT_EQ(matrix1(1, 0), 3);
  EXPECT_EQ(matrix1(1, 1), 1);
}

TEST(transpose, empty) {
  S21Matrix matrix;
  EXPECT_THROW(matrix.Transpose(), const char*);
}

TEST(transpose, 1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5;

  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result.GetRows(), 1);
  EXPECT_EQ(result.GetCols(), 1);
  EXPECT_EQ(result(0, 0), 5);
}

TEST(transpose, rectangle) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;

  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 2);
  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 5);
  EXPECT_EQ(result(2, 0), 3);
  EXPECT_EQ(result(2, 1), 6);
}

TEST(transpose, square) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;

  S21Matrix result = matrix.Transpose();

  EXPECT_EQ(result.GetRows(), 3);
  EXPECT_EQ(result.GetCols(), 3);
  EXPECT_EQ(result(0, 0), 1);
  EXPECT_EQ(result(0, 1), 4);
  EXPECT_EQ(result(0, 2), 7);
  EXPECT_EQ(result(1, 0), 2);
  EXPECT_EQ(result(1, 1), 5);
  EXPECT_EQ(result(1, 2), 8);
  EXPECT_EQ(result(2, 0), 3);
  EXPECT_EQ(result(2, 1), 6);
  EXPECT_EQ(result(2, 2), 9);
}

TEST(det, empty) {
  S21Matrix matrix;
  EXPECT_THROW(matrix.Determinant(), const char*);
}

TEST(det, not_square) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  EXPECT_THROW(matrix.Determinant(), const char*);
}

TEST(det, 1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 7.0;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), 7.0);
}

TEST(det, 2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix.Determinant(), 1.0 * 4.0 - 2.0 * 3.0);
}

TEST(det, 3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  double expected = 0.0;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), expected);
}

TEST(det, 4x4) {
  S21Matrix matrix(4, 4);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(0, 3) = 4.0;
  matrix(1, 0) = 5.0;
  matrix(1, 1) = 6.0;
  matrix(1, 2) = 7.0;
  matrix(1, 3) = 8.0;
  matrix(2, 0) = 9.0;
  matrix(2, 1) = 10.0;
  matrix(2, 2) = 11.0;
  matrix(2, 3) = 12.0;
  matrix(3, 0) = 13.0;
  matrix(3, 1) = 14.0;
  matrix(3, 2) = 15.0;
  matrix(3, 3) = 16.0;

  double expected = 0.0;
  EXPECT_DOUBLE_EQ(matrix.Determinant(), expected);
}

TEST(complement, empty) {
  S21Matrix matrix;
  EXPECT_THROW(matrix.CalcComplements(), const char*);
}

TEST(complement, not_square) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.CalcComplements(), const char*);
}

TEST(complement, too_small) {
  S21Matrix matrix(1, 1);
  EXPECT_THROW(matrix.CalcComplements(), const char*);
}

TEST(complement, 2x2) {
  S21Matrix matrix(2, 2), expected(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  expected(0, 0) = 4;
  expected(0, 1) = -3;
  expected(1, 0) = -2;
  expected(1, 1) = 1;

  S21Matrix result = matrix.CalcComplements();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

TEST(complement, 3x3) {
  S21Matrix matrix(3, 3), expected(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 4;
  matrix(1, 2) = 2;
  matrix(2, 0) = 5;
  matrix(2, 1) = 2;
  matrix(2, 2) = 1;

  expected(0, 0) = 0;
  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;

  S21Matrix result = matrix.CalcComplements();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

TEST(complement, zero) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 0;
  matrix(0, 1) = 0;
  matrix(0, 2) = 0;
  matrix(1, 0) = 0;
  matrix(1, 1) = 1;
  matrix(1, 2) = 0;
  matrix(2, 0) = 0;
  matrix(2, 1) = 0;
  matrix(2, 2) = 0;

  S21Matrix expected(matrix);
  expected(1, 1) = 0;

  S21Matrix result = matrix.CalcComplements();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

TEST(inverse, empty) {
  S21Matrix matrix;
  EXPECT_THROW(matrix.InverseMatrix(), const char*);
}

TEST(inverse, not_square) {
  S21Matrix matrix(2, 3);
  EXPECT_THROW(matrix.InverseMatrix(), const char*);
}

TEST(inverse, too_small) {
  S21Matrix matrix(1, 1), expected(1, 1);
  matrix(0, 0) = 2;
  expected(0, 0) = 0.5;
  S21Matrix result = matrix.InverseMatrix();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

TEST(inverse, singular_2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 2;
  matrix(1, 1) = 4;
  EXPECT_THROW(matrix.InverseMatrix(), const char*);
}

TEST(inverse, 2x2) {
  S21Matrix matrix(2, 2), expected(2, 2);
  matrix(0, 0) = 4;
  matrix(0, 1) = 7;
  matrix(1, 0) = 2;
  matrix(1, 1) = 6;

  expected(0, 0) = 0.6;
  expected(0, 1) = -0.7;
  expected(1, 0) = -0.2;
  expected(1, 1) = 0.4;

  S21Matrix result = matrix.InverseMatrix();
  EXPECT_EQ(result.EqMatrix(expected), true);
}

TEST(inverse, singular_3x3) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 4;
  matrix(1, 1) = 5;
  matrix(1, 2) = 6;
  matrix(2, 0) = 7;
  matrix(2, 1) = 8;
  matrix(2, 2) = 9;
  EXPECT_THROW(matrix.InverseMatrix(), const char*);
}

TEST(inverse, 3x3) {
  S21Matrix matrix(3, 3), expected(3, 3);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(0, 2) = 3;
  matrix(1, 0) = 0;
  matrix(1, 1) = 1;
  matrix(1, 2) = 4;
  matrix(2, 0) = 5;
  matrix(2, 1) = 6;
  matrix(2, 2) = 0;

  expected(0, 0) = -24;
  expected(0, 1) = 18;
  expected(0, 2) = 5;
  expected(1, 0) = 20;
  expected(1, 1) = -15;
  expected(1, 2) = -4;
  expected(2, 0) = -5;
  expected(2, 1) = 4;
  expected(2, 2) = 1;

  S21Matrix result = matrix.InverseMatrix();
  EXPECT_EQ(result.EqMatrix(expected), true);
}