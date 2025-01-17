// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

namespace Test1 {
  struct A { virtual ~A() {} };
  struct B final : A {};
  struct C : A { virtual ~C() final {} };
  struct D { virtual ~D() final = 0; };
  void foo(B *b) {
    delete b;
  }
  void foo2(C *c) {
    delete c;
  }
  void evil(D *p) {
    delete p;
  }
}
