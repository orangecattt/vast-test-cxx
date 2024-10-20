// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct A { A(int x = 2); };
struct B : public A {};
B x;

