// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// Check the atomic code generation for cpu targets w/wo cx16 support.

struct alignas(8) AM8 {
  int f1, f2;
};
AM8 m8;
AM8 load8() {
  AM8 am;
  // CHECK-LABEL: @_Z5load8v
  // CHECK: load atomic i64, {{.*}} monotonic, align 8
  // CORE2-LABEL: @_Z5load8v
  // CORE2: load atomic i64, {{.*}} monotonic, align 8
  __atomic_load(&m8, &am, 0);
  return am;
}

AM8 s8;
void store8() {
  // CHECK-LABEL: @_Z6store8v
  // CHECK: store atomic i64 {{.*}} monotonic, align 8
  // CORE2-LABEL: @_Z6store8v
  // CORE2: store atomic i64 {{.*}} monotonic, align 8
  __atomic_store(&m8, &s8, 0);
}

bool cmpxchg8() {
  AM8 am;
  // CHECK-LABEL: @_Z8cmpxchg8v
  // CHECK: cmpxchg ptr {{.*}} monotonic, align 8
  // CORE2-LABEL: @_Z8cmpxchg8v
  // CORE2: cmpxchg ptr {{.*}} monotonic, align 8
  return __atomic_compare_exchange(&m8, &s8, &am, 0, 0, 0);
}

struct alignas(16) AM16 {
  long f1, f2;
};

AM16 m16;
AM16 load16() {
  AM16 am;
  // CHECK-LABEL: @_Z6load16v
  // CHECK: call void @__atomic_load
  // CORE2-LABEL: @_Z6load16v
  // CORE2: load atomic i128, {{.*}} monotonic, align 16
  __atomic_load(&m16, &am, 0);
  return am;
}

AM16 s16;
void store16() {
  // CHECK-LABEL: @_Z7store16v
  // CHECK: call void @__atomic_store
  // CORE2-LABEL: @_Z7store16v
  // CORE2: store atomic i128 {{.*}} monotonic, align 16
  __atomic_store(&m16, &s16, 0);
}

bool cmpxchg16() {
  AM16 am;
  // CHECK-LABEL: @_Z9cmpxchg16v
  // CHECK: call noundef zeroext i1 @__atomic_compare_exchange
  // CORE2-LABEL: @_Z9cmpxchg16v
  // CORE2: cmpxchg ptr {{.*}} monotonic monotonic, align 16
  return __atomic_compare_exchange(&m16, &s16, &am, 0, 0, 0);
}