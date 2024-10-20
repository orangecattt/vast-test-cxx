// RUN: %driver -cc1 %isys -no-enable-noundef-analysis %s -std=c++98 -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -no-enable-noundef-analysis %s -std=c++11 -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -no-enable-noundef-analysis %s -std=c++11 -fcxx-exceptions -fexceptions -fassume-nothrow-exception-dtor %target -o %t%output-suffix && %filecheck


typedef __typeof(sizeof(0)) size_t;

void *operator new(size_t, void*);

namespace test0 {
  struct allocator {
    allocator();
    allocator(const allocator&);
    ~allocator();
  };

  void f();
  void g(bool b, bool c) {
    if (b) {
      if (!c)
        throw allocator();

      return;
    }
    f();
  }
}

namespace test1 {
  struct A { A(int); A(int, int); ~A(); void *p; };

  A *a() {
    return new A(5);
  }

  A *b() {
    extern int foo();
    return new A(foo());
  }

  struct B { B(); ~B(); operator int(); int x; };
  B makeB();

  A *c() {


    return new A(B().x);
  }


  A *d() {


    return new A(B());
  }

  A *e() {



    return new A(B(), B());
  }
  A *f() {
    return new A(makeB().x);
  }
  A *g() {
    return new A(makeB());
  }
  A *h() {
    return new A(makeB(), makeB());
  }

  A *i() {



    A *x;
    return (x = new A(makeB()), makeB(), x);
  }
}

namespace test2 {
  struct A {
    A(int); A(int, int); ~A();
    void *p;
    void *operator new(size_t);
    void operator delete(void*, size_t);
  };

  A *a() {


    return new A(5);
  }
}

namespace test3 {
  struct A {
    A(int); A(int, int); A(const A&); ~A();
    void *p;
    void *operator new(size_t, void*, double);
    void operator delete(void*, void*, double);
  };

  void *foo();
  double bar();
  A makeA(), *makeAPtr();

  A *a() {


    return new(foo(),bar()) A(5);
  }

  A *b(bool cond) {


    return (cond ?

            new(foo(),10.0) A(makeA()) :

            makeAPtr());



  }
}

namespace test4 {
  struct A {
    A(int); A(int, int); ~A();
    void *p;
    void *operator new(size_t, void*, void*);
    void operator delete(void*, size_t, void*, void*); // not a match
  };

  A *a() {
    extern void *foo(), *bar();

    return new(foo(),bar()) A(5);
  }
}

namespace test5 {
  struct T { T(); ~T(); };

  struct A {
    A(const A &x, const T &t = T());
    ~A();
  };

  void foo();




  void test() {
    try {
      foo();
    } catch (A a) {
    }
  }
}

namespace test6 {
  bool cond();
  void test() {
    try {
    lbl:
      if (cond()) goto lbl;
    } catch (...) {
    }
  }
}

namespace test7 {
  struct A { A(); ~A(); };
  struct B {
    static void *operator new(size_t size) throw();
    B(const A&, B*);
    ~B();
  };

  B *test() {














    return new B(A(), new B(A(), 0));
  }
}

namespace test8 {
  struct A {
    A(const A&);
    A&operator=(const A&);

    ~A();
  };

  A makeA();
  void test() {
    throw makeA();
  }
}

namespace test9 {
  struct A {
    A();
    ~A();
  };
  A* test() {
    return new A[10];
  }
}

namespace test10 {
  extern void cleanup();
  extern bool suppress;

  struct A { ~A(); };
  A::~A() try { cleanup(); } catch (...) { return; }

  struct B { ~B(); };
  B::~B() try { cleanup(); } catch (...) {}

  struct C { ~C(); };
  C::~C() try { cleanup(); } catch (...) { if (suppress) return; }



}

namespace test11 {
  struct A {
    A();
    ~A() {}
  };

  struct C {
    A single;
    A array[2][3];

    C();
  };

  C::C() {
    throw 0;
  }






}

namespace test12 {
  struct A {
    void operator delete(void *, void *);
    A();
  };

  A *test(void *ptr) {
    return new (ptr) A();
  }

}

namespace test13 {

struct A {
  A();
  ~A();
  int a, b;
};








void test(int c) {
  const A &s = c ? static_cast<const A &>(A()) : static_cast<const A &>(A());
}

}

