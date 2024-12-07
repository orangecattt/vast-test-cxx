// RUN: %driver -cc1 %isys -std=c++1y %s %target -o %t%output-suffix && %filecheck

struct A {
  int n = 0;
  const char *p;
  char k = p[n];
  int f();
  int x = f();
  union {
    char c;
    double d = 1.0;
  };
};

int f();

union B {
  int a;
  int f();
  int b = f();
};

A a { .p = "foobar" };
A b { 4, "bazquux", .x = 42, .c = 9 };
A c { 1, 0, 'A', f(), { 3 } };



B x;
B y {};
B z { 1 };

union C {
  struct {
    int C::*memptr;
  };
};

C n{};








