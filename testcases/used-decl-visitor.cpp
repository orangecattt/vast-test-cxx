// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Make sure there is no assertion due to UsedDeclVisitor.

struct A {
  int a;
};

static A a;

struct B {
  B(int b = a.a) {}
};


void foo() {
  B();
}
