#include <gtest/gtest.h>

#include "../matrix.h"

TEST(plus, empty) {
  S21Matrix matrix1, matrix2;
  EXPECT_THROW(matrix1 + matrix2, const char*);
  EXPECT_THROW(matrix1 += matrix2, const char*);
}

TEST(plus, AddMatricesOfDifferentSizes) {
  S21Matrix matrix1(2, 2), matrix2(3, 3);
  EXPECT_THROW(matrix1 + matrix2, const char*);
  EXPECT_THROW(matrix1 += matrix2, const char*);
}

TEST(plus, 1x1) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 1;
  S21Matrix matrix2(matrix1), expected(1, 1);
  expected(0, 0) = 2;

  S21Matrix result;
  result = matrix1 + matrix2;
  EXPECT_EQ(result == expected, true);
  matrix1 += matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(plus, 2x2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 4;
  matrix2(0, 1) = 3;
  matrix2(1, 0) = 2;
  matrix2(1, 1) = 1;

  S21Matrix expected(2, 2);
  expected(0, 0) = 5;
  expected(0, 1) = 5;
  expected(1, 0) = 5;
  expected(1, 1) = 5;

  S21Matrix result;
  result = matrix1 + matrix2;
  EXPECT_EQ(result == expected, true);

  matrix1 += matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(plus, 3x3) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 9;
  matrix2(0, 1) = 8;
  matrix2(0, 2) = 7;
  matrix2(1, 0) = 6;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 4;
  matrix2(2, 0) = 3;
  matrix2(2, 1) = 2;
  matrix2(2, 2) = 1;

  S21Matrix expected(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      expected(i, j) = 10;
    }
  }

  S21Matrix result;
  result = matrix1 + matrix2;
  EXPECT_EQ(result == expected, true);

  matrix1 += matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(plus, add_zero) {
  S21Matrix matrix1(3, 3), matrix2(3, 3);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;
  matrix2(2, 0) = 7;
  matrix2(2, 1) = 8;
  matrix2(2, 2) = 9;

  S21Matrix expected(matrix2);

  S21Matrix result;
  result = matrix1 + matrix2;
  EXPECT_EQ(result == expected, true);

  matrix1 += matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(minus, SubtractMatricesOfDifferentSizes) {
  S21Matrix matrix1(2, 2), matrix2(3, 3);
  EXPECT_THROW(matrix1 - matrix2, const char*);
  EXPECT_THROW(matrix1 -= matrix2, const char*);
}

TEST(minus, 1x1) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 1;
  S21Matrix matrix2(matrix1);
  S21Matrix expected(1, 1);
  expected(0, 0) = 0;

  S21Matrix result;
  result = matrix1 - matrix2;
  EXPECT_EQ(result(0, 0), expected(0, 0));

  matrix1 -= matrix2;
  EXPECT_EQ(matrix1(0, 0), expected(0, 0));
}

