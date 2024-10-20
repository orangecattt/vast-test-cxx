// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct S {};
S f();
struct Z {
  int x;
  [[no_unique_address]] S y;
  Z();
};
Z::Z() : x(111), y(f()) {}




struct S2 {
  S2();
};
struct Z2 {
  int x;
  [[no_unique_address]] S2 y;
  Z2();
};
Z2::Z2() : x(111) {}

