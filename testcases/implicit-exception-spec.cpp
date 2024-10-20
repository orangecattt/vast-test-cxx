// RUN: %driver -cc1 %isys %s -std=c++11 -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck

struct A {
  A();
  A(const A&);
  A(A&&);
};
struct B : virtual A {
  virtual void f() = 0;
};
struct C : B {
  void f();
};

// CHECK-DAG: define {{.*}} @_ZN1BC2Ev({{.*}} #[[NOUNWIND:[0-9]*]]
C c1;
// CHECK-DAG: define {{.*}} @_ZN1BC2ERKS_({{.*}} #[[NOUNWIND]]
C c2(c1);
// CHECK-DAG: define {{.*}} @_ZN1BC2EOS_({{.*}} #[[NOUNWIND]]
C c3(static_cast<C&&>(c1));

// CHECK-DAG: #[[NOUNWIND]] = {{{.*}} nounwind
