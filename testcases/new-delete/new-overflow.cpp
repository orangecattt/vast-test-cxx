// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck

namespace test0 {
  struct A {
    A();
    int x;
  };

  typedef A elt;

  elt *test(short s) {
    return new elt[s];
  }
}

namespace test1 {
  struct A {
    A();
    int x;
  };

  typedef A elt[100];

  elt *test(short s) {
    return new elt[s];
  }
}

namespace test2 {
  struct A {
    A();
    ~A();
    int x;
  };

  typedef A elt[100];

  elt *test(short s) {
    return new elt[s];
  }
}

namespace test4 {
  struct A {
    A();
  };

  typedef A elt;

  elt *test(short s) {
    return new elt[s];
  }
}

namespace test5 {
  struct A {
    A();
  };

  typedef A elt;

  elt *test(int s) {
    return new elt[s];
  }
}

namespace test6 {
  struct A {
    A();
    int x;
  };

  typedef A elt;

  elt *test(unsigned short s) {
    return new elt[s];
  }
}

namespace test7 {
  struct A {
    A();
    int x;
  };

  typedef A elt[100];

  elt *test(unsigned short s) {
    return new elt[s];
  }
}

namespace test8 {
  struct A {
    A();
    int x;
  };

  typedef A elt;

  elt *test(long long s) {
    return new elt[s];
  }
}

namespace test9 {
  struct A {
    A();
    int x;
  };

  typedef A elt;

  elt *test(unsigned long long s) {
    return new elt[s];
  }
}
