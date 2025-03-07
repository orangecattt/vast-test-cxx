// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A {
  virtual int f() { return 1; }
};

struct B {
  virtual int f() { return 2; }
};

struct C : A, B {
  virtual int f() { return 3; }
};

struct D : C {
  virtual int f() { return 4; }
};

static int f(D* d) {
  B* b = d;
  return b->f();
};

int g() {
  D d;
  return f(&d);
}

