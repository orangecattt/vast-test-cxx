// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
#include <stddef.h>

struct X {static void * operator new(size_t size) throw(); X(int); };
int a(), b();
void b(int x)
{
  new X(x ? a() : b());
}

