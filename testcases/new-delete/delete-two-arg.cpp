// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

typedef __typeof(sizeof(int)) size_t;

namespace test1 {
  struct A { void operator delete(void*,size_t); int x; };

  void a(A *x) {
    delete x;
  }
}

namespace test2 {
  struct A {
    int x;
    void *operator new[](size_t);
    void operator delete[](void *, size_t);
  };

  A *test() {
    return ::new A[10];
  }

  void test(A *p) {
    ::delete[] p;
  }
}

namespace test3 {
  struct A {
    int x;
    void operator delete[](void *, size_t);
  };
  struct B : A {};

  void test() {
    (void) new B[5];
  }
}
