// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++98 -fexceptions -fcxx-exceptions %target -o %t%output-suffix && %filecheck

struct A {
  A();
  ~A();
};

struct B {
  B(A = A());
  ~B();
};

void f();
// CHECK-LABEL: define {{(dso_local )?}}void @_Z1gv()
void g() {
  // CHECK: br label %[[LOOP:.*]]

  // [[LOOP]]:
  // CHECK: {{call|invoke}} {{.*}} @_ZN1AC1Ev({{.*}} [[TEMPORARY:%.*]])
  // CHECK-EH:  unwind label %[[PARTIAL_ARRAY_LPAD:.*]]
  // CHECK: {{call|invoke}} {{.*}} @_ZN1BC1E1A({{.*}} [[TEMPORARY]])
  // CHECK-EH:  unwind label %[[A_AND_PARTIAL_ARRAY_LPAD:.*]]
  // CHECK: {{call|invoke}} {{.*}} @_ZN1AD1Ev({{.*}} [[TEMPORARY]])
  // CHECK-EH:  unwind label %[[PARTIAL_ARRAY_LPAD]]
  // CHECK: getelementptr {{.*}}, i{{[0-9]*}} 1
  // CHECK: icmp eq
  // CHECK: br i1 {{.*}} label %[[LOOP]]
  B b[5];

  // CHECK: {{call|invoke}} void @_Z1fv()
  f();

  // CHECK-NOT: @_ZN1AD1Ev(
  // CHECK: {{call|invoke}} {{.*}} @_ZN1BD1Ev(
}
