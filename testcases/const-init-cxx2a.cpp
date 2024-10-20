// RUN: %driver -cc1 %isys %s -std=c++2a %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -emit-pch %s -std=c++2a -o %t.pch
// RUN: %driver -cc1 %isys -include-pch %t.pch -x c++ /dev/null -std=c++2a %target -o %t%output-suffix && %filecheck

int a = (delete new int, 123);

struct B {
  constexpr B() {}
  constexpr ~B() { n *= 5; }
  int n = 123;
};
extern constexpr B b = B();

const B c;
int use_c() { return c.n; }

struct D {
  int n;
  constexpr ~D() {}
};
D d;

D d_arr[3];

thread_local D d_tl;


void f() {
  constexpr B b;
  D d = D();
}

void g() {
  static constexpr B b1;
  static const B b2;
  static D d;
  thread_local D d_tl;
}
