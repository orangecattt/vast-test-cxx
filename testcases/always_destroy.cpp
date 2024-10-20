// RUN: %driver -cc1 %isys %s -fno-c++-static-destructors %target -o %t%output-suffix && %filecheck

struct NonTrivial {
  ~NonTrivial();
};

// CHECK-NOT: __cxa_atexit{{.*}}_ZN10NonTrivialD1Ev
NonTrivial nt1;
// CHECK-NOT: _tlv_atexit{{.*}}_ZN10NonTrivialD1Ev
thread_local NonTrivial nt2;

struct NonTrivial2 {
  ~NonTrivial2();
};

// CHECK: __cxa_atexit{{.*}}_ZN11NonTrivial2D1Ev
[[clang::always_destroy]] NonTrivial2 nt21;
// CHECK: _tlv_atexit{{.*}}_ZN11NonTrivial2D1Ev
[[clang::always_destroy]] thread_local NonTrivial2 nt22;

void f() {
  // CHECK: __cxa_atexit{{.*}}_ZN11NonTrivial2D1Ev
  [[clang::always_destroy]] static NonTrivial2 nt21;
  // CHECK: _tlv_atexit{{.*}}_ZN11NonTrivial2D1Ev
  [[clang::always_destroy]] thread_local NonTrivial2 nt22;
}

// CHECK-NOT: __cxa_atexit{{.*}}_ZN10NonTrivialD1Ev
[[clang::no_destroy]] NonTrivial nt3;
// CHECK-NOT: _tlv_atexit{{.*}}_ZN10NonTrivialD1Ev
[[clang::no_destroy]] thread_local NonTrivial nt4;
