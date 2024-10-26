#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>

#define OK 0
#define ERROR 1
#define ERROR_CALC 2
#define SUCCESS 1
#define FAILURE 0

class S21Matrix {
  friend S21Matrix operator*(double num, const S21Matrix& o);

 private:
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();  // Default constructor
  S21Matrix(int rows, int cols);
  ~S21Matrix();                       // Destructor
  S21Matrix(const S21Matrix& other);  //конструктор копирования
  S21Matrix(S21Matrix&& other);

  void Print();
  void Input_a();
  void Input_b();
  void SetCols(int cols);
  void SetRows(int rows);
  int GetRows();
  int GetCols();
  void InitMatrix();
  void Copy(const S21Matrix& other);
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix CreateMinor(int row, int column);
  double Determinant();
  S21Matrix InverseMatrix();

  double& operator()(int row, int col);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(double num);
};

#endif