// RUN: %driver -cc1 %isys -fsymbol-partition=foo %s %target -o %t%output-suffix && %filecheck

// CHECK: @gv = {{.*}}, partition "foo"
// CHECK: @_ZTV1S = {{.*}}, partition "foo"
// CHECK: @_ZTS1S = {{.*}}, partition "foo"
// CHECK: @_ZTI1S = {{.*}}, partition "foo"

// CHECK: @_Z5ifuncv = {{.*}}, partition "foo"

// CHECK: define {{.*}} @_ZN1S1fEv({{.*}} partition "foo"
// CHECK: define {{.*}} @f({{.*}} partition "foo"

struct S {
  virtual void f();
};

void S::f() {}

int gv;
extern "C" void *f() { return 0; }
void ifunc() __attribute__((ifunc("f")));
