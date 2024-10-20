// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

struct S {
  S() { printf("S::S\n"); }
};

struct A {
  double x;
  A() : x(), y(), s() { printf("x = %f y = %x \n", x, y); }
  int *y;
  S s;
};

A a;

struct B {
  B() = default;
  B(const B&);
};

static B b;

struct C {
  ~C();
};

static C c[4];

int main() {
}

namespace PR22793 {
template <typename>
struct foo {
protected:
  ~foo() = default;
  friend void func();
};

void func() { foo<int> f; }

template struct foo<int>;
}
