// REQUIRES: asserts
// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// This test simply checks that the varargs thunk is created. The failing test
// case asserts.

struct Alpha {
  virtual void bravo(...);
};
struct Charlie {
  virtual ~Charlie() {}
};
struct CharlieImpl : Charlie, Alpha {
  void bravo(...) {}
} delta;

// CHECK: define {{.*}} void @_ZThn{{[48]}}_N11CharlieImpl5bravoEz(
