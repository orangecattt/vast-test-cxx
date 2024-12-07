// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

struct S {
  int i;
  int j;
};

int f() {
  auto [i, j] = S{1, 42};
  return [&i, j] {
    return i + j;
  }();
}







