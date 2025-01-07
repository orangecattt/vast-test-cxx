// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

void foo(int);

class A {
public:
  A() { foo(1); }
};

class A1 {
public:
  A1() { foo(2); }
};

class B {
public:
  B() { foo(3); }
};

class C {
public:
  static A a;
  C() { foo(4); }
};


A C::a = A();





C c;
A1 a1 __attribute__((init_priority (300)));
A a __attribute__((init_priority (300)));
B b __attribute__((init_priority (200)));
