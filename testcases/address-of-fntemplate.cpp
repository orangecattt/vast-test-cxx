// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
template <typename T> void f(T) {}
template <typename T> void f() { }

void test() {
  // CHECK: @_Z1fIiEvT_
  void (*p)(int) = &f;
  
  // CHECK: @_Z1fIiEvv
  void (*p2)() = f<int>;
}
// CHECK-LABEL: define linkonce_odr {{.*}}void @_Z1fIiEvT_
// CHECK-LABEL: define linkonce_odr {{.*}}void @_Z1fIiEvv

namespace PR6973 {
  template<typename T>
  struct X {
    void f(const T&);
  };

  template<typename T>
  int g();

  void h(X<int (*)()> xf) {
    xf.f(&g<int>);
  }
}
