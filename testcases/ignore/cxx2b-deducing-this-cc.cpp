// RUN: %driver -cc1 %isys -std=c++2b %s %target -o %t%output-suffix && %filecheck

namespace CC {

struct T {
   static void f(T&);
   void __cdecl g(this T&);
   void __thiscall h(this T&);
   void i(this T&);
};

void a() {
    T t;
    T::f(t);
}

void b() {
    T t;
    t.g();
}

void c() {
    T t;
    t.h();
}

void d() {
    T t;
    t.i();
}

}
