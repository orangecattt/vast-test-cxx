// RUN: %driver -cc1 %isys -x c++ -std=c++11 -fblocks %s %target -o %t%output-suffix && %filecheck


int main() {
  __block int baz = [&]() { return 0; }();
  ^{ (void)baz; };
  return 0;
}
