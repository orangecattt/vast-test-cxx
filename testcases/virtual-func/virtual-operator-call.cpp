// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  virtual int operator-();
};

void f(A a, A *ap) {
  -a;

  -*ap;
}
