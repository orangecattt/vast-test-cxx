// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// expected-no-diagnostics

static_assert(true, "");

void f() {
  static_assert(true, "");
}