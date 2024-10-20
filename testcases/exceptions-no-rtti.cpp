// RUN: %driver -cc1 %isys -fno-rtti -fcxx-exceptions -fexceptions -Wno-dynamic-exception-spec %s %std_cxx98- %target -o %t%output-suffix && %filecheck


namespace test0 {
  class err {};

  void f(void) {
    try {
    } catch (err &) {
    }
  }
}

namespace test1 {
  class A { virtual void foo(); };
  class B { virtual void foo(); };
  class C { virtual void foo(); };
  class D { virtual void foo(); };

  void opaque();

  void test0() {
    throw A();
  }

  void test1() throw(B) {
    opaque();
  }

  void test2() {
    try {
      opaque();
    } catch (C&) {}
  }

  void test3(D *ptr) {
    throw ptr;
  };
}
