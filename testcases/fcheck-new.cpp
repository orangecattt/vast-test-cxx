// RUN: %driver -cc1 %isys -fcheck-new -disable-O0-optnone %s %target -o %t%output-suffix && %filecheck

struct A { A(); };

A *test0() {
  return new A();
}

int *test1() {
  return new int;
}
