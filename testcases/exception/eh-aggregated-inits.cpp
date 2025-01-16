// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -fno-elide-constructors %s %target -o %t%output-suffix && %filecheck

int globId = 0;

struct ImplicitCopy {
  int id;

  ImplicitCopy() { id = 10; }
  ~ImplicitCopy() { id = 20; }
};

struct ExplicitCopy {
  int id;

  ExplicitCopy() { id = 15; }
  ExplicitCopy(const ExplicitCopy &x) { id = 25; }
  ~ExplicitCopy() { id = 35; }
};

struct Container {
  ImplicitCopy o1; // memcpy-able member.
  ExplicitCopy o2; // non-trivial initialization.

  Container() { globId = 1000; }
  ~Container() { globId = 2000; }
};

int main() {
  try {
    Container c1;
    Container c2(c1);

    return 2;
  }
  catch (...) {
    return 1;
  }
  return 0;
}
