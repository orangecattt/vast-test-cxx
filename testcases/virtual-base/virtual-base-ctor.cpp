// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct B;
extern B x;
char y;
typedef __typeof(sizeof(int)) size_t;
struct A { int a; A() { y = ((size_t)this - (size_t)&x) / sizeof(void*); } };
struct B : virtual A { void* x; };    
B x;

