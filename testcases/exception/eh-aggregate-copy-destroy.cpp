// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -fno-elide-constructors -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -fno-elide-constructors -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct ImplicitCopy {
  int x;
  ImplicitCopy() { x = 10; }
  ~ImplicitCopy() { x = 20; }
};

struct ThrowCopy {
  ThrowCopy() {}
  ThrowCopy(const ThrowCopy &) { throw 1; }
};

struct Container {
  ImplicitCopy b[2];
  ThrowCopy c;
};

int main () {
  try {
    Container c1;
    Container c2(c1);
  }
  catch (...) {
    return 1;
  }

  return 0;
}

