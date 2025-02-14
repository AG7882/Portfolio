#include "../s21_matrix_oop.h"

void S21Matrix::setRows(int rows) {
  if (rows != rows_) {
    S21Matrix mem(rows, cols_);
    if (rows > rows_) {
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) mem.matrix_[i][j] = this->matrix_[i][j];
    } else
      mem.copyMatrix(*this);
    *this = mem;
  }
}

int S21Matrix::getRows() const { return rows_; }

void S21Matrix::setCols(int cols) {
  if (cols != cols_) {
    S21Matrix mem(rows_, cols);
    if (cols > cols_) {
      for (int i = 0; i < rows_; i++)
        for (int j = 0; j < cols_; j++) mem.matrix_[i][j] = this->matrix_[i][j];
    } else
      mem.copyMatrix(*this);
    *this = mem;
  }
}

int S21Matrix::getCols() const { return cols_; }