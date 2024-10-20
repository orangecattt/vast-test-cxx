// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int a();
// CHECK: call noundef i32 @_Z1av()
struct x {int x, y : 10;} x = {1, a()};
