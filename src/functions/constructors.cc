#include "../matrix.h"

S21Matrix::S21Matrix(const S21Matrix& other) {
  if (other.matrix_ == nullptr || other.rows_ <= 0 || other.cols_ <= 0)
    throw "Used matrix is not valid";
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  InitMatrix();
  this->Copy(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  if (other.matrix_ == nullptr || other.rows_ <= 0 || other.cols_ <= 0)
    throw "Used matrix is not valid";
  if (this != &other) {
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    InitMatrix();
    this->Copy(other);
  }
  other.~S21Matrix();
}

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

void S21Matrix::InitMatrix() {
  if (rows_ <= 0 || cols_ <= 0) throw "Wrong number of rows or columns";
  matrix_ = (double**)calloc(rows_, sizeof(double*));
  if (matrix_ == nullptr) throw "Allocation error";
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = (double*)calloc(cols_, sizeof(double));
    if (matrix_[i] == nullptr) {
      for (int k = 0; k < i; k++) {
        free(matrix_[k]);
      }
      free(matrix_);
      matrix_ = nullptr;
      throw "Allocation error";
    }
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) throw "Wrong number of rows or columns";
  rows_ = rows;
  cols_ = cols;
  InitMatrix();
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int k = 0; k < rows_; k++) {
      free(matrix_[k]);
    }
    free(matrix_);
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::Copy(const S21Matrix& other) {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (other.matrix_ == nullptr || other.rows_ <= 0 || other.cols_ <= 0)
    throw "Used matrix is not valid";
  int new_rows = rows_, new_cols = cols_;
  if (rows_ > other.rows_) new_rows = other.rows_;
  if (cols_ > other.cols_) new_cols = other.cols_;
  for (int i = 0; i < new_rows; i++) {
    for (int j = 0; j < new_cols; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}