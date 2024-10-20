// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Check that we don't emit the complete constructor/destructor for this class.
struct A {
  virtual void f() = 0;
  A();
  ~A();
};

// CHECK-NOT: define{{.*}} void @_ZN1AC1Ev
// CHECK-LABEL: define{{.*}} void @_ZN1AC2Ev
// CHECK-LABEL: define{{.*}} void @_ZN1AD2Ev
// CHECK-LABEL: define{{.*}} void @_ZN1AD1Ev
A::A() { }

A::~A() { }
