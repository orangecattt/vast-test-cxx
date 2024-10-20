// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct D;
struct B {
 virtual D &operator=(D&&) = 0;
};
struct D : B { D(); virtual void a(); };
void D::a() {}
D d;

// CHECK: @_ZTV1D = {{.*}} @_ZN1DaSEOS_ 
// CHECK: define linkonce_odr {{.*}} @_ZN1DaSEOS_
