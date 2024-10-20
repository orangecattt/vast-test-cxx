// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck


struct A { int n; };
struct B { int n; };
class X { private: int n; };
struct C : A, B { A a; X x; int f, g; };

template<typename ...T> int format(int a, const char *str, T ...);

int f();

void g(C &c) {



















  __builtin_dump_struct(&c, format, f());
}

void h(X &x) {



  __builtin_dump_struct(&x, format, 0);
}
