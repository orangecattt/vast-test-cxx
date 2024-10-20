// RUN: %driver -cc1 %isys %s -o- %target -o %t%output-suffix && %filecheck

template <typename T>
constexpr T foo(T a);

int main() {
  int k = foo<int>(5);
}

template <typename T>
constexpr T foo(T a) {
  return a;
}
