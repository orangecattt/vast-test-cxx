// RUN: %driver -cc1 %isys %s -mconstructor-aliases %target -o %t%output-suffix && %filecheck

struct A { 
  A();
};

A::A() { }

struct B : virtual A { 
  B();
};

B::B() { }

struct C : virtual A {
  C(bool);
};

C::C(bool) { }

namespace PR6251 {


template<typename T>
struct A { A(); };

struct B : virtual A<char> { };
struct C : virtual A<char> { };

struct D : B, C  {
  D();
};

D::D() { }

}

namespace virtualBaseAlignment {




struct A {
  __attribute__((aligned(16))) double data1;
};

struct B : public virtual A {
  B() : x(123) {}
  double a;
  int x;
};

struct C : public virtual B {};

void test() { B b; C c; }

}
