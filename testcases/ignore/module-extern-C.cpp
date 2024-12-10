// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

module;

#include "Inputs/module-extern-C.h"

export module x;

extern "C" void foo() {
  return;
}

extern "C" {
void bar() {
  return;
}
int baz() {
  return 3;
}
double double_func() {
  return 5.0;
}
}
