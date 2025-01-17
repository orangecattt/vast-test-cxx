// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

struct A {
  virtual void f();
  virtual void f_const() const;
  virtual void g();

  A h();
};

A g();

void f(A a, A *ap, A& ar) {
  
  a.f();

  ap->f();

  ar.f();
  
  A().f();

  g().f();
  
  a.h().f();

  a.f_const();

  (a).f();
}

struct D : A { virtual void g(); };
struct XD { D d; };

D gd();

void fd(D d, XD xd, D *p) {
  d.f();

  d.g();

  D().f();

  D().g();

  gd().f();
  
  d.f_const();

  (d).f();

  (true, d).f();

  (true, d).g();

  xd.d.f();

  XD().d.f();

  D XD::*mp;
  (xd.*mp).f();

  (xd.*mp).g();

  p[0].f();

  p[1].f();
}

struct B {
  virtual void f();
  ~B();
  
  B h();
};


void f() {
  B().f();
  
  B().h().f();
}

namespace test2 {
  struct foo {
    virtual void f();
    virtual ~foo();
  };

  struct bar : public foo {
    virtual void f();
    virtual ~bar();
  };

  void f(bar *b) {
    b->foo::f();
    b->foo::~foo();
  }
}

namespace test3 {
  struct B {
  };
  struct D : public B {
  };
  void f(D d) {
    d.B::~B();
  }
}

namespace test4 {
  struct Animal {
    virtual void eat();
  };
  struct Fish : Animal {
    virtual void eat();
  };
  struct Wrapper {
    Fish fish;
  };
  extern Wrapper *p;
  void test() {
    p->fish.eat();
  }
}

namespace test5 {
  struct X {
    virtual void f() = 0;
  };
  struct Y {};
  void f(Y &y, X Y::*p) {
    (y.*p).f();
  };

  struct Z final {
    virtual void f() = 0;
  };
  void g(Z &z) {
    z.f();
  }

  struct Q {
    virtual void f() final = 0;
  };
  void h(Q &q) {
    q.f();
  }
}
