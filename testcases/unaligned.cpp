// RUN: %driver -cc1 %isys -x c++ -std=c++11 -fms-extensions < %s %target -o %t%output-suffix && %filecheck

int foo() {
  // CHECK: ret i32 1
  return alignof(__unaligned int);
}
