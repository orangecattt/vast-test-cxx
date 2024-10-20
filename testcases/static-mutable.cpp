// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct S {
  mutable int n;
};
int f() {
  // The purpose of this test is to ensure that this variable is a global
  // not a constant.
  // CHECK: @_ZZ1fvE1s = internal global {{.*}} { i32 12 }
  static const S s = { 12 };
  return ++s.n;
}
