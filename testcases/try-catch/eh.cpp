// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions -std=c++11 %s -fassume-nothrow-exception-dtor -DNOTHROWEND %target -o %t%output-suffix && %filecheck

struct test1_D {
  double d;
} d1;

void test1() {
  throw d1;
}



struct test2_D {
  test2_D(const test2_D&o);
  test2_D();
  virtual void bar() { }
  int i; int j;
} d2;

void test2() {
  throw d2;
}



struct test3_D {
  test3_D() { }
  test3_D(volatile test3_D&o);
  virtual void bar();
};

void test3() {
  throw (volatile test3_D *)0;
}



void test4() {
  throw;
}


namespace test5 {
  struct A {
    A();
    A(const A&);
    ~A();
  };

  void test() {
    try { throw A(); } catch (A &x) {}
  }
}

namespace test6 {
  template <class T> struct allocator {
    ~allocator() throw() { }
  };

  void foo() {
    allocator<int> a;
  }
}

namespace test7 {
  int foo() {
    try {
      try {
        throw 1;
      }

      catch (int) {
        throw;
      }
    }
    catch (...) {
    }
    return 0;
  }
}

namespace test8 {
  struct A { A(const A&); ~A(); };
  void bar();

  void foo() {
    try {
      bar();
    } catch (A a) {
    }
  }
}

namespace test9 {
  void opaque();

  struct A { A(); };


  A::A() try {
    opaque();
  } catch (int x) {


    opaque();
  }
}

namespace test10 {
  void opaque();

  struct A { ~A(); };
  struct B { int x; };

  void foo() {
    A a; // force a cleanup context

    try {
      opaque();
    } catch (int i) {
    } catch (B a) {
    } catch (...) {
    }

  }
}

namespace test11 {
  void opaque();

  void foo() {
    try {
      opaque();
    } catch (int**&p) {
    }
  }

  struct A {};

  void bar() {
    try {
      opaque();
    } catch (A*&p) {
    }
  }
}

namespace test12 {
  struct A { ~A() noexcept(false); };
  bool opaque(const A&);

  void test() {

    A x;
    if (opaque(x)) {
      A y;
      A z;

      goto success;
    }

  success:
    bool _ = true;

  }
}

namespace test13 {
  struct A { ~A(); };

  void test0(int x) {
    try {
      switch (x) {
      case 0:
        break;
      case 1:{
        A a;
        break;
      }
      default:
        return;
      }
      return;
    } catch (int x) {
    }
    return;
  }

  void test1(int x) {
    A y;
    try {
      switch (x) {
      default: break;
      }
    } catch (int x) {}
  }
}

namespace test14 {
  struct A { ~A(); };
  struct B { ~B(); };

  B b();
  void opaque();

  void foo() {
    A a;
    try {
      B str = b();
      opaque();
    } catch (int x) {
    }
  }
}

namespace test15 {
  struct A { ~A(); };

  bool opaque(int);

  void foo() {
    A a;

    try {
      int x = 10;

      while (true) {
        if (opaque(x))
          break;

      }
    } catch (int x) { }

  }
}

namespace test16 {
  struct A { A(); ~A() noexcept(false); };
  struct B { int x; B(const A &); ~B() noexcept(false); };
  void foo();
  bool cond();

  void bar() {

#ifndef NOTHROWEND
    cond() ? throw B(A()) : foo();
#endif





  }
}

namespace test17 {
class BaseException {
private:
  int a[4];
public:
  BaseException() {};
};

class DerivedException: public BaseException {
};

int foo() {
  throw DerivedException();

}
}