TEST(minus, 2x2) {
  S21Matrix matrix1(2, 2), matrix2(2, 2), expected(2, 2);
  matrix1(0, 0) = 5;
  matrix1(0, 1) = 6;
  matrix1(1, 0) = 7;
  matrix1(1, 1) = 8;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;

  expected(0, 0) = 4;
  expected(0, 1) = 4;
  expected(1, 0) = 4;
  expected(1, 1) = 4;

  S21Matrix result;
  result = matrix1 - matrix2;
  EXPECT_EQ(result == expected, true);

  matrix1 -= matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(minus, 3x3) {
  S21Matrix matrix1(3, 3), matrix2(3, 3), expected(3, 3);
  matrix1(0, 0) = 9;
  matrix1(0, 1) = 8;
  matrix1(0, 2) = 7;
  matrix1(1, 0) = 6;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 4;
  matrix1(2, 0) = 3;
  matrix1(2, 1) = 2;
  matrix1(2, 2) = 1;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;
  matrix2(2, 0) = 7;
  matrix2(2, 1) = 8;
  matrix2(2, 2) = 9;

  expected(0, 0) = 8;
  expected(0, 1) = 6;
  expected(0, 2) = 4;
  expected(1, 0) = 2;
  expected(1, 1) = 0;
  expected(1, 2) = -2;
  expected(2, 0) = -4;
  expected(2, 1) = -6;
  expected(2, 2) = -8;

  S21Matrix result;
  result = matrix1 - matrix2;
  EXPECT_EQ(result == expected, true);

  matrix1 -= matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(minus, good_empty) {
  S21Matrix matrix1(3, 3), matrix2;
  EXPECT_THROW(matrix1 - matrix2, const char*);
  EXPECT_THROW(matrix1 -= matrix2, const char*);
}

TEST(minus, empty_good) {
  S21Matrix matrix1, matrix2(3, 3);
  EXPECT_THROW(matrix1 - matrix2, const char*);
  EXPECT_THROW(matrix1 -= matrix2, const char*);
}

TEST(mul_matrix_op, diff_size) {
  S21Matrix matrix1(2, 3), matrix2(4, 2);
  EXPECT_THROW(matrix1 * matrix2, const char*);
  EXPECT_THROW(matrix1 *= matrix2, const char*);
}

TEST(mul_matrix_op, 2x2) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 2;
  matrix2(0, 1) = 0;
  matrix2(1, 0) = 1;
  matrix2(1, 1) = 2;

  S21Matrix expected(2, 2);
  expected(0, 0) = 4;
  expected(0, 1) = 4;
  expected(1, 0) = 10;
  expected(1, 1) = 8;

  S21Matrix result;
  result = matrix1 * matrix2;
  EXPECT_EQ(result == expected, true);

  matrix1 *= matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(mul_matrix_op, common) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  S21Matrix matrix2(3, 2);
  matrix2(0, 0) = 7;
  matrix2(0, 1) = 8;
  matrix2(1, 0) = 9;
  matrix2(1, 1) = 10;
  matrix2(2, 0) = 11;
  matrix2(2, 1) = 12;

  S21Matrix expected(2, 2);
  expected(0, 0) = 58;
  expected(0, 1) = 64;
  expected(1, 0) = 139;
  expected(1, 1) = 154;

  S21Matrix result;
  result = matrix1 * matrix2;
  EXPECT_EQ(result == expected, true);

  matrix1 *= matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(mul_matrix_op, empty_nonempty) {
  S21Matrix matrix1;
  S21Matrix matrix2(2, 2);
  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 3;
  matrix2(1, 1) = 4;
  EXPECT_THROW(matrix1 * matrix2, const char*);
  EXPECT_THROW(matrix1 *= matrix2, const char*);
}

TEST(mul_matrix_op, nonempty_empty) {
  S21Matrix matrix1(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(1, 0) = 3;
  matrix1(1, 1) = 4;

  S21Matrix matrix2;
  EXPECT_THROW(matrix1 * matrix2, const char*);
  EXPECT_THROW(matrix1 *= matrix2, const char*);
}

TEST(mul_matrix_op, 3x3) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;
  matrix1(2, 0) = 7;
  matrix1(2, 1) = 8;
  matrix1(2, 2) = 9;

  S21Matrix matrix2(3, 3);
  matrix2(0, 0) = 9;
  matrix2(0, 1) = 8;
  matrix2(0, 2) = 7;
  matrix2(1, 0) = 6;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 4;
  matrix2(2, 0) = 3;
  matrix2(2, 1) = 2;
  matrix2(2, 2) = 1;

  S21Matrix expected(3, 3);
  expected(0, 0) = 30;
  expected(0, 1) = 24;
  expected(0, 2) = 18;
  expected(1, 0) = 84;
  expected(1, 1) = 69;
  expected(1, 2) = 54;
  expected(2, 0) = 138;
  expected(2, 1) = 114;
  expected(2, 2) = 90;

  S21Matrix result(3, 3);
  result = matrix1 * matrix2;
  EXPECT_EQ(result == expected, true);

  matrix1 *= matrix2;
  EXPECT_EQ(matrix1 == expected, true);
}

TEST(mul_num, empty) {
  S21Matrix matrix;
  double scalar = 5.0;
  EXPECT_THROW(matrix * scalar, const char*);
  EXPECT_THROW(matrix *= scalar, const char*);
}

TEST(mul_num, empty2) {
  S21Matrix matrix;
  EXPECT_THROW(matrix * 5.0, const char*);
}

TEST(mul_num, 2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  double scalar = 2.0;

  S21Matrix expected(2, 2);
  expected(0, 0) = 2;
  expected(0, 1) = 4;
  expected(1, 0) = 6;
  expected(1, 1) = 8;

  S21Matrix result;
  result = matrix * scalar;
  EXPECT_EQ(result == expected, true);

  matrix *= scalar;
  EXPECT_EQ(matrix == expected, true);
}

TEST(mul_num, 2x2second) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;

  double scalar = 2.0;

  S21Matrix expected(2, 2);
  expected(0, 0) = 2;
  expected(0, 1) = 4;
  expected(1, 0) = 6;
  expected(1, 1) = 8;

  S21Matrix result;
  result = scalar * matrix;
  EXPECT_EQ(result == expected, true);
}

TEST(mul_num, 3x3) {
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

  double scalar = 3.0;

  S21Matrix expected(3, 3);
  expected(0, 0) = 3;
  expected(0, 1) = 6;
  expected(0, 2) = 9;
  expected(1, 0) = 12;
  expected(1, 1) = 15;
  expected(1, 2) = 18;
  expected(2, 0) = 21;
  expected(2, 1) = 24;
  expected(2, 2) = 27;

  S21Matrix result;
  result = matrix * scalar;
  EXPECT_EQ(result == expected, true);

  matrix *= scalar;
  EXPECT_EQ(matrix == expected, true);
}

TEST(mul_num, 3x3second) {
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

  double scalar = 3.0;

  S21Matrix expected(3, 3);
  expected(0, 0) = 3;
  expected(0, 1) = 6;
  expected(0, 2) = 9;
  expected(1, 0) = 12;
  expected(1, 1) = 15;
  expected(1, 2) = 18;
  expected(2, 0) = 21;
  expected(2, 1) = 24;
  expected(2, 2) = 27;

  S21Matrix result;
  result = matrix * scalar;
  EXPECT_EQ(result == expected, true);
}

TEST(getter, empty) {
  S21Matrix matrix;
  EXPECT_THROW(matrix(0, 0), const char*);
}

TEST(getter, out_of_range) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 2;
  matrix(1, 0) = 3;
  matrix(1, 1) = 4;
  EXPECT_THROW(matrix(2, 2), const char*);
  EXPECT_THROW(matrix(-3, 0), const char*);
  EXPECT_EQ(matrix(0, 0), 1);
  EXPECT_EQ(matrix(0, 1), 2);
  EXPECT_EQ(matrix(1, 0), 3);
  EXPECT_EQ(matrix(1, 1), 4);
}