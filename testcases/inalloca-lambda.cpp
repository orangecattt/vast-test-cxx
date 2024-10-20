// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  A();
  A(const A &);
  int x;
};
void decayToFp(int (*f)(A));
void test() {
  auto ld = [](A a) {
    static int calls = 0;
    ++calls;
    return a.x + calls;
  };
  decayToFp(ld);
  ld(A{});
}




struct B {
  B();
  B(B &);
  void operator=(B);
  long long x;
} b;

void f() {
  [](B) {}(b);
}

