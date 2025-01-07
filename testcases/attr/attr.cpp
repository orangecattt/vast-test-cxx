// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


int foo() __attribute__((aligned(1024)));
int foo() { }

class C {
  virtual void bar1() __attribute__((aligned(1)));
  virtual void bar2() __attribute__((aligned(2)));
  virtual void bar3() __attribute__((aligned(1024)));
  void bar4() __attribute__((aligned(1024)));
} c;

void C::bar1() { }

void C::bar2() { }

void C::bar3() { }

void C::bar4() { }

int test1() { return 10; }
extern "C" int test2() __attribute__((alias("_Z5test1v")));

