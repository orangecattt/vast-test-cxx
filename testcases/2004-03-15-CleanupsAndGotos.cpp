// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Testcase from Bug 291

struct X {
  ~X();
};

void foo() {
  X v;

TryAgain:
  goto TryAgain;
}
