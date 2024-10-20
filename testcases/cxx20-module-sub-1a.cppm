// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

export module FOO.BAR;
export class A;
namespace Bob {
export class B;

// CHECK-DAG: void @_ZN3BobW3FOOW3BAR3BarEPS1_1APNS_S1_1BE(
export void Bar (A *, B*) {
}
}

// CHECK-DAG: void @_ZW3FOOW3BAR3FooPS0_1APN3BobS0_1BE(
export void Foo (A *, Bob::B*) {
}
