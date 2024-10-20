// RUN: %driver -cc1 %isys -fms-extensions %s -o- %target -o %t%output-suffix && %filecheck

struct A {
  void foo() __unaligned;
  void foo() const __unaligned;
  void foo() volatile __unaligned;
  void foo() const volatile __unaligned;
};

void A::foo() __unaligned {}
// CHECK: define {{(dso_local )?}}[[THISCALL:(x86_thiscallcc )?]]void @_ZNU11__unaligned1A3fooEv(

void A::foo() const __unaligned {}
// CHECK: define {{(dso_local )?}}[[THISCALL]]void @_ZNU11__unalignedK1A3fooEv(

void A::foo() volatile __unaligned {}
// CHECK: define {{(dso_local )?}}[[THISCALL]]void @_ZNU11__unalignedV1A3fooEv(

void A::foo() const volatile __unaligned {}
// CHECK: define {{(dso_local )?}}[[THISCALL]]void @_ZNU11__unalignedVK1A3fooEv(
