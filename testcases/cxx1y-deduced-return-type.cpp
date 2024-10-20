// RUN: %driver -cc1 %isys -std=c++1y %s %target -o %t%output-suffix && %filecheck


inline auto f() {
  int n = 0;
  return [=] () mutable { return ++n; };
}

auto x = f();

template<typename T> auto *g(T t) { return t; }
template<typename T> decltype(auto) h(T t) { return t; }

void z() {
  g(&x);
  h(&x);
}

auto i() { return [] {}; }
auto j() {
  h(i());
}
