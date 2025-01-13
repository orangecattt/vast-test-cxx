// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


template<typename T, typename U>
T* next(T* ptr, const U& diff);

template<typename T, typename U>
T* next(T* ptr, const U& diff) { 
  return ptr + diff; 
}

void test(int *iptr, float *fptr, int diff) {
  iptr = next(iptr, diff);

  fptr = next(fptr, diff);
}

template<typename T, typename U>
T* next(T* ptr, const U& diff);

void test2(int *iptr, double *dptr, int diff) {
  iptr = next(iptr, diff);

  dptr = next(dptr, diff);
}

namespace PR21904 {
template <typename>
const int &GetData(bool);

template <>
const int &GetData<int>(bool b) {
  static int i = 4;
  if (b) {
    static int i = 2;
    return i;
  }
  return i;
}
}
