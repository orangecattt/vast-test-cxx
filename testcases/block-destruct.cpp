// RUN: %driver -cc1 %isys %s -fblocks %target -o %t%output-suffix && %filecheck

struct A { ~A(); };

void f() {
  __block A a;
}

// CHECK: call void @_ZN1AD1Ev
