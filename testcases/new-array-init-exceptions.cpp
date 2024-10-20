// RUN: %driver -cc1 %isys -std=c++11 -fexceptions -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// REQUIRES: asserts

struct Throws {
  Throws(int);
  Throws();
  ~Throws();
};

// CHECK-LABEL: define{{.*}} void @_Z7cleanupi
void cleanup(int n) {
  // CHECK: invoke void @_ZN6ThrowsC1Ei
  // CHECK-NEXT: to label %{{[^ ]+}} unwind label %[[LPAD:[^ ]+]]
  // CHECK: invoke void @_ZN6ThrowsC1Ei
  // CHECK-NEXT: to label %{{[^ ]+}} unwind label %[[LPAD]]
  // CHECK: invoke void @_ZN6ThrowsC1Ei
  // CHECK-NEXT: to label %{{[^ ]+}} unwind label %[[LPAD]]
  // CHECK: invoke void @_ZN6ThrowsC1Ev
  // CHECK-NEXT: to label %{{[^ ]+}} unwind label %[[LPAD]]
  new Throws[n] { 1, 2, 3 };
  // CHECK: [[LPAD]]:
  // CHECK-NEXT: landingpad
  // CHECK: call void @_ZN6ThrowsD1Ev
  // CHECK: call void @_ZdaPv
}


// CHECK-LABEL: define{{.*}} void @_Z7cleanupv
void cleanup() {
  // CHECK: invoke void @_ZN6ThrowsC1Ei
  // CHECK-NEXT: to label %{{[^ ]+}} unwind label %[[LPAD2:[^ ]+]]
  // CHECK: invoke void @_ZN6ThrowsC1Ei
  // CHECK-NEXT: to label %{{[^ ]+}} unwind label %[[LPAD2]]
  // CHECK: invoke void @_ZN6ThrowsC1Ei
  // CHECK-NEXT: to label %{{[^ ]+}} unwind label %[[LPAD2]]
  new Throws[3] { 1, 2, 3 };
  // CHECK: [[LPAD2]]:
  // CHECK-NEXT: landingpad
  // CHECK: call void @_ZN6ThrowsD1Ev
  // CHECK: call void @_ZdaPv
}
