// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct A { virtual ~A(); };
template<typename T> struct B : virtual A {
  ~B() override {}
};
struct C : B<int>, B<float> { C(); ~C() override; };
struct D : C { ~D() override; };

// We must not create a reference to B<int>::~B() here, because we're not going to emit it.
// CHECK-NOT: @_ZN1BIiED1Ev
// CHECK-NOT: @_ZTC1D0_1BIiE =
// CHECK-NOT: @_ZTT1D = available_externally
D *p = new D;
