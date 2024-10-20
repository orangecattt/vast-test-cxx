// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

// This code used to cause an assertion failure in EmitDelegateCallArg.

// CHECK-LABEL: define internal void @"?__invoke@<lambda_0>@?0??test@@YAXXZ@CA@UTrivial@@@Z"(
// CHECK: %unused.capture = alloca %class.anon, align 1
// CHECK: call void @"??R<lambda_0>@?0??test@@YAXXZ@QEBA@UTrivial@@@Z"(ptr noundef nonnull align 1 dereferenceable(1) %unused.capture,

// CHECK: define internal void @"??R<lambda_0>@?0??test@@YAXXZ@QEBA@UTrivial@@@Z"(ptr noundef nonnull align 1 dereferenceable(1) %this,

struct Trivial {
  int x;
};

void (*fnptr)(Trivial);

void test() {
  fnptr = [](Trivial a){ (void)a; };
}

// CHECK-LABEL: define internal i32 @"?__invoke@<lambda_1>@?0??test2@@YAXXZ@CA@H@Z"(
// CHECK: %unused.capture = alloca %class.anon.0, align 1
// CHECK: call void @"??R<lambda_1>@?0??test2@@YAXXZ@QEBA@H@Z"(ptr noundef nonnull align 1 dereferenceable(1) %unused.capture,

// CHECK: define internal void @"??R<lambda_1>@?0??test2@@YAXXZ@QEBA@H@Z"(ptr noundef nonnull align 1 dereferenceable(1) %this,

Trivial (*fnptr2)(int);

void test2() {
  fnptr2 = [](int) -> Trivial { return {}; };
}
