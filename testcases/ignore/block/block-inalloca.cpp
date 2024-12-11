// RUN: %driver -cc1 %isys -fblocks %s %target -o %t%output-suffix && %filecheck

struct S {
  S(const struct S &) {}
};

void (^b)(S) = ^(S) {};


