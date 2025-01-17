// RUN: %driver -cc1 %isys -flto -flto-unit -fvirtual-function-elimination -fwhole-program-vtables %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -flto -fvirtual-function-elimination -fno-virtual-function-elimination -fwhole-program-vtables %s %target -S -o %t%output-suffix && %filecheck

struct __attribute__((visibility("default"))) A {
  virtual void foo();
};

void test_1(A *p) {
  p->foo();
}


struct __attribute__((visibility("hidden"))) [[clang::lto_visibility_public]] B {
  virtual void foo();
};

void test_2(B *p) {
  p->foo();
}


struct __attribute__((visibility("hidden"))) C {
  virtual void foo();
  virtual void bar();
};

void test_3(C *p) {
  p->foo();
}

void test_4(C *p) {
  p->bar();
}

void test_5(C *p, void (C::*q)(void)) {

  (p->*q)();
}
