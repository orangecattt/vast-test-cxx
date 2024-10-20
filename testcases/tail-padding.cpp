// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace Implicit {
  struct A { char c; A(const A&); };
  struct B { int n; char c[3]; ~B(); };
  struct C : B, virtual A {};
  static_assert(sizeof(C) == sizeof(void*) + 8);
  C f(C c) { return c; }

}

namespace InitWithinNVSize {
  struct A { char c; A(const A&); };
  struct B { int n; char c[3]; ~B(); };
  struct C : B, virtual A { char x; };
  static_assert(sizeof(C) > sizeof(void*) + 8);
  C f(C c) { return c; }

}

namespace NoUniqueAddr {
  struct A { char c; A(const A&); };
  struct B { int n; char c[3]; ~B(); };
  struct C : virtual A { B b; };
  struct D : virtual A { [[no_unique_address]] B b; };
  struct E : virtual A { [[no_unique_address]] B b; char x; };
  static_assert(sizeof(C) == sizeof(void*) + 8 + alignof(void*));
  static_assert(sizeof(D) == sizeof(void*) + 8);
  static_assert(sizeof(E) == sizeof(void*) + 8 + alignof(void*));

  C f(C c) { return c; }

  D f(D d) { return d; }

  E f(E e) { return e; }

  struct F : virtual A {
    F(const F &o) : A(o), b(o.b) {}
    [[no_unique_address]] B b;
  };

  F f(F x) { return x; }
}
