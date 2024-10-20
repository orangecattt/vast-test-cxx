// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck
export module FOO;
namespace Outer {
class Y;
class Inner {
  class X;
  void Fn (X &, Y &); // #2
};
void Inner::Fn (X &, Y &) {}
}

