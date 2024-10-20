// RUN: %driver -cc1 %isys %s -mconstructor-aliases -fcxx-exceptions -fexceptions -std=c++03 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -mconstructor-aliases -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck

struct A {
  int a;

  ~A();
};

struct B : A {
  ~B();
};

B::~B() { }

struct C {
  A a;

  ~C();
};

C::~C() { }

namespace PR7526 {
  extern void foo();
  struct allocator {
    ~allocator() throw();
  };

  struct allocator_derived : allocator { };


  allocator::~allocator() throw() { foo(); }

  void foo() {
    allocator_derived ad;
  }
}

template<typename T>
class A1 {
  ~A1();
};

template<> A1<char>::~A1();

namespace PR5529 {
  struct A {
    ~A();
  };

  A::~A() { }
  struct B : A {
    virtual ~B();
  };

  B::~B()  {}
}

namespace test0 {
  void foo();
  struct VBase { ~VBase(); };
  struct Base { ~Base(); };
  struct Member { ~Member(); };

  struct A : Base {
    Member M;
    ~A();
  };

  A::~A() try { } catch (int i) {}




  struct B : Base, virtual VBase {
    Member M;
    ~B();
  };
  B::~B() try { } catch (int i) {}




}

namespace test1 {
  struct A { ~A(); char ***m; }; // non-trivial destructor
  struct B { ~B(); }; // non-trivial destructor
  struct Empty { }; // trivial destructor, empty
  struct NonEmpty { int x; }; // trivial destructor, non-empty

  A::~A() { delete m; }

  struct M : A { ~M(); };
  M::~M() {}

  struct N : A, Empty { ~N(); };
  N::~N() {}

  struct O : Empty, A { ~O(); };
  O::~O() {}

  struct P : NonEmpty, A { ~P(); };
  P::~P() {} // CHECK3-LABEL: define{{.*}} void @_ZN5test11PD2Ev(ptr {{[^,]*}} %this) unnamed_addr

  struct Q : A, B { ~Q(); };
  Q::~Q() {} // CHECK3-LABEL: define{{.*}} void @_ZN5test11QD2Ev(ptr {{[^,]*}} %this) unnamed_addr

  struct R : A { ~R(); };
  R::~R() { A a; } // CHECK3-LABEL: define{{.*}} void @_ZN5test11RD2Ev(ptr {{[^,]*}} %this) unnamed_addr

  struct S : A { ~S(); int x; };
  S::~S() {}

  struct T : A { ~T(); B x; };
  T::~T() {} // CHECK4-LABEL: define{{.*}} void @_ZN5test11TD2Ev(ptr {{[^,]*}} %this) unnamed_addr

  struct U : A, virtual B { ~U(); };
  U::~U() {} // CHECK4-LABEL: define{{.*}} void @_ZN5test11UD2Ev(ptr {{[^,]*}} %this, ptr noundef %vtt) unnamed_addr
}

namespace test2 {
  struct A { ~A(); char ***m; };
  struct B : A { ~B(); };

  B::~B() {}
}

namespace test3 {
  struct A { virtual ~A(); };
  struct B { virtual ~B(); };
  namespace { // internal linkage => deferred
    struct C : A, B {}; // ~B() in D requires a this-adjustment thunk
    struct D : C {};    // D::~D() is an alias to C::~C()
  }

  void test() {
    new D; // Force emission of D's vtable
  }









}

namespace test4 {
  struct A { ~A(); };

  void foo() {
    {
      A a;
      goto failure;
    }

  failure:
    return;
  }

  void bar(int x) {
    for (A a; x; ) {
      x--;
    }
  }
}

namespace test5 {
  struct A { ~A(); };

  void foo() {
    A elems[5];
  }
}

namespace test6 {
  void opaque();

  struct A { ~A(); };
  template <unsigned> struct B { B(); ~B(); int _; };
  struct C : B<0>, B<1>, virtual B<2>, virtual B<3> {
    A x, y, z;

    C();
    ~C();
  };

  C::C() { opaque(); }

  C::~C() { opaque(); }


}

namespace test7 {
  struct D { ~D(); };

  struct A { ~A(); };
  A::~A() { }

  struct B : public A {
    ~B();
    D arr[1];
  };

  B::~B() {}
}

namespace test8 {
  struct A { A(); ~A(); };

  void die() __attribute__((noreturn));
  void test() {
    A x;
    while (1) {
      A y;
      goto l;
    }
  l: die();
  }

}

namespace test9 {
  struct ArgType {
    ~ArgType();
  };
  template<typename T>
  void f1(const ArgType& = ArgType());
  void f2();
  void bar() {
    f1<int>();
    f2();
  }
}

namespace test10 {
  struct Option {
    virtual ~Option() {}
  };
  template <class DataType> class opt : public Option {};
  template class opt<int>;
  bool handleOccurrence() {
    Option x;
    return true;
  }
}

#if __cplusplus >= 201103L
namespace test11 {






  struct S1 {
    ~S1();
    int a[8];
  };

  void func1(S1 &) noexcept(false);

  void testLifetimeEnd(int n) {
    if (n < 10) {
      S1 t1;
      func1(t1);
    } else if (n < 100) {
      S1 t2;
      func1(t2);
    } else if (n < 1000) {
      S1 t3;
      func1(t3);
    }
  }

}

namespace final_dtor {
  struct A {
    virtual void f();
    virtual ~A() { f(); }
  };
  struct B : A {
    virtual ~B() { f(); }
  };
  struct C final : A {
    virtual ~C() { f(); }
  };
  struct D : A {
    virtual ~D() final { f(); }
  };
  void use() {
    {A a;}
    {B b;}
    {C c;}
    {D d;}
  }
}
#endif
