// RUN: %driver -cc1 %isys %std_cxx11-14 -no-enable-noundef-analysis %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %std_cxx17- -no-enable-noundef-analysis %s %target -o %t%output-suffix && %filecheck

struct A { int x; A(int); ~A(); };
A f() { return A(0); }

namespace no_elide_base {
  struct Base { 
    Base(const Base&);
    ~Base();
  };

  struct Other {
    operator Base() const;
  };

  struct Derived : public virtual Base { 
    Derived(const Other &O);
  };

  Derived::Derived(const Other &O) 
    : Base(O)
  {
  }
}


namespace PR8683 {

struct A {
  A();
  A(const A&);
  A& operator=(const A&);
};

struct B {
  A a;
};

void f() {
  A a = (B().a);
}

}

namespace PR12139 {
  struct A {
    A() : value(1) { }
    A(A const &, int value = 2) : value(value) { }
    int value;

    static A makeA() { A a; a.value = 2; return a; }
  };

  int test() {
    A a(A::makeA(), 3);
    return a.value;
  }
}

namespace ElidableCallIsNotCopyCtor {
  struct A { A(const A&); };
  struct B : A {
    B(B&);
    B(A);
    B(int);
  };
  void f() {
    B b = 0;
  }
}
