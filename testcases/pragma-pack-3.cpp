// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Base {
  char a;
};

struct Derived_1 : virtual Base
{
  char b;
};

#pragma pack(1)
struct Derived_2 : Derived_1 {
  // CHECK: %struct.Derived_2 = type { %struct.Derived_1.base, %struct.Base }
  // CHECK: %struct.Derived_1.base = type <{ ptr, i8 }>
};

Derived_2 x;
