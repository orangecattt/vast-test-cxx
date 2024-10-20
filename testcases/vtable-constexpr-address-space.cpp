// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

// constexpr virtual functions can be called at runtime and go in the vtable as
// normal. But they are implicitly inline so are never the key function.

struct DoNotEmit {
  virtual constexpr void f();
};
constexpr void DoNotEmit::f() {}

// CHECK-DAG: @_ZTV1B = {{.*}} addrspace(1) constant { [3 x ptr addrspace(1)] } { {{.*}} null, {{.*}} @_ZTI1B, {{.*}} @_ZN1B1fEv
struct B {
  // CHECK-DAG: define {{.*}} @_ZN1B1fEv
  virtual constexpr void f() {}
};
B b;

struct CBase {
  virtual constexpr void f(); // not key function
};

// CHECK-DAG: @_ZTV1C = {{.*}} addrspace(1) constant {{.*}} null, {{.*}} @_ZTI1C, {{.*}} @_ZN1C1fEv
struct C : CBase {
  void f(); // key function
};
// CHECK-DAG: define {{.*}} @_ZN1C1fEv
void C::f() {}
