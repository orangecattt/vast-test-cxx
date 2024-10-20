// RUN: %driver -cc1 %isys -mno-constructor-aliases -mconstructor-aliases %s %target -o %t%output-suffix && %filecheck

// The target attribute code used to get confused with aliases. Make sure
// we don't crash when an alias is used.

struct B {
  B();
};
B::B() {
}

// CHECK: @_ZN1BC1Ev ={{.*}} unnamed_addr alias void (ptr), ptr @_ZN1BC2Ev
// NO-ALIAS-NOT: @_ZN1BC1Ev ={{.*}} unnamed_addr alias void (ptr), ptr @_ZN1BC2Ev
