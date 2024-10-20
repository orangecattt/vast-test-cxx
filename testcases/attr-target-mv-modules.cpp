// RUN: %driver -cc1 %isys -std=c++11 -fmodules %s %target -o %t%output-suffix && %filecheck
#pragma clang module build A
module A {}
#pragma clang module contents
#pragma clang module begin A
__attribute__((target("default"))) void f();
__attribute__((target("sse4.2"))) void f();
#pragma clang module end
#pragma clang module endbuild

#pragma clang module build B
module B {}
#pragma clang module contents
#pragma clang module begin B
__attribute__((target("default"))) void f();
__attribute__((target("sse4.2"))) void f();
#pragma clang module end
#pragma clang module endbuild

#pragma clang module import A
#pragma clang module import B
void g() { f(); }

// Negative tests to validate that the resolver only calls each 1x.
// CHECK: define weak_odr ptr @_Z1fv.resolver
// CHECK: ret ptr @_Z1fv.sse4.2
// CHECK-NOT: ret ptr @_Z1fv.sse4.2
// CHECK: ret ptr @_Z1fv
// CHECK-NOT: ret ptr @_Z1fv