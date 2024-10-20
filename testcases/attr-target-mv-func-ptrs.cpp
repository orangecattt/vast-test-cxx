// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
void temp();
void temp(int);
using FP = void(*)(int);
void b() {
  FP f = temp; 
}

int __attribute__((target("sse4.2"))) foo(int) { return 0; }
int __attribute__((target("arch=sandybridge"))) foo(int);
int __attribute__((target("arch=ivybridge"))) foo(int) {return 1;}
int __attribute__((target("default"))) foo(int) { return 2; }

struct S {
int __attribute__((target("sse4.2"))) foo(int) { return 0; }
int __attribute__((target("arch=sandybridge"))) foo(int);
int __attribute__((target("arch=ivybridge"))) foo(int) {return 1;}
int __attribute__((target("default"))) foo(int) { return 2; }
};

using FuncPtr = int (*)(int);
using MemFuncPtr = int (S::*)(int);

void f(FuncPtr, MemFuncPtr);

int bar() {
  FuncPtr Free = &foo;
  MemFuncPtr Member = &S::foo;
  S s;
  f(foo, &S::foo);
  return Free(1) + (s.*Member)(2);
}





