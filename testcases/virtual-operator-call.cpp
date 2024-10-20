// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  virtual int operator-();
};

void f(A a, A *ap) {
  // CHECK: call noundef i32 @_ZN1AngEv(ptr {{[^,]*}} %a)
  -a;

  // CHECK: call noundef i32 %
  -*ap;
}
