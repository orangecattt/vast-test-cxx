// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

struct A { ~A(); int n; char c[3]; };
struct B { [[no_unique_address]] A a; char k; };
B b = {1, 2, 3, 4, 5};

struct C : A {};
struct D : C {};
struct E { int e; [[no_unique_address]] D d; char k; };
E e = {1, 2, 3, 4, 5, 6};

struct Empty1 {};
struct Empty2 {};
struct Empty3 {};
struct HasEmpty {
  [[no_unique_address]] Empty1 e1;
  int a;
  [[no_unique_address]] Empty2 e2;
  int b;
  [[no_unique_address]] Empty3 e3;
};
HasEmpty he = {{}, 1, {}, 2, {}};

struct HasEmptyDuplicates {
  [[no_unique_address]] Empty1 e1; // +0
  int a;
  [[no_unique_address]] Empty1 e2; // +4
  int b;
  [[no_unique_address]] Empty1 e3; // +8
};
Empty1 HasEmptyDuplicates::*off1 = &HasEmptyDuplicates::e1;
Empty1 HasEmptyDuplicates::*off2 = &HasEmptyDuplicates::e2;
Empty1 HasEmptyDuplicates::*off3 = &HasEmptyDuplicates::e3;

HasEmptyDuplicates hed = {{}, 1, {}, 2, {}};

struct __attribute__((packed, aligned(2))) PackedAndPadded {
  ~PackedAndPadded();
  char c;
  int n;
};
struct WithPackedAndPadded {
  [[no_unique_address]] PackedAndPadded pap;
  char d;
};
WithPackedAndPadded wpap = {1, 2, 3};

struct FieldOverlap {
  [[no_unique_address]] Empty1 e1, e2, e3, e4;
  int n;
};
static_assert(sizeof(FieldOverlap) == 4);
FieldOverlap fo = {{}, {}, {}, {}, 1234};

Empty1 &e1 = fo.e1;
Empty1 &e2 = fo.e2;

Empty1 &accessE1(FieldOverlap &fo) { return fo.e1; }

Empty1 &accessE2(FieldOverlap &fo) { return fo.e2; }

struct LaterDeclaredFieldHasLowerOffset {
  int a;
  int b;
  [[no_unique_address]] Empty1 e;
};
int loadWhereLaterDeclaredFieldHasLowerOffset(LaterDeclaredFieldHasLowerOffset &a) {
  return a.b;
}

struct NonTrivialInit {
  NonTrivialInit();
};
struct HasZeroSizedFieldWithNonTrivialInit {
  int a;
  [[no_unique_address]] NonTrivialInit b;
};
HasZeroSizedFieldWithNonTrivialInit testHasZeroSizedFieldWithNonTrivialInit = {.a = 1};
