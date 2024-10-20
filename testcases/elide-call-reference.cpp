// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// PR5695

struct A { A(const A&); ~A(); };
A& a();
void b() {
  A x = a();
}

// CHECK: call {{.*}} @_ZN1AC1ERKS_
// CHECK: call {{.*}} @_ZN1AD1Ev
