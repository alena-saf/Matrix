#include "../matrix.h"

double& S21Matrix::operator()(int row, int col) {
  if (this->matrix_ == nullptr) {
    throw "Used matrix is not valid";
  } else if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw "Wrong value of row or column";
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix copy(*this);
  copy.SumMatrix(other);
  return copy;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix copy(*this);
  copy.SubMatrix(other);
  return copy;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix copy(*this);
  copy.MulMatrix(other);
  return copy;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix copy(*this);
  copy.MulNumber(num);
  return copy;
}

S21Matrix operator*(double num, const S21Matrix& other) {
  S21Matrix copy(other);
  copy.MulNumber(num);
  return copy;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  bool result = this->EqMatrix(other);
  return result;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (&other != this) {
    if (matrix_ != nullptr) {
      for (int k = 0; k < rows_; k++) {
        free(matrix_[k]);
      }
      free(matrix_);
      matrix_ = nullptr;
    }
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    InitMatrix();
    this->Copy(other);
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(double num) {
  this->MulNumber(num);
  return *this;
}