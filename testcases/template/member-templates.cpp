// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  template<typename T>
  A(T);
};

template<typename T> A::A(T) {}

struct B {
  template<typename T>
  B(T);
};

template<typename T> B::B(T) {}

template B::B(int);

template<typename T>
struct C {
  void f() {
    int a[] = { 1, 2, 3 };
  }
};

void f(C<int>& c) {
  c.f();
}
