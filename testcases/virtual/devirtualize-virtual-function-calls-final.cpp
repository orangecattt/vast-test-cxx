// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

namespace Test1 {
  struct A {
    virtual int f() final;
  };

  int f(A *a) {
    return a->f();
  }
}

namespace Test2 {
  struct A final {
    virtual int f();
  };

  int f(A *a) {
    return a->f();
  }
}

namespace Test2a {
  struct A {
    virtual ~A() final {}
    virtual int f();
  };

  int f(A *a) {
    return a->f();
  }
}


namespace Test3 {
  struct A {
    virtual int f();  };

  struct B final : A { };

  int f(B *b) {
    return b->f();
  }

  int f(B &b) {
    return b.f();
  }

  int f(void *v) {
    return static_cast<B*>(v)->f();
  }
}

namespace Test4 {
  struct A {
    virtual void f();
    virtual int operator-();
  };

  struct B final : A {
    virtual void f();
    virtual int operator-();
  };

  void f(B* d) {
    static_cast<A*>(d)->f();
    -static_cast<A&>(*d);
  }
}

namespace Test5 {
  struct A {
    virtual void f();
    virtual int operator-();
  };

  struct B : A {
    virtual void f();
    virtual int operator-();
  };

  struct C final : B {
  };

  void f(C* d) {
    static_cast<A*>(d)->f();
  }
  void fop(C* d) {
    -static_cast<A&>(*d);
  }
}

namespace Test6 {
  struct A {
    virtual ~A();
  };

  struct B : public A {
    virtual ~B();
  };

  struct C {
    virtual ~C();
  };

  struct D final : public C, public B {
  };

  void f(D* d) {
    static_cast<A*>(d)->~A();
  }
}

namespace Test7 {
  struct foo {
    virtual void g() {}
  };

  struct bar {
    virtual int f() { return 0; }
  };

  struct zed final : public foo, public bar {
    int z;
    virtual int f() {return z;}
  };

  int f(zed *z) {
    return static_cast<bar*>(z)->f();
  }
}

namespace Test8 {
  struct A { virtual ~A() {} };
  struct B {
    int b;
    virtual int foo() { return b; }
  };
  struct C final : A, B {  };
  int test(C *c) {
    return static_cast<B*>(c)->foo();
  }
}

namespace Test9 {
  struct A {
    int a;
  };
  struct B {
    int b;
  };
  struct C : public B, public A {
  };
  struct RA {
    virtual A *f() {
      return 0;
    }
    virtual A *operator-() {
      return 0;
    }
  };
  struct RC final : public RA {
    virtual C *f() {
      C *x = new C();
      x->a = 1;
      x->b = 2;
      return x;
    }
    virtual C *operator-() {
      C *x = new C();
      x->a = 1;
      x->b = 2;
      return x;
    }
  };
  A *f(RC *x) {
    return static_cast<RA*>(x)->f();
  }
  A *fop(RC *x) {
    return -static_cast<RA&>(*x);
  }
}

namespace Test10 {
  struct A {
    virtual int f();
  };

  struct B : A {
    int f() final;
  };

  int f(B *b) {
    return static_cast<A *>(b)->f();
  }
}

namespace TestVBase {
  struct A { virtual void f(); };
  struct B : virtual A {};
  struct C : virtual A { void f() override; };

  extern struct BC final : B, C {} &bc;
  extern struct BCusingA final : B, C { using A::f; } &bc_using_a;
  extern struct BCusingB final : B, C { using B::f; } &bc_using_b;
  extern struct BCusingC final : B, C { using C::f; } &bc_using_c;

  extern struct CB final : C, B {} &cb;
  extern struct CBusingA final : C, B { using A::f; } &cb_using_a;
  extern struct CBusingB final : C, B { using B::f; } &cb_using_b;
  extern struct CBusingC final : C, B { using C::f; } &cb_using_c;

  void test() {

    bc.f();
    bc_using_a.f();
    bc_using_b.f();
    bc_using_c.f();

    cb.f();
    cb_using_a.f();
    cb_using_b.f();
    cb_using_c.f();
  }
}

namespace Test11 {

  class Base {
  public:
    virtual void operator()() {}
    virtual bool operator==(const Base &other) { return false; }
    virtual bool operator!() { return false; }
    virtual Base &operator[](int i) { return *this; }
  };

  template<class T>
  struct S {
    class Derived final : public Base {
    public:
      void operator()() override {}
      bool operator==(const Base &other) override { return true; }
      bool operator!() override { return true; }
      Base &operator[](int i) override { return *this; }
    };

    Derived *ptr = nullptr, *ptr2 = nullptr;

    void foo1() {
      if (ptr && ptr2) {
        (*ptr)();
        (void)(*ptr == *ptr2);
        (void)(!(*ptr));
        (void)((*ptr)[1]);
      }
    }
  };

  void foo2() {
    S<int> *s = new S<int>;
    s->foo1();
  }
}
