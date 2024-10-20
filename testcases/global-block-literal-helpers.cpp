// RUN: %driver -cc1 %isys -std=c++11 -fblocks %s %target -o %t%output-suffix && %filecheck

namespace N {
  typedef void (^BL)();
  int func(BL, BL, BL);

  BL ArrBlock [] = { ^{}, ^{}, ^{} };

  int ival = func(^{}, ^{}, ^{});

  void (^gvarlobal)(void) = ^{};

  struct S {
    BL field = ^{};
  };

  S blf;
};
