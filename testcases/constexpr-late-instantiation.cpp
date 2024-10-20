// Make sure foo is instantiated and we don't get a link error
// RUN: %driver -cc1 %isys %s -o- %target -o %t%output-suffix && %filecheck

template <typename T>
constexpr T foo(T a);

// CHECK-LABEL: define {{.*}} @main
int main() {
  // CHECK: call {{.*}} @_Z3fooIiET_S0_
  int k = foo<int>(5);
}
// CHECK: }

template <typename T>
constexpr T foo(T a) {
  return a;
}
