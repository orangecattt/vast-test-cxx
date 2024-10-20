// RUN: %driver -cc1 %isys -fblocks %s %target -o %t%output-suffix && %filecheck

struct S {
  S(const struct S &) {}
};

void (^b)(S) = ^(S) {};

// CHECK: [[DESCRIPTOR:%.*]] = getelementptr inbounds <{ ptr, %struct.S, [3 x i8] }>, ptr %0, i32 0, i32 0
// CHECK: load ptr, ptr [[DESCRIPTOR]]

