// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck

struct X { };

const X g();

void f() {
  try {
    throw g();
  } catch (const X x) {
  }
}

void h() {
  try {
    throw "ABC";
  } catch (char const(&)[4]) {
  }
}
