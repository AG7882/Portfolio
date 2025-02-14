#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <stdexcept>

#define EPS 1e-7
#define EX_CODE_OK 0
#define EX_CODE_WRONG_MATRIX 1

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  bool createMatrix();
  void outError(char num);
  void removeMatrix();
  void copyMatrix(const S21Matrix &other);
  bool zeroRowCol(const S21Matrix &other);
  S21Matrix get_minor(int row, int column) const;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  double get_determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(const double num);
  double &operator()(int i, int j);
  double operator()(int i, int j) const;

  void setRows(int rows);
  int getRows() const;
  void setCols(int cols);
  int getCols() const;
};

#endif