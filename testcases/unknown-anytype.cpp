// RUN: %driver -cc1 %isys -funknown-anytype %s %target -o %t%output-suffix && %filecheck


int test0() {
  extern __unknown_anytype test0_any;
  return (int) test0_any;
}

int test1() {
  extern __unknown_anytype test1_any();
  return (int) test1_any();
}

extern "C" __unknown_anytype test2_any(...);
float test2() {
  return (float) test2_any(0.5f);
}

extern "C" __unknown_anytype test2a_any(...);
float test2a() {
  return (float) test2a_any((float) 0.5f);
}

float test3() {
  extern __unknown_anytype test3_any;
  return ((float(*)(int)) test3_any)(5);
}

namespace test4 {
  extern __unknown_anytype test4_any1;
  extern __unknown_anytype test4_any2;

  int test() {
    return (int) test4_any1 + (char) test4_any2;
  }
}

extern "C" __unknown_anytype test5_any();
void test5() {
  return (void) test5_any();
}

extern "C" __unknown_anytype test6_any(float *);
long test6() {
  return (long long) test6_any(0);
}

struct Test7 {
  ~Test7();
};
extern "C" __unknown_anytype test7_any(int);
Test7 test7() {
  return (Test7) test7_any(5);
}

struct Test8 {
  __unknown_anytype foo();
  __unknown_anytype foo(int);

  void test();
};
void Test8::test() {
  float f;
  f = (int) foo();
  f = (int) foo(5);
  f = (float) this->foo();
  f = (float) this->foo(5);
}
void test8(Test8 *p) {
  double d;
  d = (double) p->foo();
  d = (double) p->foo(5);
  d = (bool) (*p).foo();
  d = (bool) (*p).foo(5);
}

extern "C" __unknown_anytype test9_foo;
void *test9() {
  return (int*) &test9_foo;
}

extern "C" __unknown_anytype test10_any(...);
void test10() {
  (void) test10_any(), (void) test10_any();
}

extern "C" __unknown_anytype malloc(...);
void test11() {
  void *s = (void*)malloc(12);
  void *d = (void*)malloc(435);
}
