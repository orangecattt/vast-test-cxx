// RUN: %driver -cc1 %isys -no-enable-noundef-analysis %s %target -o %t%output-suffix && %filecheck

void __attribute__((fastcall)) foo1(int &y);
void bar1(int &y) {
  // CHECK-LABEL: define{{.*}} void @_Z4bar1Ri
  // CHECK: call x86_fastcallcc void @_Z4foo1Ri(ptr inreg nonnull align {{[0-9]+}} dereferenceable({{[0-9]+}}) %
  foo1(y);
}

struct S1 {
  int x;
  S1(const S1 &y);
};

void __attribute__((fastcall)) foo2(S1 a, int b);
void bar2(S1 a, int b) {
  // CHECK-LABEL: define{{.*}} void @_Z4bar22S1i
  // CHECK: call x86_fastcallcc void @_Z4foo22S1i(ptr inreg %{{.*}}, i32 inreg %
  foo2(a, b);
}
