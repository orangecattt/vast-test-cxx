// RUN: %driver -cc1 %isys -fenable-matrix %s -std=c++11 %target -o %t%output-suffix && %filecheck
typedef double dx5x5_t __attribute__((matrix_type(5, 5)));
using fx2x3_t = float __attribute__((matrix_type(2, 3)));

template <typename EltTy, unsigned Rows, unsigned Columns>
struct MyMatrix {
  using matrix_t = EltTy __attribute__((matrix_type(Rows, Columns)));

  matrix_t value;
};

template <typename EltTy0, unsigned R0, unsigned C0>
typename MyMatrix<EltTy0, R0, C0>::matrix_t add(MyMatrix<EltTy0, R0, C0> &A, MyMatrix<EltTy0, R0, C0> &B) {
  return A.value + B.value;
}

void test_add_template() {


  MyMatrix<float, 2, 5> Mat1;
  MyMatrix<float, 2, 5> Mat2;
  Mat1.value = add(Mat1, Mat2);
}

template <typename EltTy0, unsigned R0, unsigned C0>
typename MyMatrix<EltTy0, R0, C0>::matrix_t subtract(MyMatrix<EltTy0, R0, C0> &A, MyMatrix<EltTy0, R0, C0> &B) {
  return A.value - B.value;
}

void test_subtract_template() {


  MyMatrix<float, 2, 5> Mat1;
  MyMatrix<float, 2, 5> Mat2;
  Mat1.value = subtract(Mat1, Mat2);
}

struct DoubleWrapper1 {
  int x;
  operator double() {
    return x;
  }
};

void test_DoubleWrapper1_Sub1(MyMatrix<double, 10, 9> &m) {

  DoubleWrapper1 w1;
  w1.x = 10;
  m.value = m.value - w1;
}

void test_DoubleWrapper1_Sub2(MyMatrix<double, 10, 9> &m) {

  DoubleWrapper1 w1;
  w1.x = 10;
  m.value = w1 - m.value;
}

struct DoubleWrapper2 {
  int x;
  operator double() {
    return x;
  }
};

void test_DoubleWrapper2_Add1(MyMatrix<double, 10, 9> &m) {

  DoubleWrapper2 w2;
  w2.x = 20;
  m.value = m.value + w2;
}

void test_DoubleWrapper2_Add2(MyMatrix<double, 10, 9> &m) {

  DoubleWrapper2 w2;
  w2.x = 20;
  m.value = w2 + m.value;
}

struct IntWrapper {
  char x;
  operator int() {
    return x;
  }
};

void test_IntWrapper_Add(MyMatrix<double, 10, 9> &m) {

  IntWrapper w3;
  w3.x = 'c';
  m.value = m.value + w3;
}

void test_IntWrapper_Sub(MyMatrix<double, 10, 9> &m) {

  IntWrapper w3;
  w3.x = 'c';
  m.value = w3 - m.value;
}

template <typename EltTy0, unsigned R0, unsigned C0, unsigned C1>
typename MyMatrix<EltTy0, R0, C1>::matrix_t multiply(MyMatrix<EltTy0, R0, C0> &A, MyMatrix<EltTy0, C0, C1> &B) {
  return A.value * B.value;
}

MyMatrix<float, 2, 2> test_multiply_template(MyMatrix<float, 2, 5> Mat1,
                                             MyMatrix<float, 5, 2> Mat2) {

  MyMatrix<float, 2, 2> Res;
  Res.value = multiply(Mat1, Mat2);
  return Res;
}

void test_IntWrapper_Multiply(MyMatrix<double, 10, 9> &m, IntWrapper &w3) {
  m.value = w3 * m.value;
}

template <typename EltTy, unsigned Rows, unsigned Columns>
void insert(MyMatrix<EltTy, Rows, Columns> &Mat, EltTy e, unsigned i, unsigned j) {
  Mat.value[i][j] = e;
}

void test_insert_template1(MyMatrix<unsigned, 2, 2> &Mat, unsigned e, unsigned i, unsigned j) {

  insert(Mat, e, i, j);
}

void test_insert_template2(MyMatrix<float, 3, 8> &Mat, float e) {

  insert(Mat, e, 2, 5);
}

template <typename EltTy, unsigned Rows, unsigned Columns>
EltTy extract(MyMatrix<EltTy, Rows, Columns> &Mat) {
  return Mat.value[1u][0u];
}

int test_extract_template(MyMatrix<int, 2, 2> Mat1) {

  return extract(Mat1);
}

using double4x4 = double __attribute__((matrix_type(4, 4)));

template <class R, class C>
auto matrix_subscript(double4x4 m, R r, C c) -> decltype(m[r][c]) {}

double test_matrix_subscript(double4x4 m) {

  return matrix_subscript(m, 1, 2);
}

const double &test_matrix_subscript_reference(const double4x4 m) {

  return m[0][1];
}

struct UnsignedWrapper {
  char x;
  operator unsigned() {
    return x;
  }
};

double extract_IntWrapper_idx(double4x4 &m, IntWrapper i, UnsignedWrapper j) {
  return m[i + 1][j - 1];
}

template <class T, unsigned R, unsigned C>
using matrix_type = T __attribute__((matrix_type(R, C)));
struct identmatrix_t {
  template <class T, unsigned N>
  operator matrix_type<T, N, N>() const {
    matrix_type<T, N, N> result;
    for (unsigned i = 0; i != N; ++i)
      result[i][i] = 1;
    return result;
  }
};

constexpr identmatrix_t identmatrix;

void test_constexpr1(matrix_type<float, 4, 4> &m) {

  m = m + identmatrix;
}

void test_constexpr2(matrix_type<int, 5, 5> &m) {


  m = identmatrix - m + 1;
}
