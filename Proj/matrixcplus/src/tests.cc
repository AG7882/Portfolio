#include "s21_matrix_oop.h"

#include <gtest/gtest.h>

TEST(equal, 1)
{
  S21Matrix matrix_a(1, 1);
  S21Matrix matrix_b(1, 1);
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(equal, 2)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = 2.2;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3333333;
  matrix_b(1, 1) = 0.0;
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(equal, 3)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = 2.2;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3333333;
  matrix_b(1, 1) = 1.0;
  EXPECT_FALSE(matrix_a == matrix_b);
}

TEST(sum, 1)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3333333;
  matrix_b(1, 1) = 1.0;
  matrix_c(0, 0) = 2.2;
  matrix_c(0, 1) = -0.1;
  matrix_c(1, 0) = 6.6666666;
  matrix_c(1, 1) = 1.0;
  matrix_a.SumMatrix(matrix_b);
  EXPECT_TRUE(matrix_a == matrix_c);
}

TEST(sum, 2)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3333333;
  matrix_b(1, 1) = 1.0;
  matrix_c(0, 0) = 2.2;
  matrix_c(0, 1) = -0.1;
  matrix_c(1, 0) = 6.0;
  matrix_c(1, 1) = 1.0;
  matrix_a.SumMatrix(matrix_b);
  EXPECT_FALSE(matrix_a == matrix_c);
}

TEST(sub, 1)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  matrix_c(0, 0) = 10;
  matrix_c(0, 1) = 2;
  matrix_c(1, 0) = -3;
  matrix_c(1, 1) = -2;
  matrix_a.SubMatrix(matrix_b);
  EXPECT_TRUE(matrix_a == matrix_c);
}

TEST(sub, 2)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 6.6666666;
  matrix_a(1, 1) = 1.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3333333;
  matrix_b(1, 1) = 1.0;
  matrix_c(0, 0) = 2.2;
  matrix_c(0, 1) = -0.1;
  matrix_c(1, 0) = 0.0;
  matrix_c(1, 1) = 1.0;
  matrix_a.SubMatrix(matrix_b);
  EXPECT_FALSE(matrix_a == matrix_c);
}

TEST(mult_n, 1)
{
  S21Matrix matrix_a(2, 2);
  double B_num = 2.0;
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_c(0, 0) = 2.2;
  matrix_c(0, 1) = -4.6;
  matrix_c(1, 0) = 6.6666666;
  matrix_c(1, 1) = 0.0;
  matrix_a.MulNumber(B_num);
  EXPECT_TRUE(matrix_a == matrix_c);
}

TEST(mult_m, 1)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3;
  matrix_b(1, 1) = 1.0;
  matrix_c(0, 0) = -6.38;
  matrix_c(0, 1) = 0.12;
  matrix_c(1, 0) = 3.63;
  matrix_c(1, 1) = 7.26;
  matrix_a.MulMatrix(matrix_b);
  EXPECT_TRUE(matrix_a == matrix_c);
}

TEST(transpose, 1)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 3.3;
  matrix_b(1, 0) = -2.3;
  matrix_b(1, 1) = 0.0;
  S21Matrix matrix_c = matrix_a.Transpose();
  EXPECT_TRUE(matrix_c == matrix_b);
}

TEST(determinant, 1)
{
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 4;
  matrix_a(1, 1) = 5;
  matrix_a(1, 2) = 6;
  matrix_a(2, 0) = 7;
  matrix_a(2, 1) = 8;
  matrix_a(2, 2) = 9;
  matrix_a.Transpose();
  EXPECT_TRUE(matrix_a.Determinant() == 0);
}

TEST(calc, 1)
{
  S21Matrix matrix_a(3, 3);
  S21Matrix matrix_c(3, 3);
  matrix_a(0, 0) = 1;
  matrix_a(0, 1) = 2;
  matrix_a(0, 2) = 3;
  matrix_a(1, 0) = 0;
  matrix_a(1, 1) = 4;
  matrix_a(1, 2) = 2;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = 2;
  matrix_a(2, 2) = 1;
  matrix_c(0, 0) = 0;
  matrix_c(0, 1) = 10;
  matrix_c(0, 2) = -20;
  matrix_c(1, 0) = 4;
  matrix_c(1, 1) = -14;
  matrix_c(1, 2) = 8;
  matrix_c(2, 0) = -8;
  matrix_c(2, 1) = -2;
  matrix_c(2, 2) = 4;
  S21Matrix matrix_b = matrix_a.CalcComplements();

  EXPECT_TRUE(matrix_b == matrix_c);
}

