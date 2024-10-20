// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck

struct X { };

const X g();

void f() {
  try {
    throw g();
    // CHECK: @_ZTI1X
  } catch (const X x) {
  }
}

void h() {
  try {
    throw "ABC";
    // CHECK: @_ZTIPKc
  } catch (char const(&)[4]) {
  }
}
