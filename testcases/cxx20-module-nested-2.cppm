// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck
export module FOO;
namespace Outer {
class Y;
class Inner {
  class X;
  void Fn (X &, Y &); // #2
};
// CHECK-DAG: void @_ZN5OuterW3FOO5Inner2FnERNS1_1XERNS_S0_1YE(
void Inner::Fn (X &, Y &) {}
}

