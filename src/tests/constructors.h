#include <gtest/gtest.h>

#include "../matrix.h"

TEST(constructor, small_sizes) {
  for (int i = 1; i < 10; i++) {
    S21Matrix a(i, i);
    EXPECT_EQ(i, a.GetCols());
    EXPECT_EQ(i, a.GetRows());
  }
}

TEST(constructor, except_rows) {
  for (int i = -5; i < 0; i++) {
    EXPECT_THROW(S21Matrix a(i, 1), const char*);
  }
}

TEST(constructor, except_cols) {
  for (int i = -5; i < 0; i++) {
    EXPECT_THROW(S21Matrix a(1, i), const char*);
  }
}

TEST(constructor, standart) {
  S21Matrix test;
  EXPECT_EQ(test.GetRows(), 0);
  EXPECT_EQ(test.GetCols(), 0);
}

TEST(constructor, copy) {
  S21Matrix orig(2, 3);
  int k = 0;
  for (int i = 0; i < orig.GetRows(); i++) {
    for (int j = 0; j < orig.GetCols(); j++) {
      orig(i, j) = k;
      k++;
    }
  }
  S21Matrix copy(orig);
  EXPECT_EQ(copy.GetRows(), orig.GetRows());
  EXPECT_EQ(copy.GetCols(), orig.GetCols());

  for (int i = 0; i < orig.GetRows(); i++) {
    for (int j = 0; j < orig.GetCols(); j++) {
      EXPECT_EQ(copy(i, j), orig(i, j));
    }
  }
}

TEST(constructor, copy_large) {
  int rows = 100;
  int cols = 100;
  S21Matrix orig(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      orig(i, j) = i * cols + j;
    }
  }

  S21Matrix copy(orig);

  EXPECT_EQ(copy.GetRows(), orig.GetRows());
  EXPECT_EQ(copy.GetCols(), orig.GetCols());

  for (int i = 0; i < orig.GetRows(); ++i) {
    for (int j = 0; j < orig.GetCols(); ++j) {
      EXPECT_EQ(copy(i, j), orig(i, j));
    }
  }
}

TEST(constructor, move) {
  S21Matrix original(2, 3);
  original(0, 0) = 1;
  original(0, 1) = 2;
  original(0, 2) = 3;
  original(1, 0) = 4;
  original(1, 1) = 5;
  original(1, 2) = 6;

  S21Matrix moved(std::move(original));

  EXPECT_EQ(moved.GetRows(), 2);
  EXPECT_EQ(moved.GetCols(), 3);
  EXPECT_EQ(moved(0, 0), 1);
  EXPECT_EQ(moved(0, 1), 2);
  EXPECT_EQ(moved(0, 2), 3);
  EXPECT_EQ(moved(1, 0), 4);
  EXPECT_EQ(moved(1, 1), 5);
  EXPECT_EQ(moved(1, 2), 6);

  EXPECT_EQ(original.GetRows(), 0);
  EXPECT_EQ(original.GetCols(), 0);
}

TEST(constructor, copy_null) {
  S21Matrix test;
  EXPECT_THROW(S21Matrix copy(test), const char*);
}

TEST(constructor, move_null) {
  S21Matrix test;
  EXPECT_THROW(S21Matrix copy(std::move(test)), const char*);
}

TEST(setters, set_cols_0) {
  S21Matrix test(1, 1);
  EXPECT_THROW(test.SetCols(-1), const char*);
}

TEST(setters, set_rows_0) {
  S21Matrix test(1, 1);
  EXPECT_THROW(test.SetRows(0), const char*);
}

TEST(setters, set_rows_less) {
  S21Matrix matrix1(2, 3), matrix2(1, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;

  matrix1.SetRows(1);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(setters, set_rows_more) {
  S21Matrix matrix1(2, 3), matrix2(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  matrix1.SetRows(3);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(setters, set_cols_less) {
  S21Matrix matrix1(2, 3), matrix2(2, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;

  matrix1.SetCols(2);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(setters, set_cols_more) {
  S21Matrix matrix1(2, 3), matrix2(2, 4);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(1, 0) = 4;
  matrix1(1, 1) = 5;
  matrix1(1, 2) = 6;

  matrix2(0, 0) = 1;
  matrix2(0, 1) = 2;
  matrix2(0, 2) = 3;
  matrix2(1, 0) = 4;
  matrix2(1, 1) = 5;
  matrix2(1, 2) = 6;

  matrix1.SetCols(4);
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(copy, invalid) {
  S21Matrix matrix4;
  S21Matrix matrix1;
  EXPECT_THROW(matrix1.Copy(matrix4), const char*);
}

TEST(copy, selfcopy) {
  S21Matrix matrix1(3, 3);
  EXPECT_NO_THROW(matrix1.Copy(matrix1));
}