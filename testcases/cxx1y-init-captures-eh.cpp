// RUN: %driver -cc1 %isys -std=c++1y -fexceptions -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck

struct S {
  S();
  ~S();
};

struct T {
  T() noexcept;
  ~T();
  int n;
};

void f() {
  [s = S()] {}, throw 0;

}

void g() {
  [s = S(), t = (throw 0, 1)] {};

}

void x() noexcept;
void y() noexcept;

void h(bool b1, bool b2) {










  [s = S(), t = T().n, u = (b1 ? throw 1 : 42)] {}, (b2 ? throw 2 : 0), x();
  y();

}
