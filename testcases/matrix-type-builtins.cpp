// RUN: %driver -cc1 %isys -fenable-matrix %s -std=c++17 %target -o %t%output-suffix && %filecheck


template <typename EltTy, unsigned Rows, unsigned Columns>
using matrix_t = EltTy __attribute__((matrix_type(Rows, Columns)));

template <typename EltTy, unsigned Rows, unsigned Columns>
struct MyMatrix {
  matrix_t<EltTy, Rows, Columns> value;
};

template <typename T, unsigned R, unsigned C>
MyMatrix<T, C, R> transpose(const MyMatrix<T, R, C> &M) {
  MyMatrix<T, C, R> Res;
  Res.value = __builtin_matrix_transpose(M.value);
  return Res;
}

void test_transpose_template1() {


  MyMatrix<int, 4, 10> M1;
  MyMatrix<int, 10, 4> M1_t = transpose(M1);
}

void test_transpose_template2(MyMatrix<double, 7, 6> &M) {



  MyMatrix<double, 6, 7> M2_t = transpose(transpose(transpose(M)));
}

matrix_t<float, 3, 3> get_matrix();

void test_transpose_rvalue() {
  matrix_t<float, 3, 3> m_t = __builtin_matrix_transpose(get_matrix() + 2.0);
}

void test_transpose_const(const matrix_t<float, 3, 3> &m) {
  matrix_t<float, 3, 3> m_t = __builtin_matrix_transpose(m);
}


template <typename T, unsigned R, unsigned C, unsigned S>
matrix_t<T, R, C> column_major_load_with_stride(T *Ptr) {
  return __builtin_matrix_column_major_load(Ptr, R, C, S);
}

void test_column_major_load_with_stride_template_double(double *Ptr) {


  matrix_t<double, 10, 4> M1 = column_major_load_with_stride<double, 10, 4, 15>(Ptr);
}

void test_column_major_load_with_stride_template_int(int *Ptr) {


  matrix_t<int, 3, 2> M1 = column_major_load_with_stride<int, 3, 2, 12>(Ptr);
}

struct UnsignedWrapper {
  char x;
  operator unsigned() {
    return x;
  }
};

void test_column_major_load_stride_wrapper(int *Ptr, UnsignedWrapper &W) {
  matrix_t<int, 2, 2> M1 = __builtin_matrix_column_major_load(Ptr, 2, 2, W);
}

constexpr int constexpr3() { return 3; }

void test_column_major_load_constexpr_num_rows(int *Ptr) {

  matrix_t<int, 3, 2> M1 = __builtin_matrix_column_major_load(Ptr, constexpr3(), 2, 3);
}

constexpr int constexpr1() { return 1; }

void test_column_major_load_constexpr_num_columns(int *Ptr) {
  matrix_t<int, 2, 1> M1 = __builtin_matrix_column_major_load(Ptr, 2, constexpr1(), 3);
}

template <unsigned N>
constexpr int constexpr_plus1() { return N + 1; }

void test_column_major_load_constexpr_num_columns_temp(int *Ptr) {
  matrix_t<int, 2, 5> M1 = __builtin_matrix_column_major_load(Ptr, 2, constexpr_plus1<4>(), 3);
}

void test_column_major_load_constexpr_stride_constexpr(int *Ptr) {

  matrix_t<int, 2, 2> M1 = __builtin_matrix_column_major_load(Ptr, 2, 2, constexpr3());
}

template <typename T>
struct remove_pointer {
  typedef T type;
};

template <typename T>
struct remove_pointer<T *> {
  typedef typename remove_pointer<T>::type type;
};

template <typename PtrT, unsigned R, unsigned C, unsigned S>
matrix_t<typename remove_pointer<PtrT>::type, R, C> column_major_load_with_stride2(PtrT Ptr) {
  return __builtin_matrix_column_major_load(Ptr, R, C, S);
}

void call_column_major_load_with_stride2(float *Ptr) {
  matrix_t<float, 2, 2> m = column_major_load_with_stride2<float *, 2, 2, 2>(Ptr);
}

template <typename T, unsigned R, unsigned C, unsigned S>
void column_major_store_with_stride(matrix_t<T, R, C> &m, T *Ptr) {
  __builtin_matrix_column_major_store(m, Ptr, S);
}

void test_column_major_store_with_stride_template_double(double *Ptr) {


  matrix_t<double, 10, 4> M1;
  column_major_store_with_stride<double, 10, 4, 15>(M1, Ptr);
}

void test_column_major_store_with_stride_template_int(int *Ptr) {


  matrix_t<int, 3, 2> M1;
  column_major_store_with_stride<int, 3, 2, 3>(M1, Ptr);
}

void test_column_major_store_stride_wrapper(int *Ptr, UnsignedWrapper &W) {

  matrix_t<int, 2, 2> M1;
  __builtin_matrix_column_major_store(M1, Ptr, W);
}

void test_column_major_store_constexpr_stride_constexpr(int *Ptr) {

  matrix_t<int, 2, 2> M;
  __builtin_matrix_column_major_store(M, Ptr, constexpr3());
}
