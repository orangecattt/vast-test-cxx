// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);


struct C {
  C() : iC(6) {printf("C()\n"); }
  C(const C& c) { printf("C(const C& c)\n"); }
  int iC;
};

C foo() {
  return C();
};

class X { // ...
public: 
  X(int) {}
  X(const X&, int i = 1, int j = 2, C c = foo()) {
    printf("X(const X&, %d, %d, %d)\n", i, j, c.iC);
  }
};


struct S {
  S();
};

S::S() { printf("S()\n"); }

void Call(S) {};

int main() {
  X a(1);
  X b(a, 2);
  X c = b;
  X d(a, 5, 6);
  S s;
  Call(s);
}

struct V {
  int x;
};

typedef V V_over_aligned __attribute((aligned(8)));
extern const V_over_aligned gv1 = {};

extern "C" V f() { return gv1; }

