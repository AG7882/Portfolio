#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix() { rows_ = 0, cols_ = 0, matrix_ = nullptr; }

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows > 0 && cols > 0) {
    rows_ = rows, cols_ = cols;
    if (createMatrix()) throw std::runtime_error("err");
  } else {
    throw std::invalid_argument("err");
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  this->rows_ = other.rows_, this->cols_ = other.cols_;
  if (createMatrix()) throw std::runtime_error("err");
  copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  rows_ = other.rows_, cols_ = other.cols_, matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { removeMatrix(); }

void S21Matrix::copyMatrix(const S21Matrix &other) {
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) this->matrix_[i][j] = other(i, j);
}