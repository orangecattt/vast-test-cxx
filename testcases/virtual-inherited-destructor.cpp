// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { virtual ~A(); };
struct B : A {
  ~B() { }
};
B x;

