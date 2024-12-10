// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

struct A {
  ~A();
};

struct B {
  A a;
};

struct C {
  union {
    B b;
  };

  ~C() noexcept;
};

C::~C() noexcept {}
