// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

union PR23373 {
  PR23373(PR23373&) = default;
  PR23373 &operator=(PR23373&) = default;
  int n;
  float f;
};
extern PR23373 pr23373_a;

PR23373 pr23373_b(pr23373_a);

PR23373 pr23373_f() { return pr23373_a; }

void pr23373_g(PR23373 &a, PR23373 &b) { a = b; }

struct A { virtual void a(); };
A x(A& y) { return y; }

