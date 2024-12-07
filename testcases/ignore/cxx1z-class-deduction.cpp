// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

template<typename T> struct A {
  A(T = 0);
  A(void*);
};

template<typename T> A(T*) -> A<long>;
A() -> A<int>;

void f(int *p) {
  A a{};

  A b = p;

  A c = 123LL;
}

namespace N {
  template<typename T> struct B { B(T); };
}
using N::B;

struct X {
  template<typename T> struct C { C(T); };
};

template<typename T> auto g(T x, decltype(A(x)), A<T>) {}
template<typename T> auto h(T x, decltype(B(x)), B<T>) {}
template<typename U, typename T> auto i(T x, decltype(typename U::C(x)), typename U::template C<T>) {}
void test() {
  g(1, 2, A(3));
  h(1, 2, B(3));
  i<X>(1, 2, X::C(3));
}
