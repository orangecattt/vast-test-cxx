// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct X {
  X();
  ~X();
};

struct Y {
  Y();
  ~Y();
};

// CHECK-LABEL: define{{.*}} void @_Z1fiPPKc(
void f(int argc, const char* argv[]) {
  // CHECK: call void @_ZN1XC1Ev
  X x;
  // CHECK: call ptr @llvm.stacksave.p0(
  const char *argv2[argc];
  // CHECK: call void @_ZN1YC1Ev
  Y y;
  for (int i = 0; i != argc; ++i)
    argv2[i] = argv[i];

  // CHECK: call void @_ZN1YD1Ev
  // CHECK: call void @llvm.stackrestore.p0
  // CHECK: call void @_ZN1XD1Ev
  // CHECK: ret void
}

namespace PR11744 {
  // Make sure this doesn't crash; there was a use-after-free issue
  // for this testcase.
  template<typename T> int f(int n) {
    T arr[3][n];
    return 3;
  }
  int test = f<int>(0);
}
