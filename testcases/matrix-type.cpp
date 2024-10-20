// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -fenable-matrix -fclang-abi-compat=latest %s -std=c++17 %target -o %t%output-suffix && %filecheck

typedef double dx5x5_t __attribute__((matrix_type(5, 5)));
typedef float fx3x4_t __attribute__((matrix_type(3, 4)));


void load_store(dx5x5_t *a, dx5x5_t *b) {

  *a = *b;
}

typedef float fx3x3_t __attribute__((matrix_type(3, 3)));

void parameter_passing(fx3x3_t a, fx3x3_t *b) {
  *b = a;
}

fx3x3_t return_matrix(fx3x3_t *a) {
  return *a;
}

struct Matrix {
  char Tmp1;
  fx3x4_t Data;
  float Tmp2;
};

void matrix_struct_pointers(Matrix *a, Matrix *b) {
  b->Data = a->Data;
}

void matrix_struct_reference(Matrix &a, Matrix &b) {
  b.Data = a.Data;
}

class MatrixClass {
public:
  int Tmp1;
  fx3x4_t Data;
  long Tmp2;
};

void matrix_class_reference(MatrixClass &a, MatrixClass &b) {
  b.Data = a.Data;
}

template <typename Ty, unsigned Rows, unsigned Cols>
class MatrixClassTemplate {
public:
  using MatrixTy = Ty __attribute__((matrix_type(Rows, Cols)));
  int Tmp1;
  MatrixTy Data;
  long Tmp2;
};

template <typename Ty, unsigned Rows, unsigned Cols>
void matrix_template_reference(MatrixClassTemplate<Ty, Rows, Cols> &a, MatrixClassTemplate<Ty, Rows, Cols> &b) {
  b.Data = a.Data;
}

MatrixClassTemplate<float, 10, 15> matrix_template_reference_caller(float *Data) {


  MatrixClassTemplate<float, 10, 15> Result, Arg;
  Arg.Data = *((MatrixClassTemplate<float, 10, 15>::MatrixTy *)Data);
  matrix_template_reference(Arg, Result);
  return Result;
}

template <class T, unsigned long R, unsigned long C>
using matrix = T __attribute__((matrix_type(R, C)));

template <int N>
struct selector {};

template <class T, unsigned long R, unsigned long C>
selector<0> use_matrix(matrix<T, R, C> &m) {}

template <class T, unsigned long R>
selector<1> use_matrix(matrix<T, R, 10> &m) {}

template <class T>
selector<2> use_matrix(matrix<T, 10, 10> &m) {}

template <class T, unsigned long C>
selector<3> use_matrix(matrix<T, 10, C> &m) {}

template <unsigned long R, unsigned long C>
selector<4> use_matrix(matrix<float, R, C> &m) {}

void test_template_deduction() {







  matrix<int, 10, 12> m0;
  selector<3> w = use_matrix(m0);
  matrix<int, 10, 10> m1;
  selector<2> x = use_matrix(m1);
  matrix<int, 12, 10> m2;
  selector<1> y = use_matrix(m2);
  matrix<int, 12, 12> m3;
  selector<0> z = use_matrix(m3);
  matrix<float, 12, 12> m4;
  selector<4> v = use_matrix(m4);
}

template <auto R>
void foo(matrix<int, R, 10> &m) {
}

void test_auto_t() {


  matrix<int, 13, 10> m;
  foo(m);
}

template <unsigned long R, unsigned long C>
matrix<float, R + 1, C + 2> use_matrix_2(matrix<int, R, C> &m) {}

template <unsigned long R, unsigned long C>
selector<0> use_matrix_2(matrix<int, R + 2, C / 2> &m1, matrix<float, R, C> &m2) {}

template <unsigned long R, unsigned long C>
selector<1> use_matrix_2(matrix<int, R + C, C> &m1, matrix<float, R, C - R> &m2) {}

template <unsigned long R>
matrix<float, R + R, R - 3> use_matrix_2(matrix<int, R, 10> &m1) {}

template <unsigned long R>
selector<2> use_matrix_3(matrix<int, R - 2, R> &m) {}

void test_use_matrix_2() {






  matrix<int, 4, 6> m1;
  matrix<float, 5, 8> r1 = use_matrix_2(m1);

  matrix<float, 2, 12> m2;
  selector<0> r2 = use_matrix_2(m1, m2);

  matrix<int, 13, 8> m3;
  matrix<float, 5, 3> m4;
  selector<1> r3 = use_matrix_2(m3, m4);

  matrix<int, 5, 10> m5;
  matrix<float, 10, 2> r4 = use_matrix_2(m5);

  selector<2> r5 = use_matrix_3(m1);
}
