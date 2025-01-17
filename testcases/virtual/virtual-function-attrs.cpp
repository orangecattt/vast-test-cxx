// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

class A {
  virtual void f();
  virtual void g();
  virtual ~A();
};

void A::f() {}

