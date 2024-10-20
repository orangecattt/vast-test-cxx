// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// CHECK: @llvm.global_ctors

// PR6521
void bar();
struct Foo {
  // CHECK-LABEL: define linkonce_odr {{.*}}void @_ZN3Foo3fooEv
  static void foo() __attribute__((constructor)) {
    bar();
  }
};
