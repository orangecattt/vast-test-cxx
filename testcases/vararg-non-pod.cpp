// RUN: %driver -cc1 %isys -Wno-error=non-pod-varargs %s %target -o %t%output-suffix && %filecheck

struct X {
  X();
  X(const X&);
  ~X();
};

void vararg(...);

// CHECK-LABEL: define {{.*}}void @_Z4test1X
void test(X x) {
  // CHECK: call void @llvm.trap()
  vararg(x);
  // CHECK: ret void
}
