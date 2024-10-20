// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck

struct X {
  X();
  ~X();
};

struct Y { };

void f() {
  static X x;

  throw Y();

}