TEST(inverse, 1)
{
  S21Matrix matrix_a(3, 3);
  matrix_a(0, 0) = 2;
  matrix_a(0, 1) = 5;
  matrix_a(0, 2) = 7;
  matrix_a(1, 0) = 6;
  matrix_a(1, 1) = 3;
  matrix_a(1, 2) = 4;
  matrix_a(2, 0) = 5;
  matrix_a(2, 1) = -2;
  matrix_a(2, 2) = -3;
  S21Matrix matrix_b = matrix_a.InverseMatrix();
  S21Matrix matrix_c(3, 3);
  matrix_c(0, 0) = 1;
  matrix_c(0, 1) = -1;
  matrix_c(0, 2) = 1;
  matrix_c(1, 0) = -38;
  matrix_c(1, 1) = 41;
  matrix_c(1, 2) = -34;
  matrix_c(2, 0) = 27;
  matrix_c(2, 1) = -29;
  matrix_c(2, 2) = 24;
  EXPECT_TRUE(matrix_b == matrix_c);
}

TEST(mutators, setCols)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 1);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = 2.2;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(1, 0) = 3.3333333;
  matrix_a.setCols(1);
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(mutators, getCols)
{
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = 2.2;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;

  EXPECT_TRUE(matrix_a.getCols() == 2);
}

TEST(mutators, setRows)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(1, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = 2.2;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_a.setRows(1);
  EXPECT_TRUE(matrix_a == matrix_b);
}

TEST(mutators, getRows)
{
  S21Matrix matrix_a(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = 2.2;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;

  EXPECT_TRUE(matrix_a.getRows() == 2);
}

TEST(operators, plus)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3333333;
  matrix_b(1, 1) = 1.0;
  matrix_c(0, 0) = 2.2;
  matrix_c(0, 1) = -0.1;
  matrix_c(1, 0) = 6.6666666;
  matrix_c(1, 1) = 1.0;

  EXPECT_TRUE((matrix_a + matrix_b) == matrix_c);
}

TEST(operators, minus)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  matrix_c(0, 0) = 10;
  matrix_c(0, 1) = 2;
  matrix_c(1, 0) = -3;
  matrix_c(1, 1) = -2;

  EXPECT_TRUE((matrix_a - matrix_b) == matrix_c);
}

TEST(operators, mulNum)
{
  S21Matrix matrix_a(2, 2);
  double B_num = 2.0;
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_c(0, 0) = 2.2;
  matrix_c(0, 1) = -4.6;
  matrix_c(1, 0) = 6.6666666;
  matrix_c(1, 1) = 0.0;

  EXPECT_TRUE((matrix_a * B_num) == matrix_c);
}

TEST(operators, mulMat)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3;
  matrix_b(1, 1) = 1.0;
  matrix_c(0, 0) = -6.38;
  matrix_c(0, 1) = 0.12;
  matrix_c(1, 0) = 3.63;
  matrix_c(1, 1) = 7.26;
  EXPECT_TRUE((matrix_a * matrix_b) == matrix_c);
}

TEST(operators, plusEq)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3333333;
  matrix_b(1, 1) = 1.0;
  matrix_c(0, 0) = 2.2;
  matrix_c(0, 1) = -0.1;
  matrix_c(1, 0) = 6.6666666;
  matrix_c(1, 1) = 1.0;
  matrix_a += matrix_b;
  EXPECT_TRUE(matrix_a == matrix_c);
}

TEST(operators, minusEq)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 3;
  matrix_a(0, 1) = 2;
  matrix_a(1, 0) = -6;
  matrix_a(1, 1) = 0;
  matrix_b(0, 0) = -7;
  matrix_b(0, 1) = 0;
  matrix_b(1, 0) = -3;
  matrix_b(1, 1) = 2;
  matrix_c(0, 0) = 10;
  matrix_c(0, 1) = 2;
  matrix_c(1, 0) = -3;
  matrix_c(1, 1) = -2;
  matrix_a -= matrix_b;
  EXPECT_TRUE(matrix_a == matrix_c);
}

TEST(operators, mulNEq)
{
  S21Matrix matrix_a(2, 2);
  double B_num = 2.0;
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3333333;
  matrix_a(1, 1) = 0.0;
  matrix_c(0, 0) = 2.2;
  matrix_c(0, 1) = -4.6;
  matrix_c(1, 0) = 6.6666666;
  matrix_c(1, 1) = 0.0;
  matrix_a *= B_num;
  EXPECT_TRUE(matrix_a == matrix_c);
}

TEST(operators, mulMatEq)
{
  S21Matrix matrix_a(2, 2);
  S21Matrix matrix_b(2, 2);
  S21Matrix matrix_c(2, 2);
  matrix_a(0, 0) = 1.1;
  matrix_a(0, 1) = -2.3;
  matrix_a(1, 0) = 3.3;
  matrix_a(1, 1) = 0.0;
  matrix_b(0, 0) = 1.1;
  matrix_b(0, 1) = 2.2;
  matrix_b(1, 0) = 3.3;
  matrix_b(1, 1) = 1.0;
  matrix_c(0, 0) = -6.38;
  matrix_c(0, 1) = 0.12;
  matrix_c(1, 0) = 3.63;
  matrix_c(1, 1) = 7.26;
  matrix_a *= matrix_b;
  EXPECT_TRUE(matrix_a == matrix_c);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
