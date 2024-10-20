// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
void f(bool flag) {
  int a = 1;
  int b = 2;
  
  (flag ? a : b) = 3;
}

namespace test0 {
  struct A {
    A(const A &);
    A &operator=(const A &);
    A sub() const;
    void foo() const;
  };
  void foo(bool cond, const A &a) {
    (cond ? a : a.sub()).foo();
  }
}
