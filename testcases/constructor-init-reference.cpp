// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int x;
struct A {
  int& y;
  A() : y(x) {}
};
A z;
// CHECK: store ptr @x, ptr
