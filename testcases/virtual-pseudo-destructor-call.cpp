// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  virtual ~A();
};

void f(A *a) {
  // CHECK: define {{.*}} @_Z1fP1A
  // CHECK: load
  // CHECK: load
  // CHECK: [[CALLEE:%[a-zA-Z0-9.]*]] = load
  // CHECK: call {{.*}} [[CALLEE]](
  a->~A();
}
