// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

module;

#include "Inputs/module-extern-C.h"

export module x;

// CHECK: void @foo()
extern "C" void foo() {
  return;
}

extern "C" {
// CHECK: void @bar()
void bar() {
  return;
}
// CHECK: i32 @baz()
int baz() {
  return 3;
}
// CHECK: double @double_func()
double double_func() {
  return 5.0;
}
}
