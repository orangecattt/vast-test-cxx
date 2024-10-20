// RUN: %driver -cc1 %isys %s -fexceptions -fcxx-exceptions -fexternc-nounwind -Wno-dynamic-exception-spec %std_cxx98- %target -o %t%output-suffix && %filecheck

namespace test1 {
struct Cleanup { ~Cleanup(); };
extern "C" void never_throws();
void may_throw();

void caller() {
  Cleanup x;
  never_throws();
  may_throw();
}
}
// CHECK-LABEL: define dso_local void @"?caller@test1@@YAXXZ"(
// CHECK: call void @never_throws(
// CHECK: invoke void @"?may_throw@test1@@YAXXZ"(

namespace test2 {
struct Cleanup { ~Cleanup(); };
extern "C" void throws_int() throw(int);
void may_throw();

void caller() {
  Cleanup x;
  throws_int();
  may_throw();
}
}
// CHECK-LABEL: define dso_local void @"?caller@test2@@YAXXZ"(
// CHECK: invoke void @throws_int(
// CHECK: invoke void @"?may_throw@test2@@YAXXZ"(
