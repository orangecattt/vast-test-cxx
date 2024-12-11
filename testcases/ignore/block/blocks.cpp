// RUN: %driver -cc1 %isys %s -fblocks %target -o %t%output-suffix && %filecheck


namespace test0 {
  void test(int x) {
    ^{ ^{ (void) x; }; };
  }
}

extern void (^out)();

namespace test1 {
  void test1() {
    const int NumHorsemen = 4;
    out = ^{ (void) NumHorsemen; };
  }

  struct loc { double x, y; };
  void test2() {
    const loc target = { 5, 6 };
    out = ^{ (void) target; };
  }

  struct mut { mutable int x; };
  void test3() {
    const mut obj = { 5 };
    out = ^{ (void) obj; };
  }

  struct scope { int x; ~scope(); };
  void test4() {
    const scope obj = { 5 };
    out = ^{ (void) obj; };
  }

}

namespace test2 {
  struct A {
    A();
    A(const A &);
    ~A();
  };

  struct B {
    B();
    B(const B &);
    ~B();
  };

  void test() {
    __block A a;
    __block B b;
    ^{ (void)a; (void)b; };
  }




}

namespace test3 {
  struct A {
    A(const A&);
    ~A();
  };

  struct B : A {
  };

  void test(B b) {
    extern void consume(void(^)());
    consume(^{ (void) b; });
  }
}

namespace test4 {
  struct A {
    A();
    ~A();
  };

  void foo(A a);

  void test() {
    extern void consume(void(^)());
    consume(^{ return foo(A()); });
  }
}

namespace test5 {
  struct A {
    unsigned afield;
    A();
    A(const A&);
    ~A();
    void foo() const;
  };

  void doWithBlock(void(^)());

  void test(bool cond) {
    A x;
    void (^b)() = (cond ? ^{ x.foo(); } : (void(^)()) 0);
    doWithBlock(b);
  }


}

namespace test6 {
  struct A {
    A();
    ~A();
  };

  void foo(const A &, void (^)());
  void bar();

  void test() {
    foo(A(), ^{ bar(); });
    bar();
  }

}

namespace test7 {
  int f() {
    static int n;
    int *const p = &n;
    return ^{ return *p; }();
  }
}

namespace test8 {
  struct X {
    int x;

    template<typename T>
    int foo() {
      return ^ { return x; }();
    }
  };

  template int X::foo<int>();
}

namespace test9 {
  struct B {
    void *p;
    B();
    B(const B&);
    ~B();
  };

  void use_block(void (^)());
  void use_block_2(void (^)(), const B &a);

  void test() {
    B x;
    use_block(^{
        int y;
        use_block_2(^{ (void)y; }, x);
    });
  }
}

namespace test10 {


  struct B {
    int a;
    B();
    B(const B &);
    B(const volatile B &);
    ~B();
  };

  void test() {
    volatile B x;
    ^{ (void)x; };
  }
}




namespace {
  struct B {
    int a;
    B();
    B(const B &);
    ~B();
  };

  void test() {
    B x;
    ^{ (void)x; };
  }
}

void callTest() {
  test();
}
