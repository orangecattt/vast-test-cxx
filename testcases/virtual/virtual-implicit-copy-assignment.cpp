// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct D;
struct B {
 virtual D& operator = (const D&);
};
struct D : B { D(); virtual void a(); };
void D::a() {}

