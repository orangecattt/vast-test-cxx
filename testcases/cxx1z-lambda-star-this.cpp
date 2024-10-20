// RUN: %driver -cc1 %isys -std=c++1y %s %target -o %t%output-suffix && %filecheck
struct A {
  double a = 111;
  auto foo() { return [*this] { return a; }; }
};

namespace ns1 {
int X = A{}.foo()();
} //end ns1


struct B {
  double b = 222;
  auto bar() { return [this] { return b; }; };
};

namespace ns2 {
int X = B{}.bar()();
}
