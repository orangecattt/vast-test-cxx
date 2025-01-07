// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

__attribute__((internal_linkage)) void f() {}

class A {
public:
  static int y __attribute__((internal_linkage));
  static int y2 [[clang::internal_linkage]];
  void f1() __attribute__((internal_linkage));
  void f2() __attribute__((internal_linkage)) {}
  static void f4() __attribute__((internal_linkage)) {}
  A() __attribute__((internal_linkage)) {}
  ~A() __attribute__((internal_linkage)) {}
};

int A::y;
int A::y2;

void A::f1() {
}

class B;

class __attribute__((internal_linkage)) B {
public:
  B() {}
  ~B() {}
  void f() {};
  static int x;
};

int B::x;

class __attribute__((internal_linkage)) C;
class C {
public:
  static int x;
};

int C::x;

__attribute__((internal_linkage)) void g();
void g() {}

void use() {
  A a;
  a.f1();
  a.f2();
  A::f4();
  f();
  int &Y = A::y;
  int &Y2 = A::y2;
  B b;
  b.f();
  int &XX2 = B::x;
  g();
  int &XX3 = C::x;
}
