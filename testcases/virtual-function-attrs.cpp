// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

class A {
  virtual void f();
  virtual void g();
  virtual ~A();
};

void A::f() {}

// CHECK: define {{(dso_local )?}}[[CC:(x86_thiscallcc )?]]void @_ZN1A1fEv({{.*}}) unnamed_addr
// CHECK: declare {{(dso_local )?}}[[CC]]void @_ZN1A1gEv({{.*}}) unnamed_addr
// CHECK: declare {{.*}} @_ZN1AD1Ev({{.*}}) unnamed_addr
// CHECK: declare {{(dso_local )?}}[[CC]]void @_ZN1AD0Ev({{.*}}) unnamed_addr
