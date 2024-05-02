#include "my_matrix_oop.h"

MYMatrix::MYMatrix() : MYMatrix(3, 3) {}

MYMatrix::MYMatrix(int m, int n) : rows_(m), cols_(n) {
  if (!ValidRowsCols(m) || !ValidRowsCols(n))
    throw std::runtime_error("Error: Arguments mush be possitive");

  matrix_ = new double*[m];
  for (int i = 0; i < m; i++) {
    matrix_[i] = new double[n];
    for (int j = 0; j < n; j++) matrix_[i][j] = 0.0;
  }
}

MYMatrix::MYMatrix(const MYMatrix& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  Alloc();
  Copy(other);
}

MYMatrix::MYMatrix(MYMatrix&& other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

MYMatrix::~MYMatrix() { Free(); }

bool MYMatrix::EqMatrix(const MYMatrix& other) const {
  bool res = true;

  if (!IsEqualDimensions(other)) res = false;

  if (res) {
    for (int i = 0; i < rows_ && res; i++) {
      for (int j = 0; j < cols_ && res; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= MY_EPS) res = false;
      }
    }
  }

  return res;
}

void MYMatrix::SumMatrix(const MYMatrix& other) {
  if (!IsEqualDimensions(other))
    throw std::runtime_error("Error: Matrix must be same dimensions");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void MYMatrix::SubMatrix(const MYMatrix& other) {
  if (!IsEqualDimensions(other))
    throw std::runtime_error("Error: Matrix must be same dimensions");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void MYMatrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void MYMatrix::MulMatrix(const MYMatrix& other) {
  if (other.rows_ != cols_)
    throw std::runtime_error(
        "Error: Cols from first matrix must be \
                                equal to rows from second matrix");

  MYMatrix res(rows_, other.cols_);
  for (int i = 0; i < res.rows_; i++) {
    for (int j = 0; j < res.cols_; j++) {
      for (int k = 0; k < cols_; k++)
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
    }
  }

  *this = res;
}

MYMatrix MYMatrix::Transpose() {
  MYMatrix res(cols_, rows_);

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res.matrix_[j][i] = matrix_[i][j];

  return res;
}

MYMatrix MYMatrix::CalcComplements() {
  if (!IsMatrixSquare())
    throw std::runtime_error("Error: Matrix must be squared");

  MYMatrix res(rows_, cols_);
  if (rows_ == 1)
    res.matrix_[0][0] = matrix_[0][0];
  else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) {
        MYMatrix minor(Minor(i, j));
        res.matrix_[i][j] = pow(-1, i + j) * minor.Determinant();
      }
  }

  return res;
}

double MYMatrix::Determinant() {
  if (!IsMatrixSquare())
    throw std::runtime_error("Error: Matrix must be squared");

  double res = 0;

  if (rows_ == 1)
    res = matrix_[0][0];
  else {
    for (int j = 0; j < cols_; j++) {
      MYMatrix minor(Minor(0, j));
      res += pow(-1, j) * matrix_[0][j] * minor.Determinant();
    }
  }

  return res;
}

MYMatrix MYMatrix::InverseMatrix() {
  if (!IsMatrixSquare())
    throw std::runtime_error("Error: Matrix must be squared");
  double det = Determinant();
  if (fabs(det) < MY_EPS)
    throw std::runtime_error("Error: Determinant must be not zero");

  MYMatrix res(rows_, cols_);
  if (rows_ == 1)
    res.matrix_[0][0] = 1.0 / matrix_[0][0];
  else {
    MYMatrix com = CalcComplements();
    res = com.Transpose();
    res.MulNumber(1 / det);
  }

  return res;
}

MYMatrix MYMatrix::operator+(const MYMatrix& other) {
  MYMatrix res(*this);
  res.SumMatrix(other);

  return res;
}

MYMatrix MYMatrix::operator-(const MYMatrix& other) {
  MYMatrix res(*this);
  res.SubMatrix(other);

  return res;
}

MYMatrix MYMatrix::operator*(const double num) {
  MYMatrix res(*this);
  res.MulNumber(num);

  return res;
}

MYMatrix operator*(double num, MYMatrix& other) { return other * num; }

MYMatrix MYMatrix::operator*(const MYMatrix& other) {
  MYMatrix res(*this);
  res.MulMatrix(other);

  return res;
}

bool MYMatrix::operator==(const MYMatrix& other) const {
  return EqMatrix(other);
}

MYMatrix& MYMatrix::operator=(const MYMatrix& other) {
  if (this != &other) {
    Free();
    rows_ = other.rows_;
    cols_ = other.cols_;
    Alloc();
    Copy(other);
  }

  return *this;
}

MYMatrix& MYMatrix::operator+=(const MYMatrix& other) {
  SumMatrix(other);

  return *this;
}

MYMatrix& MYMatrix::operator-=(const MYMatrix& other) {
  SubMatrix(other);

  return *this;
}

MYMatrix& MYMatrix::operator*=(const double num) {
  MulNumber(num);

  return *this;
}

MYMatrix& MYMatrix::operator*=(const MYMatrix& other) {
  MulMatrix(other);

  return *this;
}

double& MYMatrix::operator()(int i, int j) {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::runtime_error("Error: Index is invalid");

  return matrix_[i][j];
}

double& MYMatrix::operator()(int i, int j) const {
  if (i < 0 || j < 0 || i >= rows_ || j >= cols_)
    throw std::runtime_error("Error: Index is invalid");

  return matrix_[i][j];
}

int MYMatrix::GetRows() const { return rows_; }

int MYMatrix::GetCols() const { return cols_; }

void MYMatrix::SetRows(int rows) {
  if (!ValidRowsCols(rows))
    throw std::runtime_error("Error: Argument mush be possitive");

  MYMatrix res(rows, cols_);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols_; j++) {
      if (i < rows_)
        res.matrix_[i][j] = matrix_[i][j];
      else
        res.matrix_[i][j] = 0;
    }
  }

  *this = res;
}

void MYMatrix::SetCols(int cols) {
  if (!ValidRowsCols(cols))
    throw std::runtime_error("Error: Argument mush be possitive");

  MYMatrix res(rows_, cols);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols; j++) {
      if (j < cols_)
        res.matrix_[i][j] = matrix_[i][j];
      else
        res.matrix_[i][j] = 0;
    }
  }

  *this = res;
}

bool MYMatrix::ValidRowsCols(int val) { return val > 0; }

void MYMatrix::Alloc() {
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) matrix_[i][j] = 0.0;
  }
}

void MYMatrix::Copy(const MYMatrix& other) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

bool MYMatrix::IsEqualDimensions(const MYMatrix& other) const {
  return rows_ == other.rows_ && cols_ == other.cols_;
}

void MYMatrix::Free() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++)
      if (matrix_[i]) delete[] matrix_[i];
    delete[] matrix_;
  }
}

bool MYMatrix::IsMatrixSquare() { return rows_ == cols_; }

MYMatrix MYMatrix::Minor(int row, int col) {
  MYMatrix res(rows_ - 1, cols_ - 1);

  for (int i = 0, i_r = 0; i < rows_; i++) {
    if (i != row) {
      for (int j = 0, j_r = 0; j < cols_; j++) {
        if (j != col) {
          res.matrix_[i_r][j_r] = matrix_[i][j];
          j_r++;
        }
      }

      i_r++;
    }
  }

  return res;
}
