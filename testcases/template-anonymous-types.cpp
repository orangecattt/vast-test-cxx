// RUN: %driver -cc1 %isys %s -w %target -o %t%output-suffix && %filecheck

struct S {
  enum { FOO = 42 };
  enum { BAR = 42 };
};

template <typename T> struct X {
  T value;
  X(T t) : value(t) {}
  int f() { return value; }
};

template <typename T> int f(T t) {
  X<T> x(t);
  return x.f();
}

void test() {
  (void)f(S::FOO);
  (void)f(S::BAR);

}
