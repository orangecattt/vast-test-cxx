// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

template <typename T>
struct X {
  X();
};

// CHECK: define {{.*}} @_ZN1XIbEC2Ev
// CHECK: define {{.*}} @_ZN1XIbEC1Ev
template <> X<bool>::X() = default;

// CHECK: define weak_odr {{.*}} @_ZN1XIiEC2Ev
// CHECK: define weak_odr {{.*}} @_ZN1XIiEC1Ev
template <typename T> X<T>::X() = default;
template X<int>::X();

// CHECK: define linkonce_odr {{.*}} @_ZN1XIcEC1Ev
// CHECK: define linkonce_odr {{.*}} @_ZN1XIcEC2Ev
X<char> x;
