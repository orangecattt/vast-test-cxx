// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// expected-no-diagnostics

struct A {};
struct B : A {};
void a(const A& x = B());
void b() { a(); }
