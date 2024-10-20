// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

template<typename ...Types>
int get_num_types(Types...) {
  return sizeof...(Types);
}

// CHECK-LABEL: define weak_odr noundef i32 @_Z13get_num_typesIJifdEEiDpT_
// CHECK: ret i32 3
template int get_num_types(int, float, double);

// PR10260 - argument packs that expand to nothing
namespace test1 {
  template <class... T> void foo() {
    int values[sizeof...(T)+1] = { T::value... };
    // CHECK-LABEL: define linkonce_odr void @_ZN5test13fooIJEEEvv()
    // CHECK: alloca [1 x i32], align 4
  }

  void test() {
    foo<>();
  }
}
