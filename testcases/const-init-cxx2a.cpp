// RUN: %driver -cc1 %isys %s -std=c++2a %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -emit-pch %s -std=c++2a -o %t.pch
// RUN: %driver -cc1 %isys -include-pch %t.pch -x c++ /dev/null -std=c++2a %target -o %t%output-suffix && %filecheck

// CHECK: @a ={{.*}} global i32 123,
int a = (delete new int, 123);

struct B {
  constexpr B() {}
  constexpr ~B() { n *= 5; }
  int n = 123;
};
// CHECK: @b ={{.*}} constant {{.*}} i32 123
extern constexpr B b = B();

// CHECK: @_ZL1c = internal constant {{.*}} i32 123
const B c;
int use_c() { return c.n; }

struct D {
  int n;
  constexpr ~D() {}
};
D d;
// CHECK: @d ={{.*}} global {{.*}} zeroinitializer

D d_arr[3];
// CHECK: @d_arr ={{.*}} global {{.*}} zeroinitializer

thread_local D d_tl;
// CHECK: @d_tl ={{.*}} thread_local global {{.*}} zeroinitializer

// CHECK-NOT: @llvm.global_ctors

// CHECK-LABEL: define {{.*}} @_Z1fv(
void f() {
  // CHECK-NOT: call
  // CHECK: call {{.*}}memcpy
  // CHECK-NOT: call
  // CHECK: call {{.*}}memset
  // CHECK-NOT: call
  // CHECK: }
  constexpr B b;
  D d = D();
}

// CHECK-LABEL: define {{.*}} @_Z1gv(
void g() {
  // CHECK-NOT: call
  // CHECK-NOT: cxa_guard
  // CHECK-NOT: _ZGV
  // CHECK: }
  static constexpr B b1;
  static const B b2;
  static D d;
  thread_local D d_tl;
}
