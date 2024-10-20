// RUN: %driver -cc1 %isys -std=c++11 -fblocks %s %target -o %t%output-suffix && %filecheck

namespace N {
  typedef void (^BL)();
  int func(BL, BL, BL);

// CHECK-LABEL: define internal void @_ZN1N8ArrBlockE_block_invoke(
// CHECK-LABEL: define internal void @_ZN1N8ArrBlockE_block_invoke_2(
// CHECK-LABEL: define internal void @_ZN1N8ArrBlockE_block_invoke_3
  BL ArrBlock [] = { ^{}, ^{}, ^{} };

// CHECK-LABEL: define internal void @_ZN1N4ivalE_block_invoke_4(
// CHECK-LABEL: define internal void @_ZN1N4ivalE_block_invoke_5(
// CHECK-LABEL: define internal void @_ZN1N4ivalE_block_invoke_6(
  int ival = func(^{}, ^{}, ^{});

// CHECK-LABEL: define internal void @_ZN1N9gvarlobalE_block_invoke_7(
  void (^gvarlobal)(void) = ^{};

  struct S {
    BL field = ^{};
  };

// CHECK-LABEL: define internal void @_ZN1N3blfE_block_invoke_8(
  S blf;
};
