// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  long x, y;
};

struct B {
  long x, y, z, w;
};

extern "C" {

int f1(A, A, A, A);
B f2(void);
_Complex float f3(void);
A &f4();

}

void test() {
  A a;

  __builtin_call_with_static_chain(f1(a, a, a, a), f1);

  __builtin_call_with_static_chain(f2(), f2);

  __builtin_call_with_static_chain(f3(), f3);

  __builtin_call_with_static_chain(f4(), f4);
}
