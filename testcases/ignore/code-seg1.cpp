// RUN: %driver -cc1 %isys -fms-extensions %s %target -o %t%output-suffix && %filecheck


struct __declspec(code_seg("foo_outer")) Foo1 {
  struct Inner {
    void bar1();
    static void bar2();
  };
};
void Foo1::Inner::bar1() {}
void Foo1::Inner::bar2() {}


struct __declspec(code_seg("foo_outer")) Foo2 {
  struct __declspec(code_seg("foo_inner")) Inner {
    void bar1();
    static void bar2();
  };
};
void Foo2::Inner::bar1() {}
void Foo2::Inner::bar2() {}


#pragma code_seg(push, "otherseg")
struct __declspec(code_seg("foo_outer")) Foo3 {
  struct Inner {
    void bar1();
    static void bar2();
  };
};
void Foo3::Inner::bar1() {}
void Foo3::Inner::bar2() {}


struct __declspec(code_seg("foo_outer")) Foo4 {
  struct __declspec(code_seg("foo_inner")) Inner {
    void bar1();
    static void bar2();
  };
};
void Foo4::Inner::bar1() {}
void Foo4::Inner::bar2() {}


#pragma code_seg(pop)
struct __declspec(code_seg("foo_outer")) Foo5 {
  struct Inner {
    void bar1();
    static void bar2();
    struct __declspec(code_seg("inner1_seg")) Inner1 {
      struct Inner2 {
        void bar1();
        static void bar2();
      };
    };
  };
};
void Foo5::Inner::bar1() {}
void Foo5::Inner::bar2() {}
void Foo5::Inner::Inner1::Inner2::bar1() {}
void Foo5::Inner::Inner1::Inner2::bar2() {}


