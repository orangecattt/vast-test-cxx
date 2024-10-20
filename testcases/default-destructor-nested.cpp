// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// PR6294

class A {
public: virtual ~A();
};
class B {
  class C;
};
class B::C : public A {
  C();
};
B::C::C() {}
