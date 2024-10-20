// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
namespace foo {

extern "C" int a;

extern int b;

int c = 5;

extern "C" struct d;

extern "C++" int should_not_appear;

extern "C++" int extern_cxx = 0;

}

extern "C" int global_a;

extern "C" int global_b = 0;

extern "C++" int should_not_appear;

extern "C++" int extern_cxx = 0;

namespace test1 {
  namespace {
    struct X {};
  }
  extern "C" {
    X test1_b = X();
  }
  void *use = &test1_b;
}

namespace test2 {
  namespace {
    struct X {};
  }

  extern "C" X test2_b;
  X test2_b;
}

extern "C" {
  static int unused_var;
  static int unused_fn() { return 0; }

  __attribute__((used)) static int internal_var;
  __attribute__((used)) static int internal_fn() { return 0; }

  __attribute__((used)) static int duplicate_internal_var;
  __attribute__((used)) static int duplicate_internal_fn() { return 0; }

  namespace N {
    __attribute__((used)) static int duplicate_internal_var;
    __attribute__((used)) static int duplicate_internal_fn() { return 0; }
  }


}

namespace PR19411 {
  struct A { void f(); };
  extern "C" void A::f() { void g(); g(); }
}
