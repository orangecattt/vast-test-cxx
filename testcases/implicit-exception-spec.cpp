// RUN: %driver -cc1 %isys %s -std=c++11 -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck

struct A {
  A();
  A(const A&);
  A(A&&);
};
struct B : virtual A {
  virtual void f() = 0;
};
struct C : B {
  void f();
};

C c1;
C c2(c1);
C c3(static_cast<C&&>(c1));

