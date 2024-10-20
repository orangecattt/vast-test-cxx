// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct D;
struct B {
 virtual D& operator = (const D&);
};
struct D : B { D(); virtual void a(); };
void D::a() {}

// CHECK: @_ZTV1D = {{.*}} @_ZN1DaSERKS_ 
// CHECK: define linkonce_odr {{.*}} @_ZN1DaSERKS_
