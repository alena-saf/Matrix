#include "../matrix.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (other.matrix_ == nullptr || other.rows_ <= 0 || other.cols_ <= 0)
    throw "Used matrix is not valid";
  bool result = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    result = false;
  else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
          result = false;
        }
      }
    }
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (other.matrix_ == nullptr || other.rows_ <= 0 || other.cols_ <= 0)
    throw "Used matrix is not valid";
  if (rows_ != other.rows_ || cols_ != other.cols_) throw "Calculation error";
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (other.matrix_ == nullptr || other.rows_ <= 0 || other.cols_ <= 0)
    throw "Used matrix is not valid";
  if (rows_ != other.rows_ || cols_ != other.cols_) throw "Calculation error";
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (std::isinf(num) == true || std::isnan(num) == true) throw "Wrong number";
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != 0) matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (other.matrix_ == nullptr || other.rows_ <= 0 || other.cols_ <= 0)
    throw "Used matrix is not valid";
  if (cols_ != other.rows_) throw "These matrices cannot be multiplied";
  S21Matrix temp(rows_, other.cols_);
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        temp.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  this->SetCols(temp.cols_);
  this->Copy(temp);
  temp.~S21Matrix();
}

S21Matrix S21Matrix::Transpose() {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (rows_ != cols_) throw "Complements cannot be found";
  if (rows_ == 1) throw "Complements cannot be found";
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = this->CreateMinor(i, j);
      double det_res = 0, helper = 1;
      det_res = minor.Determinant();
      helper = (i + j) % 2 == 0 ? 1 : -1;
      result.matrix_[i][j] = helper * det_res;
      minor.~S21Matrix();
    }
  }
  return result;
}

S21Matrix S21Matrix::CreateMinor(int row, int column) {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int k = 0; k < rows_; k++) {
    for (int j = 0; j < cols_; j++) {
      if (j < column && k < row)
        minor.matrix_[k][j] = this->matrix_[k][j];
      else if (j < column && k > row)
        minor.matrix_[k - 1][j] = this->matrix_[k][j];
      else if (j > column && k < row)
        minor.matrix_[k][j - 1] = this->matrix_[k][j];
      else if (j > column && k > row)
        minor.matrix_[k - 1][j - 1] = this->matrix_[k][j];
    }
  }
  return minor;
}

double S21Matrix::Determinant() {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (rows_ != cols_) throw "Determinant cannot be found";
  double result = 0;
  if (rows_ == 1)
    result = matrix_[0][0];
  else if (rows_ == 2)
    result = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  else if (rows_ == 3)
    result = matrix_[0][0] * matrix_[1][1] * matrix_[2][2] +
             matrix_[2][0] * matrix_[0][1] * matrix_[1][2] +
             matrix_[0][2] * matrix_[1][0] * matrix_[2][1] -
             matrix_[2][0] * matrix_[1][1] * matrix_[0][2] -
             matrix_[2][2] * matrix_[0][1] * matrix_[1][0] -
             matrix_[0][0] * matrix_[2][1] * matrix_[1][2];
  else {
    double helper = 1;
    result = 0;
    for (int i = 0; i < cols_; i++) {
      S21Matrix minor = this->CreateMinor(0, i);
      double sub_res = 0;
      sub_res = minor.Determinant();
      result += matrix_[0][i] * helper * sub_res;
      helper *= -1;
      minor.~S21Matrix();
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (matrix_ == nullptr || rows_ <= 0 || cols_ <= 0)
    throw "Used matrix is not valid";
  if (rows_ != cols_) throw "The inverse matrix cannot be found";
  double det = this->Determinant();
  if (det == 0) throw "The inverse matrix cannot be found";
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / this->matrix_[0][0];
  } else {
    S21Matrix help_matrix = this->CalcComplements();
    det = 1.0 / det;
    S21Matrix temp = help_matrix.Transpose();
    temp.MulNumber(det);
    result.Copy(temp);
    help_matrix.~S21Matrix();
    temp.~S21Matrix();
  }
  return result;
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) throw "Number of columns <= 0";
  S21Matrix temp(*this);
  for (int i = 0; i < this->rows_; i++) {
    free(matrix_[i]);
  }
  free(matrix_);
  this->cols_ = cols;
  InitMatrix();
  this->Copy(temp);
  temp.~S21Matrix();
}

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) throw "Number of rows <= 0";
  S21Matrix temp(*this);
  for (int i = 0; i < this->rows_; i++) {
    free(matrix_[i]);
  }
  free(matrix_);
  this->rows_ = rows;
  InitMatrix();
  this->Copy(temp);
  temp.~S21Matrix();
}

int S21Matrix::GetRows() { return this->rows_; }

int S21Matrix::GetCols() { return this->cols_; }
