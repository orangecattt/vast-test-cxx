// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { int i; };
struct B { char j; };
struct C : A, B { int k; };

struct D final : virtual C { 
  D(); 
  virtual void f();
};

// CHECK-LABEL: define {{.*}}dereferenceable({{[0-9]+}}) ptr @_Z1fR1D
B &f(D &d) {
  // CHECK-NOT: load ptr, ptr %{{[0-9]+}}
  return d;
}
