// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { int a; virtual int aa(); };
struct B { int b; virtual int bb(); };
struct C : virtual A, virtual B { int c; virtual int aa(); virtual int bb(); };
struct AA { int a; virtual int aa(); };
struct BB { int b; virtual int bb(); };
struct CC : AA, BB { virtual int aa(); virtual int bb(); virtual int cc(); };
struct D : virtual C, virtual CC { int e; };

D* x;

A* a() { return x; }


B* b() { return x; }



BB* c() { return x; }


struct E { int e; };
struct F : E, D { int f; };

F* y;

BB* d() { return y; }


