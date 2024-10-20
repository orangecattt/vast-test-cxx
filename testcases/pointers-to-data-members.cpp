// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { int a; int b; };
struct B { int b; };
struct C : B, A { };

namespace ZeroInit {
  int A::* a;
  
  int A::* aa[2];
  
  int A::* aaa[2][2];
  
  int A::* b = 0;

  struct {
    int A::*a;
  } sa;
  void test_sa() { (void) sa; } // force emission
  
  struct {
    int A::*aa[2];
  } ssa[2];
  void test_ssa() { (void) ssa; }
  
  struct {
    struct {
      int A::*pa;
    } s;
  } ss;
  void test_ss() { (void) ss; }
  
  struct A {
    int A::*a;
    int b;
  };

  struct B {
    A a[10];
    char c;
    int B::*b;
  };

  struct C : A, B { int j; };
  C c;
}

namespace PR5674 {
  int A::*pb = &A::b;
}

namespace Casts {

int A::*pa;
int C::*pc;

void f() {
  pa = 0;

  pc = pa;

  pa = static_cast<int A::*>(pc);
}

}

namespace Comparisons {
  void f() {
    int A::*a;

    if (a) { }

    if (a != 0) { }
    
    if (0 != a) { }

    if (a == 0) { }

    if (0 == a) { }
  }
}

namespace ValueInit {

struct A {
  int A::*a;

  char c;

  A();
};

A::A() : a() {}

}

namespace VirtualBases {

struct A {
  char c;
  int A::*i;
};

struct B : virtual A { };
B b;

struct C : virtual A { int A::*i; };
C c;

struct D : C { int A::*i; };
D d;

}

namespace Test1 {

struct A {
  int A::* a;
  int b : 10;
};
A a;

}

namespace BoolPtrToMember {
  struct X {
    bool member;
  };

  bool &f(X &x, bool X::*member) {
    return x.*member;
  }
}

namespace PR8507 {
  
struct S;
void f(S* p, double S::*pm) {
  if (0 < p->*pm) {
  }
}

}

namespace test4 {
  struct A             { int A_i; };
  struct B : virtual A { int A::*B_p; };
  struct C : virtual B { int    *C_p; };
  struct D :         C { int    *D_p; };

  D d;
}

namespace PR11487 {
  union U
  {
    int U::* mptr;
    char x[16];
  } x;
  
}

namespace PR13097 {
  struct X { int x; X(const X&); };
  struct A {
    int qq;
      X x;
  };
  A f();
  X g() { return f().*&A::x; }
}

namespace PR21089 {
struct A {
  bool : 1;
  int A::*x;
  bool y;
  A();
};
struct B : A {
};
B b;
}

namespace PR21282 {
union U {
  int U::*x;
  long y[2];
};
U u;
}

namespace FlexibleArrayMember {
struct S {
  int S::*x[];
};
S s;
}

namespace IndirectPDM {
union U {
  union {
    int U::*m;
  };
};
U u;
}

namespace PR47864 {
  struct B;
  struct B {};
  struct D : B { int m; };
  auto x = (int B::*)&D::m;
}
