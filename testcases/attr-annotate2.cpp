// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


void f() {
  int n = 10;
  [[clang::annotate("_Generic selection expression should be fine", _Generic(n, int : 0, default : 1))]]
  int j = 0; // second arg should resolve to 0 fine
}
