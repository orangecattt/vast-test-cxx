// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck
// PR13359

struct X {
  ~X();
};
struct Error {
  Error(const X&) noexcept;
};

void f() {
  try {
    throw Error(X());
  } catch (...) { }
}

// CHECK-LABEL: define{{.*}} void @_Z1fv
// CHECK: call void @_ZN5ErrorC1ERK1X
// CHECK: invoke void @__cxa_throw
// CHECK: landingpad
// CHECK: call void @_ZN1XD1Ev
// CHECK-NOT: __cxa_free_exception
