// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" {
int f();
int g();
}

struct A {
  A(int, int);
};


void foo() {
  A a{f(), g()};
}
// CHECK-ITANIUM-LABEL: define{{.*}} void @_Z3foov
// CHECK-MS-LABEL: define dso_local void @"?foo@@YAXXZ"
// CHECK: call i32 @f()
// CHECK: call i32 @g()

struct B : A {
  B();
};
B::B() : A{f(), g()} {}
// CHECK-ITANIUM-LABEL: define{{.*}} void @_ZN1BC2Ev
// CHECK-MS-LABEL: define dso_local x86_thiscallcc noundef ptr @"??0B@@QAE@XZ"
// CHECK: call i32 @f()
// CHECK: call i32 @g()