// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void f()
{
  // CHECK: store i32 0
  int i{};
}
