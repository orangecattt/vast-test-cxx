// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

export module FOO.BAR;
export class A;
namespace Bob {
export class B;

export void Bar (A *, B*) {
}
}

export void Foo (A *, Bob::B*) {
}
