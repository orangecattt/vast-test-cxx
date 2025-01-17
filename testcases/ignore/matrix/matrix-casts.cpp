// RUN: %driver -cc1 %isys -std=c++11 -fenable-matrix %s %target -o %t%output-suffix && %filecheck

template <typename X>
using matrix_4_4 = X __attribute__((matrix_type(4, 4)));

template <typename Y>
using matrix_5_5 = Y __attribute__((matrix_type(5, 5)));

void CastCharMatrixToIntCStyle() {

  matrix_5_5<char> c;
  matrix_5_5<int> i;
  i = (matrix_5_5<int>)c;
}

void CastCharMatrixToIntStaticCast() {

  matrix_5_5<char> c;
  matrix_5_5<int> i;
  i = static_cast<matrix_5_5<int>>(c);
}

void CastCharMatrixToUnsignedIntCStyle() {

  matrix_5_5<char> c;
  matrix_5_5<unsigned int> u;
  u = (matrix_5_5<unsigned int>)c;
}

void CastCharMatrixToUnsignedIntStaticCast() {

  matrix_5_5<char> c;
  matrix_5_5<unsigned int> u;
  u = static_cast<matrix_5_5<unsigned int>>(c);
}

void CastUnsignedLongIntMatrixToShortCStyle() {

  matrix_5_5<unsigned long int> u;
  matrix_5_5<short int> s;
  s = (matrix_5_5<short int>)u;
}

void CastUnsignedLongIntMatrixToShortStaticCast() {

  matrix_5_5<unsigned long int> u;
  matrix_5_5<short int> s;
  s = static_cast<matrix_5_5<short int>>(u);
}

void CastIntMatrixToShortCStyle() {

  matrix_5_5<int> i;
  matrix_5_5<short int> s;
  s = (matrix_5_5<short int>)i;
}

void CastIntMatrixToShortStaticCast() {

  matrix_5_5<int> i;
  matrix_5_5<short int> s;
  s = static_cast<matrix_5_5<short int>>(i);
}

void CastIntMatrixToFloatCStyle() {

  matrix_5_5<int> i;
  matrix_5_5<float> f;
  f = (matrix_5_5<float>)i;
}

void CastIntMatrixToFloatStaticCast() {

  matrix_5_5<int> i;
  matrix_5_5<float> f;
  f = static_cast<matrix_5_5<float>>(i);
}

void CastUnsignedIntMatrixToFloatCStyle() {

  matrix_5_5<unsigned short int> u;
  matrix_5_5<float> f;
  f = (matrix_5_5<float>)u;
}

void CastUnsignedIntMatrixToFloatStaticCast() {

  matrix_5_5<unsigned short int> u;
  matrix_5_5<float> f;
  f = static_cast<matrix_5_5<float>>(u);
}

void CastDoubleMatrixToIntCStyle() {

  matrix_5_5<double> d;
  matrix_5_5<int> i;
  i = (matrix_5_5<int>)d;
}

void CastDoubleMatrixToIntStaticCast() {

  matrix_5_5<double> d;
  matrix_5_5<int> i;
  i = static_cast<matrix_5_5<int>>(d);
}

void CastFloatMatrixToUnsignedShortIntCStyle() {

  matrix_5_5<float> f;
  matrix_5_5<unsigned short int> i;
  i = (matrix_5_5<unsigned short int>)f;
}

void CastFloatMatrixToUnsignedShortIntStaticCast() {

  matrix_5_5<float> f;
  matrix_5_5<unsigned short int> i;
  i = static_cast<matrix_5_5<unsigned short int>>(f);
}

void CastDoubleMatrixToFloatCStyle() {

  matrix_5_5<double> d;
  matrix_5_5<float> f;
  f = (matrix_5_5<float>)d;
}

void CastDoubleMatrixToFloatStaticCast() {

  matrix_5_5<double> d;
  matrix_5_5<float> f;
  f = static_cast<matrix_5_5<float>>(d);
}

void CastUnsignedShortIntToUnsignedIntCStyle() {

  matrix_5_5<unsigned short int> s;
  matrix_5_5<unsigned int> i;
  i = (matrix_5_5<unsigned int>)s;
}

void CastUnsignedShortIntToUnsignedIntStaticCast() {

  matrix_5_5<unsigned short int> s;
  matrix_5_5<unsigned int> i;
  i = static_cast<matrix_5_5<unsigned int>>(s);
}

void CastUnsignedLongIntToUnsignedShortIntCStyle() {

  matrix_5_5<unsigned long int> l;
  matrix_5_5<unsigned short int> s;
  s = (matrix_5_5<unsigned short int>)l;
}

void CastUnsignedLongIntToUnsignedShortIntStaticCast() {

  matrix_5_5<unsigned long int> l;
  matrix_5_5<unsigned short int> s;
  s = static_cast<matrix_5_5<unsigned short int>>(l);
}

void CastUnsignedShortIntToIntCStyle() {

  matrix_5_5<unsigned short int> u;
  matrix_5_5<int> i;
  i = (matrix_5_5<int>)u;
}

void CastUnsignedShortIntToIntStaticCast() {

  matrix_5_5<unsigned short int> u;
  matrix_5_5<int> i;
  i = static_cast<matrix_5_5<int>>(u);
}

void CastIntToUnsignedLongIntCStyle() {

  matrix_5_5<int> i;
  matrix_5_5<unsigned long int> u;
  u = (matrix_5_5<unsigned long int>)i;
}

void CastIntToUnsignedLongIntStaticCast() {

  matrix_5_5<int> i;
  matrix_5_5<unsigned long int> u;
  u = static_cast<matrix_5_5<unsigned long int>>(i);
}

class Foo {
  int x[10];

public:
  Foo(matrix_5_5<int> x);
};

Foo class_constructor_matrix_ty(matrix_5_5<int> m) {

  return Foo(m);
}

struct Bar {
  float x[10];
  Bar(matrix_4_4<float> x);
};

Bar struct_constructor_matrix_ty(matrix_4_4<float> m) {

  return Bar(m);
}
