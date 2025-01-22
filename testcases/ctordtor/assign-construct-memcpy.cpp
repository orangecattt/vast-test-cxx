// RUN: %driver -cc1 %isys -std=c++11 %s -DPOD %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

typedef __typeof__(sizeof(0)) size_t;
void *operator new(size_t, void*) throw();
void operator delete(void*, void*) throw();
void *operator new[](size_t, void*) throw();
void operator delete[](void*, void*) throw();
template<typename T> T &&move(T&);

struct foo {
#ifndef POD
  foo() {} // non-POD
#endif
  void *a, *b;
  bool c;
};


foo *test1(void *f, const foo &x) {
  return new (f) foo(x);

}

foo *test2(const foo &x) {
  return new foo(x);

}

foo test3(const foo &x) {
  foo f = x;
  return f;

}

foo *test4(foo &&x) {
  return new foo(x);

}

void test5(foo &f, const foo &x) {
  f = x;

}

extern foo globtest;

void test6(foo &&x) {
  globtest = move(x);

}

void byval(foo f);

void test7(const foo &x) {
  byval(x);

}
