// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template <class T>
void CheckIntScalarTypes() {

  typedef T __attribute__((mode(QI))) T1;
  typedef T __attribute__((mode(HI))) T2;
  typedef T __attribute__((mode(SI))) T3;
  typedef T __attribute__((mode(DI))) T4;

  T1 a1;
  T2 a2;
  T3 a3;
  T4 a4;
}

template <class T>
void CheckIntVectorTypes() {

  typedef int __attribute__((mode(QI))) __attribute__((vector_size(8)))  VT_11;
  typedef T   __attribute__((mode(V8QI)))                                VT_12;
  typedef int __attribute__((mode(SI))) __attribute__((vector_size(16))) VT_21;
  typedef T   __attribute__((mode(V4SI)))                                VT_22;
  typedef int __attribute__((mode(DI))) __attribute__((vector_size(64))) VT_31;
  typedef T   __attribute__((mode(V8DI)))                                VT_32;

  VT_11 v11;
  VT_12 v12;

  VT_21 v21;
  VT_22 v22;

  VT_31 v31;
  VT_32 v32;
}

template <class T>
void CheckFloatVectorTypes() {

  typedef float __attribute__((mode(SF))) __attribute__((vector_size(128))) VT_41;
  typedef T     __attribute__((mode(V32SF)))                                VT_42;
  typedef float __attribute__((mode(DF))) __attribute__((vector_size(256))) VT_51;
  typedef T     __attribute__((mode(V32DF)))                                VT_52;

  VT_41 v41;
  VT_42 v42;

  VT_51 v51;
  VT_52 v52;
}

template <class T>
void CheckInstantiationWithModedType() {
  T x1;
}

typedef enum { A1, B1 }                       EnumTy;
typedef int __attribute__((mode(DI)))         Int64Ty1;
typedef enum __attribute__((mode(DI))) { A2 } Int64Ty2;
typedef int __attribute__((mode(V8HI)))       IntVecTy1;

void test() {

  CheckIntScalarTypes<int>();

  CheckIntScalarTypes<EnumTy>();

  CheckIntVectorTypes<int>();

  CheckFloatVectorTypes<float>();

  CheckInstantiationWithModedType<Int64Ty1>();

  CheckInstantiationWithModedType<Int64Ty2>();

  CheckInstantiationWithModedType<IntVecTy1>();
}
