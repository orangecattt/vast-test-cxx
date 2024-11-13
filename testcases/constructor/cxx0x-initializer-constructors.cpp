// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct S {
  S(int x) { }
  S(int x, double y, double z) { }
};

void fn1() {
  S s { 1 };
}

void fn2() {
  S s { 1, 2.0, 3.0 };
}

void fn3() {
  S sa[] { { 1 }, { 2 }, { 3 } };
}

void fn4() {
  S sa[] { { 1, 2.0, 3.0 }, { 4, 5.0, 6.0 } };
}

namespace TreeTransformBracedInit {
  struct S {};
  struct T { T(const S &); T(const T&); ~T(); };
  void x(const T &);
  template<typename> void foo(const S &s) {
    x({s});
  }
  template void foo<void>(const S&);
}
