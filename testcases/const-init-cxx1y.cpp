// RUN: %driver -cc1 %isys %s -std=c++1y %target -o %t%output-suffix && %filecheck

struct A {
  constexpr A() : n(1) {}
  ~A();
  int n;
};
struct B : A {
  A a[3];
  constexpr B() {
    ++a[0].n;
    a[1].n += 2;
    a[2].n = n + a[1].n;
  }
};
B b;


namespace ModifyStaticTemporary {
  struct A { int &&temporary; int x; };
  constexpr int f(int &r) { r *= 9; return r - 12; }
  A a = { 6, f(a.temporary) };

  A b = { 7, ++b.temporary };

  A c = { 10, (++c.temporary, b.x) };
}

namespace VariableTemplateWithConstRef {
  template <typename T>
  const int &i = 5;
  const int &use = i<void>;
}

namespace HiddenVariableTemplateWithConstRef {
  template <typename T>
  __attribute__((visibility("hidden"))) const int &i = 5;
  const int &use = i<void>;
}

namespace VariableTemplateWithPack {
  struct A {
    const int &r;
  };
  struct S {
    A &&a, &&b, &&c, &&d;
  };
  template <int... N>
  S &&s = {A{N}...};
  S *p = &s<1, 2, 3, 4>;
}


typedef int v[2];
struct Z { int &&x, y; };
Z z = { v{1,2}[0], z.x = 10 };

struct R { mutable long x; };
struct Z2 { const R &x, y; };
Z2 z2 = { R{1}, z2.x.x = 10 };


