// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

class B {
public:
  [[clang::disable_tail_calls]] virtual int m1() { return 1; }
  virtual int m2() { return 2; }
  int m3() { return 3; }
  [[clang::disable_tail_calls]] int m4();
};

class D : public B {
public:
  int m1() override { return 11; }
  [[clang::disable_tail_calls]] int m2() override { return 22; }
};

int foo1() {
  B *b = new B;
  D *d = new D;
  int t = 0;
  t += b->m1() + b->m2() + b->m3() + b->m4();
  t += d->m1() + d->m2();
  return t;
}


