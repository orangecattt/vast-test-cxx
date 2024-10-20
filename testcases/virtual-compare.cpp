// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

#include "Inputs/std-compare.h"

struct A;
struct X {
  virtual void x();
  friend auto operator<=>(X, X) = default;
};
struct Y {
  virtual ~Y();
  virtual A &operator=(const A &);
  friend auto operator<=>(Y, Y) = default;
};
struct A : X, Y {
  virtual void f();
  virtual std::strong_ordering operator<=>(const A &) const & = default;
  virtual void g();
  virtual void h();



};




void A::f() {}
