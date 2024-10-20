// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck


struct S1 {
  ~S1();
};
struct S2 {
  ~S2();
};

struct Base {
  Base(const S1&, const S2&, const char *fmt, ...) {}
};

struct NonTrivialDtor {
  ~NonTrivialDtor() {}
};
struct Inheritor : public NonTrivialDtor, public Base {
  using Base::Base;
};

void f() {
  Inheritor(S1(), S2(), "foo");



}
