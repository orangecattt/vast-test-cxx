// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -std=c++1z %s %target -o %t%output-suffix && %filecheck

// CHECK-LABEL: define {{.*}} @_Z11builtin_newm(
// CHECK: call {{.*}} @_Znwm(
void *builtin_new(unsigned long n) { return __builtin_operator_new(n); }

// CHECK-LABEL: define {{.*}} @_Z14builtin_deletePv(
// CHECK: call {{.*}} @_ZdlPv(
void builtin_delete(void *p) { return __builtin_operator_delete(p); }
