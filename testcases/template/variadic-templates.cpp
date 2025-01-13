// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

template<typename ...Types>
int get_num_types(Types...) {
  return sizeof...(Types);
}

template int get_num_types(int, float, double);

namespace test1 {
  template <class... T> void foo() {
    int values[sizeof...(T)+1] = { T::value... };
  }

  void test() {
    foo<>();
  }
}
