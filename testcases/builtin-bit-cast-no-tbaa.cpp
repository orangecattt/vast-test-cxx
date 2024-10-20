// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

void test_scalar() {
  // CHECK-LABEL: define{{.*}} void @_Z11test_scalarv
  __builtin_bit_cast(float, 42);

  // CHECK: load float, ptr {{.*}}, align 4, !tbaa ![[MAY_ALIAS_TBAA:.*]]
}

void test_scalar2() {
  // CHECK-LABEL: define{{.*}} void @_Z12test_scalar2v
  struct S {int m;};
  __builtin_bit_cast(int, S{42});

  // CHECK: load i32, ptr {{.*}}, align 4, !tbaa ![[MAY_ALIAS_TBAA]]
}

int test_same_type(int &r) {
  // CHECK: load i32, ptr {{.*}}, align 4, !tbaa ![[MAY_ALIAS_TBAA]]
  return __builtin_bit_cast(int, r);
}

// CHECK: ![[CHAR_TBAA:.*]] = !{!"omnipotent char", {{.*}}, i64 0}
// CHECK: ![[MAY_ALIAS_TBAA]] = !{![[CHAR_TBAA]], ![[CHAR_TBAA]], i64 0}
