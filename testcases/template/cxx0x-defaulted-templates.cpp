// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

template <typename T>
struct X {
  X();
};

template <> X<bool>::X() = default;

template <typename T> X<T>::X() = default;
template X<int>::X();

X<char> x;
