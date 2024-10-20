// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A;

struct B {
  virtual void f();
  virtual A g();
};

void B::f() { }

// CHECK-LABEL: define{{.*}} i32 @_ZN1D1gEv(ptr {{[^,]*}} %this)
// CHECK: declare void @_ZN1B1gEv()

struct C;

struct D {
  virtual void f();
  virtual C g();
};

void D::f() { }

struct C {
  int a;
};

C D::g() {
  return C();
}
