#include <gtest/gtest.h>

#include "../my_matrix_oop.h"

TEST(Test_1, Constructor) {
  MYMatrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(Test_2, Constuctor) {
  MYMatrix matrix(1, 1);
  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetCols(), 1);
}

TEST(Test_3, Constructor) {
  MYMatrix matrix(2, 3);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(Test_4, Constructor) {
  EXPECT_THROW(MYMatrix matrix(2, -4), std::runtime_error);
}

TEST(Test_4, Copy) {
  MYMatrix src(4, 5);
  src(0, 0) = 4.5;
  src(0, 1) = 4.2;
  src(3, 4) = 2.6;
  src(0, 2) = -1;
  src(2, 4) = 12.32;
  src(3, 3) = -131.213;
  MYMatrix dst(src);

  EXPECT_EQ(true, src == dst);
}

TEST(Test_5, Copy) {
  MYMatrix src(2, 3);
  src(0, 0) = 131.5;
  src(0, 1) = 242.35;
  src(0, 2) = 2144.622;
  src(1, 0) = -11442;
  src(1, 1) = 11242.224;
  src(1, 2) = 24121.2233;
  MYMatrix dst(src);

  EXPECT_EQ(true, src == dst);
}

TEST(Test_6, Move) {
  MYMatrix src(2, 3);
  src(0, 0) = 131.5;
  src(0, 1) = 242.35;
  src(0, 2) = 2144.622;
  src(1, 0) = -11442;
  src(1, 1) = 11242.224;
  src(1, 2) = 24121.2233;
  MYMatrix tmp(src);
  MYMatrix dst(std::move(src));

  EXPECT_EQ(true, tmp == dst);
  EXPECT_EQ(0, src.GetCols());
  EXPECT_EQ(0, src.GetRows());
}

TEST(Test_7, Move) {
  MYMatrix src(4, 5);
  src(0, 0) = 4.5;
  src(0, 1) = 4.2;
  src(3, 4) = 2.6;
  src(0, 2) = -1;
  src(2, 4) = 12.32;
  src(3, 3) = -131.213;
  MYMatrix tmp(src);
  MYMatrix dst(std::move(src));

  EXPECT_EQ(true, tmp == dst);
  EXPECT_EQ(0, src.GetCols());
  EXPECT_EQ(0, src.GetRows());
}

TEST(Test_8, Equal) {
  MYMatrix first(2, 3);
  MYMatrix second(3, 2);

  EXPECT_NE(true, first.EqMatrix(second));
}

TEST(Test_9, Equal) {
  MYMatrix first(3, 2);
  MYMatrix second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;

  EXPECT_EQ(first.GetCols(), second.GetCols());
  EXPECT_EQ(first.GetRows(), second.GetRows());
  EXPECT_EQ(first(0, 0), second(0, 0));
  EXPECT_EQ(first(0, 1), second(0, 1));
  EXPECT_EQ(first(1, 0), second(1, 0));
  EXPECT_EQ(first(1, 1), second(1, 1));
  EXPECT_EQ(first(2, 0), second(2, 0));
  EXPECT_EQ(first(2, 1), second(2, 1));
}

TEST(Test_10, Sum) {
  MYMatrix first(3, 2);
  MYMatrix second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  first.SumMatrix(second);
  EXPECT_EQ(first.GetCols(), second.GetCols());
  EXPECT_EQ(first.GetRows(), second.GetRows());
  EXPECT_EQ(first(0, 0), second(0, 0) * 2);
  EXPECT_EQ(first(0, 1), second(0, 1) * 2);
  EXPECT_EQ(first(1, 0), second(1, 0) * 2);
  EXPECT_EQ(first(1, 1), second(1, 1) * 2);
  EXPECT_EQ(first(2, 0), second(2, 0) * 2);
  EXPECT_EQ(first(2, 1), second(2, 1) * 2);
}

TEST(Test_11, Sum) {
  MYMatrix first(3, 2);
  MYMatrix second(2, 3);

  EXPECT_THROW(first.SumMatrix(second), std::runtime_error);
}

TEST(Test_12, Sub) {
  MYMatrix first(3, 2);
  MYMatrix second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  first.SubMatrix(second);
  EXPECT_EQ(first.GetCols(), second.GetCols());
  EXPECT_EQ(first.GetRows(), second.GetRows());
  EXPECT_EQ(first(0, 0), 0);
  EXPECT_EQ(first(0, 1), 0);
  EXPECT_EQ(first(1, 0), 0);
  EXPECT_EQ(first(1, 1), 0);
  EXPECT_EQ(first(2, 0), 0);
  EXPECT_EQ(first(2, 1), 0);
}

TEST(Test_13, Sub) {
  MYMatrix first(3, 2);
  MYMatrix second(2, 3);

  EXPECT_THROW(first.SubMatrix(second), std::runtime_error);
}

TEST(Test_14, MulNum) {
  double num = 23.34;
  MYMatrix first(3, 2), second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  first.MulNumber(num);
  EXPECT_EQ(first.GetCols(), 2);
  EXPECT_EQ(first.GetRows(), 3);
  EXPECT_EQ(first(0, 0), second(0, 0) * num);
  EXPECT_EQ(first(0, 1), second(0, 1) * num);
  EXPECT_EQ(first(1, 0), second(1, 0) * num);
  EXPECT_EQ(first(1, 1), second(1, 1) * num);
  EXPECT_EQ(first(2, 0), second(2, 0) * num);
  EXPECT_EQ(first(2, 1), second(2, 1) * num);
}

TEST(Test_15, MulMatrix) {
  MYMatrix first(1, 2);
  MYMatrix second(2, 3);

  first(0, 0) = 123.5;
  first(0, 1) = 23.4;

  second(0, 0) = 2;
  second(0, 1) = 1.2;
  second(0, 2) = 4.5;
  second(1, 0) = -13;
  second(1, 1) = 0;
  second(1, 2) = -2;

  EXPECT_THROW(second.MulMatrix(first), std::runtime_error);
  first.MulMatrix(second);

  EXPECT_DOUBLE_EQ(first.GetRows(), 1);
  EXPECT_DOUBLE_EQ(first.GetCols(), 3);
  EXPECT_DOUBLE_EQ(first(0, 0), -57.2);
  EXPECT_DOUBLE_EQ(first(0, 1), 148.2);
  EXPECT_DOUBLE_EQ(first(0, 2), 508.95);
}

TEST(Test_16, Transpose) {
  MYMatrix first(1, 1);
  first(0, 0) = 1234.56;
  first.Transpose();
  EXPECT_EQ(first.GetCols(), 1);
  EXPECT_EQ(first.GetRows(), 1);
  EXPECT_DOUBLE_EQ(first(0, 0), 1234.56);
}

TEST(Test_17, Transpose) {
  MYMatrix second(2, 3);

  second(0, 0) = 2;
  second(0, 1) = 1.2;
  second(0, 2) = 4.5;
  second(1, 0) = -13;
  second(1, 1) = 0;
  second(1, 2) = -2;
  MYMatrix res = second.Transpose();

  EXPECT_DOUBLE_EQ(res(0, 0), second(0, 0));
  EXPECT_DOUBLE_EQ(res(0, 1), second(1, 0));
  EXPECT_DOUBLE_EQ(res(1, 0), second(0, 1));
  EXPECT_DOUBLE_EQ(res(1, 1), second(1, 1));
  EXPECT_DOUBLE_EQ(res(2, 0), second(0, 2));
  EXPECT_DOUBLE_EQ(res(2, 1), second(1, 2));

  EXPECT_EQ(res.GetCols(), 2);
  EXPECT_EQ(res.GetRows(), 3);
}

TEST(Test_18, Components) {
  MYMatrix first(3, 3), expect(3, 3);
  first(0, 0) = 3.0;
  first(0, 1) = 2.0;
  first(0, 2) = -1.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;
  first(1, 2) = 5.0;
  first(2, 0) = 1.0;
  first(2, 1) = -1.0;
  first(2, 2) = 1.0;
  expect(0, 0) = 1.0;
  expect(0, 1) = 8.0;
  expect(0, 2) = 7.0;
  expect(1, 0) = -1.0;
  expect(1, 1) = 4.0;
  expect(1, 2) = 5.0;
  expect(2, 0) = 6.0;
  expect(2, 1) = -12.0;
  expect(2, 2) = -6.0;

  MYMatrix res(first.CalcComplements());
  EXPECT_EQ(true, res.EqMatrix(expect));
}

TEST(Test_20, Components) {
  MYMatrix first(3, 2);
  EXPECT_THROW(first.CalcComplements(), std::runtime_error);
}

TEST(Test_21, Components) {
  MYMatrix first(1, 1);
  first(0, 0) = 2.97;

  MYMatrix res = first.CalcComplements();
  EXPECT_EQ(res(0, 0), first(0, 0));
}

TEST(Test_22, Determinant) {
  MYMatrix first(3, 3);
  first(0, 0) = 3.0;
  first(0, 1) = 2.0;
  first(0, 2) = -1.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;
  first(1, 2) = 5.0;
  first(2, 0) = 1.0;
  first(2, 1) = -1.0;
  first(2, 2) = 1.0;

  EXPECT_EQ(12, first.Determinant());
}

TEST(Test_23, Determinant) {
  MYMatrix first(2, 2);
  first(0, 0) = 3.0;
  first(0, 1) = 2.0;
  first(1, 0) = -1.0;
  first(1, 1) = -3.0;

  EXPECT_EQ(-7.0, first.Determinant());
}

TEST(Test_24, Determinant) {
  MYMatrix first(3, 4);

  EXPECT_THROW(first.Determinant(), std::runtime_error);
}

TEST(Test_25, Determinant) {
  MYMatrix first(1, 1);
  first(0, 0) = 2.87;

  EXPECT_EQ(first.Determinant(), 2.87);
}

TEST(Test_26, Inverse) {
  MYMatrix first(3, 3), expect(3, 3);
  first(0, 0) = 3.0;
  first(0, 1) = 2.0;
  first(0, 2) = -1.0;
  first(1, 0) = -3.0;
  first(1, 1) = -4.0;
  first(1, 2) = 5.0;
  first(2, 0) = 1.0;
  first(2, 1) = -1.0;
  first(2, 2) = 1.0;
  expect(0, 0) = 1.0 / 12;
  expect(0, 1) = -1.0 / 12;
  expect(0, 2) = 0.5;
  expect(1, 0) = 2.0 / 3;
  expect(1, 1) = 1.0 / 3;
  expect(1, 2) = -1.0;
  expect(2, 0) = 7.0 / 12;
  expect(2, 1) = 5.0 / 12;
  expect(2, 2) = -0.5;

  EXPECT_EQ(true, first.InverseMatrix().EqMatrix(expect));
}

TEST(Test_27, Inverse) {
  MYMatrix first(2, 1);
  first(0, 0) = 2.34;
  first(1, 0) = -32.23;
  EXPECT_THROW(first.InverseMatrix(), std::runtime_error);
}

TEST(Test_28, Inverse) {
  MYMatrix first(2, 2), expect(2, 2);
  first(0, 0) = 3.0;
  first(0, 1) = 2.0;
  first(1, 0) = -1.0;
  first(1, 1) = -3.0;

  expect(0, 0) = 3.0 / 7;
  expect(0, 1) = 2.0 / 7;
  expect(1, 0) = -1.0 / 7;
  expect(1, 1) = -3.0 / 7;

  MYMatrix res(first.InverseMatrix());

  EXPECT_EQ(true, res.EqMatrix(expect));
}

TEST(Test_29, Inverse) {
  MYMatrix first(1, 1), expect(1, 1);
  first(0, 0) = 3.0;

  expect(0, 0) = 1.0 / 3;

  EXPECT_EQ(true, first.InverseMatrix().EqMatrix(expect));
}

TEST(Test_30, Inverse) {
  MYMatrix first(2, 2), expect(2, 2);
  first(0, 0) = 3.0;
  first(0, 1) = 3.0;
  first(1, 0) = 2.0;
  first(1, 1) = 2.0;

  EXPECT_THROW(first.InverseMatrix(), std::runtime_error);
}

TEST(Test_31, Sum_operator) {
  MYMatrix first(3, 2);
  MYMatrix second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  MYMatrix res = first + second;
  EXPECT_EQ(first.GetCols(), second.GetCols());
  EXPECT_EQ(first.GetRows(), second.GetRows());
  EXPECT_EQ(res(0, 0), second(0, 0) * 2);
  EXPECT_EQ(res(0, 1), second(0, 1) * 2);
  EXPECT_EQ(res(1, 0), second(1, 0) * 2);
  EXPECT_EQ(res(1, 1), second(1, 1) * 2);
  EXPECT_EQ(res(2, 0), second(2, 0) * 2);
  EXPECT_EQ(res(2, 1), second(2, 1) * 2);
}

TEST(Test_32, Sum_operator) {
  MYMatrix first(3, 2);
  MYMatrix second(2, 3);

  EXPECT_THROW(first + second, std::runtime_error);
}

TEST(Test_33, Sub_operator) {
  MYMatrix first(3, 2);
  MYMatrix second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  MYMatrix res = first - second;
  EXPECT_EQ(res.GetCols(), second.GetCols());
  EXPECT_EQ(res.GetRows(), second.GetRows());
  EXPECT_EQ(res(0, 0), 0);
  EXPECT_EQ(res(0, 1), 0);
  EXPECT_EQ(res(1, 0), 0);
  EXPECT_EQ(res(1, 1), 0);
  EXPECT_EQ(res(2, 0), 0);
  EXPECT_EQ(res(2, 1), 0);
}

TEST(Test_34, Sub_operator) {
  MYMatrix first(3, 2);
  MYMatrix second(2, 3);

  EXPECT_THROW(first - second, std::runtime_error);
}

TEST(Test_35, MulNum_operator) {
  double num = 23.34;
  MYMatrix first(3, 2), second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  MYMatrix res = first * num;
  MYMatrix res2 = num * first;
  EXPECT_EQ(res.GetCols(), 2);
  EXPECT_EQ(res.GetRows(), 3);
  EXPECT_EQ(res(0, 0), second(0, 0) * num);
  EXPECT_EQ(res(0, 1), second(0, 1) * num);
  EXPECT_EQ(res(1, 0), second(1, 0) * num);
  EXPECT_EQ(res(1, 1), second(1, 1) * num);
  EXPECT_EQ(res(2, 0), second(2, 0) * num);
  EXPECT_EQ(res(2, 1), second(2, 1) * num);

  EXPECT_EQ(res2.GetCols(), 2);
  EXPECT_EQ(res2.GetRows(), 3);
  EXPECT_EQ(res2(0, 0), second(0, 0) * num);
  EXPECT_EQ(res2(0, 1), second(0, 1) * num);
  EXPECT_EQ(res2(1, 0), second(1, 0) * num);
  EXPECT_EQ(res2(1, 1), second(1, 1) * num);
  EXPECT_EQ(res2(2, 0), second(2, 0) * num);
  EXPECT_EQ(res2(2, 1), second(2, 1) * num);
}

TEST(Test_36, MulMatrix_operator) {
  MYMatrix first(1, 2);
  MYMatrix second(2, 3);

  first(0, 0) = 123.5;
  first(0, 1) = 23.4;

  second(0, 0) = 2;
  second(0, 1) = 1.2;
  second(0, 2) = 4.5;
  second(1, 0) = -13;
  second(1, 1) = 0;
  second(1, 2) = -2;

  EXPECT_THROW(second * first, std::runtime_error);
  MYMatrix res = first * second;

  EXPECT_DOUBLE_EQ(res.GetRows(), 1);
  EXPECT_DOUBLE_EQ(res.GetCols(), 3);
  EXPECT_DOUBLE_EQ(res(0, 0), -57.2);
  EXPECT_DOUBLE_EQ(res(0, 1), 148.2);
  EXPECT_DOUBLE_EQ(res(0, 2), 508.95);
}

TEST(Test_37, SumAssign_operator) {
  MYMatrix first(3, 2);
  MYMatrix second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  first += second;
  EXPECT_EQ(first.GetCols(), second.GetCols());
  EXPECT_EQ(first.GetRows(), second.GetRows());
  EXPECT_EQ(first(0, 0), second(0, 0) * 2);
  EXPECT_EQ(first(0, 1), second(0, 1) * 2);
  EXPECT_EQ(first(1, 0), second(1, 0) * 2);
  EXPECT_EQ(first(1, 1), second(1, 1) * 2);
  EXPECT_EQ(first(2, 0), second(2, 0) * 2);
  EXPECT_EQ(first(2, 1), second(2, 1) * 2);
}

TEST(Test_38, SumAssign_operator) {
  MYMatrix first(3, 2);
  MYMatrix second(2, 3);

  EXPECT_THROW(first += second, std::runtime_error);
}

TEST(Test_39, SubAssign_operator) {
  MYMatrix first(3, 2);
  MYMatrix second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  first -= second;
  EXPECT_EQ(first.GetCols(), second.GetCols());
  EXPECT_EQ(first.GetRows(), second.GetRows());
  EXPECT_EQ(first(0, 0), 0);
  EXPECT_EQ(first(0, 1), 0);
  EXPECT_EQ(first(1, 0), 0);
  EXPECT_EQ(first(1, 1), 0);
  EXPECT_EQ(first(2, 0), 0);
  EXPECT_EQ(first(2, 1), 0);
}

TEST(Test_40, SubAssign_operator) {
  MYMatrix first(3, 2);
  MYMatrix second(2, 3);

  EXPECT_THROW(first -= second, std::runtime_error);
}

TEST(Test_41, MulNumAssign_operator) {
  double num = 23.34;
  MYMatrix first(3, 2), second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;
  first *= num;
  EXPECT_EQ(first.GetCols(), 2);
  EXPECT_EQ(first.GetRows(), 3);
  EXPECT_EQ(first(0, 0), second(0, 0) * num);
  EXPECT_EQ(first(0, 1), second(0, 1) * num);
  EXPECT_EQ(first(1, 0), second(1, 0) * num);
  EXPECT_EQ(first(1, 1), second(1, 1) * num);
  EXPECT_EQ(first(2, 0), second(2, 0) * num);
  EXPECT_EQ(first(2, 1), second(2, 1) * num);
}

TEST(Test_42, MulMatrixAssign_operator) {
  MYMatrix first(1, 2);
  MYMatrix second(2, 3);

  first(0, 0) = 123.5;
  first(0, 1) = 23.4;

  second(0, 0) = 2;
  second(0, 1) = 1.2;
  second(0, 2) = 4.5;
  second(1, 0) = -13;
  second(1, 1) = 0;
  second(1, 2) = -2;

  EXPECT_THROW(second *= first, std::runtime_error);
  first *= second;

  EXPECT_DOUBLE_EQ(first.GetRows(), 1);
  EXPECT_DOUBLE_EQ(first.GetCols(), 3);
  EXPECT_DOUBLE_EQ(first(0, 0), -57.2);
  EXPECT_DOUBLE_EQ(first(0, 1), 148.2);
  EXPECT_DOUBLE_EQ(first(0, 2), 508.95);
}

TEST(Test_43, Index) {
  const MYMatrix first(2, 3);
  MYMatrix second(2, 3);
  double tmp;

  EXPECT_THROW(first(0, -1) = 3.0, std::runtime_error);
  EXPECT_THROW(first(-1, 0) = 3.0, std::runtime_error);
  EXPECT_THROW(first(2, 1) = 3.0, std::runtime_error);
  EXPECT_THROW(first(0, 3) = 3.0, std::runtime_error);
  tmp = first(0, 0);
  EXPECT_EQ(tmp, 0);

  EXPECT_THROW(second(0, -1) = 3.0, std::runtime_error);
  EXPECT_THROW(second(-1, 0) = 3.0, std::runtime_error);
  EXPECT_THROW(second(2, 1) = 3.0, std::runtime_error);
  EXPECT_THROW(second(0, 3) = 3.0, std::runtime_error);
  second(0, 1) = 3.42;
  tmp = second(0, 1);
  EXPECT_EQ(tmp, second(0, 1));
}

TEST(Test_44, SetRows) {
  MYMatrix first(1, 1);
  first(0, 0) = -3.2;
  first.SetRows(4);
  EXPECT_EQ(first(0, 0), -3.2);
  for (int i = 1; i < 4; i++) EXPECT_EQ(first(i, 0), 0);
}

TEST(Test_45, SetRows) {
  MYMatrix first(1, 1);
  first(0, 0) = -3.2;
  EXPECT_THROW(first.SetRows(0), std::runtime_error);
  EXPECT_THROW(first.SetRows(-1), std::runtime_error);
}

TEST(Test_46, SetRows) {
  MYMatrix first(3, 2), second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;

  first.SetRows(3);

  EXPECT_EQ(true, first == second);
}

TEST(Test_47, SetCols) {
  MYMatrix first(1, 1);
  first(0, 0) = -3.2;
  first.SetCols(4);
  EXPECT_EQ(first(0, 0), -3.2);
  for (int i = 1; i < 4; i++) EXPECT_EQ(first(0, i), 0);
}

TEST(Test_48, SetCows) {
  MYMatrix first(1, 1);
  first(0, 0) = -3.2;
  EXPECT_THROW(first.SetCols(0), std::runtime_error);
  EXPECT_THROW(first.SetCols(-1), std::runtime_error);
}

TEST(Test_49, SetRows) {
  MYMatrix first(3, 2), second(3, 2);
  first(0, 0) = second(0, 0) = 4.5;
  first(0, 1) = second(0, 1) = 4.2;
  first(1, 0) = second(1, 0) = 2.6;
  first(1, 1) = second(1, 1) = -1;
  first(2, 0) = second(2, 0) = 12.32;
  first(2, 1) = second(2, 1) = -131.213;

  first.SetCols(2);

  EXPECT_EQ(true, first == second);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}