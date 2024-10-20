// RUN: %driver -cc1 %isys -std=c++1z %s -fexceptions -fcxx-exceptions %target -o %t%output-suffix && %filecheck

namespace Constant {
  struct A {
    int n;
    char k;
    ~A();
  };

  struct B {
    char k2;
  };

  struct C : B {};

  struct D : A, C {};

  C c1 = {};
  C c2 = {1};

  D d1 = {};
  D d2 = {1, 2, 3};
  D d3 = {1};



}

namespace Dynamic {
  struct A {
    A();
    A(int);
    A(const char*, unsigned);
    ~A();
    void *p;
  };

  struct B {
    ~B();
    int n = 5;
  };

  struct C {
    C(bool = true);
  };

  int f(), g(), h(), i();
  struct D : A, B, C {
    int n = f();
  };

  D d1 = {};

  D d2 = {1, 2, false};

  D d3 = {g(), h(), {}, i()};
}

namespace Instantiated1 {
  struct A { A(); };
  struct B : A { using A::A; };
  template<int> B v({});
  template B v<0>;
}

namespace Instantiated2 {
  struct A { A(); };
  struct B : A {};
  template<int> B v({});
  template B v<0>;
}
