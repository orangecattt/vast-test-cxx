// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fstrict-vtable-pointers %target -o %t%output-suffix && %filecheck

// PR5021
namespace PR5021 {

struct A {
  virtual void f(char);
};

void f(A *a) {
  // CHECK: call {{.*}}void %
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

  // CHECK-LABEL: @_ZN15VirtualNoreturn1f
  // CHECK-INVARIANT-LABEL: define {{(dso_local )?}}void @_ZN15VirtualNoreturn1f
  void f(A *p) {
    p->f();
    // CHECK: call {{.*}}void %{{[^#]*$}}
    // CHECK-NOT: unreachable
    // CHECK-INVARIANT: load {{.*}} !invariant.load ![[EMPTY_NODE:[0-9]+]]
  }
}

// CHECK-INVARIANT: ![[EMPTY_NODE]] = !{}
