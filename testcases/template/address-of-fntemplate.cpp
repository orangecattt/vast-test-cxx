// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
template <typename T> void f(T) {}
template <typename T> void f() { }

void test() {
  void (*p)(int) = &f;
  
  void (*p2)() = f<int>;
}

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
