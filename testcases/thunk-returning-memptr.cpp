// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct X;
typedef void (X::*memptr)();

struct A {
  virtual memptr f();
};

struct B {
  virtual memptr f();
};

struct C : A, B {
  C();
  memptr f() override __attribute__((noinline)) { return nullptr; };
};

C::C() {}

// Make sure the member pointer is returned from the thunk via the return slot.
// Because of the tail call, the return value cannot be copied into a local
// alloca. (PR39901)

// CHECK-LABEL: define linkonce_odr void @_ZThn4_N1C1fEv(ptr dead_on_unwind noalias writable sret({ i32, i32 }) align 4 %agg.result, ptr noundef %this)
// CHECK: tail call void @_ZN1C1fEv(ptr dead_on_unwind writable sret({ i32, i32 }) align 4 %agg.result
