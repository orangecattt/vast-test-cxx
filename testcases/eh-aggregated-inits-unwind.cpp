// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -fno-elide-constructors %s %target -o %t%output-suffix && %filecheck

struct ImplicitCopy {
  int id;
  ImplicitCopy() { id = 10; }
  ~ImplicitCopy() { id = 20; }
};

struct ThrowCopy {
  int id;
  ThrowCopy() { id = 15; }
  ThrowCopy(const ThrowCopy &x) {
    id = 25;
    throw 1;
  }
  ~ThrowCopy() { id = 35; }
};

struct Container {
  int id;
  ImplicitCopy o1;
  ThrowCopy o2;

  Container() { id = 1000; }
  ~Container() { id = 2000; }
};

int main() {
  try {
    Container c1;
    Container c2(c1);

    return 2;
  } catch (...) {
    return 1;
  }
  return 0;
}
