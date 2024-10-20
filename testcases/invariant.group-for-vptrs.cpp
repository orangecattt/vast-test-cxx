// RUN: %driver -cc1 %isys %s -fstrict-vtable-pointers %target -o %t%output-suffix && %filecheck

struct A {
  virtual void foo();
};

struct D : A {
  void foo();
};

// CHECK-LABEL: define{{.*}} void @_Z21testExternallyVisiblev()
void testExternallyVisible() {
  A *a = new A;

  // CHECK: load {{.*}} !invariant.group ![[MD:[0-9]+]]
  a->foo();

  D *d = new D;
  // CHECK: call void @_ZN1DC1Ev(
  // CHECK: load {{.*}} !invariant.group ![[MD]]
  d->foo();
  A *a2 = d;
  // CHECK: load {{.*}} !invariant.group ![[MD]]
  a2->foo();
}
// CHECK-LABEL: {{^}}}

namespace {

struct B {
  virtual void bar();
};

struct C : B {
  void bar();
};

}

// CHECK-LABEL: define{{.*}} void @_Z21testInternallyVisibleb(
void testInternallyVisible(bool p) {
  B *b = new B;
  // CHECK: = load {{.*}}, !invariant.group ![[MD]]
  b->bar();

  // CHECK: call void @_ZN12_GLOBAL__N_11CC1Ev(
  C *c = new C;
  // CHECK: = load {{.*}}, !invariant.group ![[MD]]
  c->bar();
}

// Checking A::A()
// CHECK-LABEL: define linkonce_odr void @_ZN1AC2Ev(
// CHECK: store {{.*}}, !invariant.group ![[MD]]
// CHECK-LABEL: {{^}}}

// Checking D::D()
// CHECK-LABEL: define linkonce_odr void @_ZN1DC2Ev(
// CHECK:  = call ptr @llvm.launder.invariant.group.p0(ptr
// CHECK:  call void @_ZN1AC2Ev(ptr
// CHECK: store {{.*}} !invariant.group ![[MD]]

// Checking B::B()
// CHECK-LABEL: define internal void @_ZN12_GLOBAL__N_11BC2Ev(
// CHECK:  store {{.*}}, !invariant.group ![[MD]]

// Checking C::C()
// CHECK-LABEL: define internal void @_ZN12_GLOBAL__N_11CC2Ev(
// CHECK:  store {{.*}}, !invariant.group ![[MD]]

// CHECK: ![[MD]] = !{}
