// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void f(void) {}

[[gnu::flatten]]
// CHECK: define{{.*}} void @_Z1gv()
void g(void) {
  // CHECK-NOT: call {{.*}} @_Z1fv
  f();
}
