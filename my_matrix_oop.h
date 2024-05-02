#ifndef _MY_MATRIX_OOP_H
#define _MY_MATRIX_OOP_H

#include <cmath>
#include <iostream>
#include <limits>

#define MY_EPS std::numeric_limits<double>::epsilon()

class MYMatrix {
 private:
  double** matrix_;
  int rows_;
  int cols_;

 public:
  MYMatrix();
  MYMatrix(int m, int n);
  MYMatrix(const MYMatrix& other);
  MYMatrix(MYMatrix&& other) noexcept;
  ~MYMatrix();

  bool EqMatrix(const MYMatrix& other) const;

  void SumMatrix(const MYMatrix& other);
  void SubMatrix(const MYMatrix& other);
  void MulNumber(const double num);
  void MulMatrix(const MYMatrix& other);

  MYMatrix Transpose();
  MYMatrix CalcComplements();
  double Determinant();
  MYMatrix InverseMatrix();

  MYMatrix operator+(const MYMatrix& other);
  MYMatrix operator-(const MYMatrix& other);
  MYMatrix operator*(const double num);
  friend MYMatrix operator*(double num, MYMatrix& other);
  MYMatrix operator*(const MYMatrix& other);

  bool operator==(const MYMatrix& other) const;
  MYMatrix& operator=(const MYMatrix& other);
  MYMatrix& operator+=(const MYMatrix& other);
  MYMatrix& operator-=(const MYMatrix& other);
  MYMatrix& operator*=(const double num);
  MYMatrix& operator*=(const MYMatrix& other);

  double& operator()(int i, int j);
  double& operator()(int i, int j) const;

  int GetRows() const;
  int GetCols() const;

  void SetRows(int rows);
  void SetCols(int cols);

 private:
  bool ValidRowsCols(int val);
  void Alloc();
  void Free();
  void Copy(const MYMatrix& other);
  bool IsEqualDimensions(const MYMatrix& other) const;
  bool IsMatrixSquare();
  MYMatrix Minor(int row, int col);
};

#endif