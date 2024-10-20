// RUN: %driver -cc1 %isys %s -fno-rtti %target -o %t%output-suffix && %filecheck
// expected-no-diagnostics

struct A {
  virtual ~A(){};
};

struct B : public A {
  B() : A() {}
};

// An upcast can be resolved statically and can be used with -fno-rtti, iff it
// does not use runtime support.
A *upcast(B *b) {
  return dynamic_cast<A *>(b);
// CHECK-LABEL: define {{.*}}ptr @_Z6upcastP1B
// CHECK-NOT: call {{.*}}ptr @__dynamic_cast
}

// A NoOp dynamic_cast can be used with -fno-rtti iff it does not use
// runtime support.
B *samecast(B *b) {
  return dynamic_cast<B *>(b);
// CHECK-LABEL: define {{.*}}ptr @_Z8samecastP1B
// CHECK-NOT: call {{.*}}ptr @__dynamic_cast
}