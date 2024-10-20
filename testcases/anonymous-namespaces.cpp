// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck

int f();

namespace {
  int a = 0;

  int b = f();

  static int c = f();

  extern int c2;
  int g() { return c2; }
  static int c2 = f();

  class D {
    static int d;
  };
  
  int D::d = f();

  struct X { 
    struct EBase { };
    struct E : public virtual EBase { virtual ~E() {} };
  };

  int foo() {
    return 32;
  }

  namespace A {
    int foo() {
      return 45;
    }
  }
}

int concrete() {
  return a + foo() + A::foo();
}

void test_XE() { throw X::E(); }

namespace test2 {
  struct A {
    template <class T> struct B {
      static void foo() {}
    };
  };
  namespace {
    struct C;
  }

  void test() {
    A::B<C>::foo();
  }

}

namespace {

int bar() {
  extern int a;
  return a;
}

} // namespace
