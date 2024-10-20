// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions -Wno-unreachable-code -Werror %s %target -o %t%output-suffix && %filecheck

int val = 42;
int& test1() {
  return throw val, val;
}

int test2() {
  return val ? throw val : val;
}

void test3() {
  throw false;
}

int test4() {
  return 1 ? throw val : val;
}

int test5(bool x, bool y, int z) {
  return (x ? throw 1 : y) ? z : throw 2;
}

int test6(bool x, bool y, int z) {
  return (x ? throw 1 : y) ? z : (throw 2);
}

namespace DR1560 {
  struct A {
    ~A();
  };
  extern bool b;
  A get();
  const A &r = b ? get() : throw 0;

  void conditional_throw() {
    int a;
    (true ? throw 0 : a) = 0; // CHECK: call void @__cxa_throw({{.*}})
  }
}

void test7(bool cond) {
  cond ? throw test7 : val;
}

int &test8(bool cond) {
  return cond ? val : ((throw "foo"));
}
