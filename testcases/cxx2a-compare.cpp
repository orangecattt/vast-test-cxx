// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

#include "Inputs/std-compare.h"


auto test_signed(int x, int y) {
  return x <=> y;
}

auto test_unsigned(unsigned x, unsigned y) {
  return x <=> y;
}

auto float_test(double x, double y) {
  return x <=> y;
}

auto ptr_test(int *x, int *y) {
  return x <=> y;
}

auto test_constant() {
  const int x = 42;
  const int y = 101;
  return x <=> y;
}

void unscoped_enum_test(int i, unsigned u, long long l, unsigned long long ul) {
  enum EnumA : int { A };
  enum EnumB : unsigned { B };
  (void)(A <=> i);

  (void)(A <=> u);

  (void)(A <=> l);

  (void)(B <=> u);

  (void)(B <=> ul);
}
