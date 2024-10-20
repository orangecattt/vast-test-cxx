// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fstrict-vtable-pointers %target -o %t%output-suffix && %filecheck

namespace PR5021 {

struct A {
  virtual void f(char);
};

void f(A *a) {
  a->f('c');
}

struct B : virtual A { 
  virtual void f();
};

void f(B * b) {
  b->f();
}

}

namespace Test1 {
  struct A { 
    virtual ~A(); 
  };

  struct B : A {
    virtual ~B();
    virtual void f();
  };

  void f(B *b) {
    b->f();
  }
}

namespace VirtualNoreturn {
  struct A {
    [[noreturn]] virtual void f();
  };

  void f(A *p) {
    p->f();
  }
}

