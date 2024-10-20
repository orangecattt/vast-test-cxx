// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

#include "Inputs/std-compare.h"

// Ensure we don't emit definitions for the global variables
// since the builtins shouldn't ODR use them.
// CHECK-NOT: constant %[[SO]]
// CHECK-NOT: constant %[[PO]]

// CHECK-LABEL: @_Z11test_signedii
auto test_signed(int x, int y) {
  // CHECK: %[[DEST:retval|agg.result]]
  // CHECK: %cmp.lt = icmp slt i32 %{{.+}}, %{{.+}}
  // CHECK: %sel.lt = select i1 %cmp.lt, i8 [[LT]], i8 [[GT]]
  // CHECK: %cmp.eq = icmp eq i32 %{{.+}}, %{{.+}}
  // CHECK: %sel.eq = select i1 %cmp.eq, i8 [[EQ]], i8 %sel.lt
  // CHECK: %__value_ = getelementptr inbounds %[[SO]], ptr %[[DEST]]
  // CHECK: store i8 %sel.eq, ptr %__value_, align 1
  // CHECK: ret
  return x <=> y;
}

// CHECK-LABEL: @_Z13test_unsignedjj
auto test_unsigned(unsigned x, unsigned y) {
  // CHECK: %[[DEST:retval|agg.result]]
  // CHECK: %cmp.lt = icmp ult i32 %{{.+}}, %{{.+}}
  // CHECK: %sel.lt = select i1 %cmp.lt, i8 [[LT]], i8 [[GT]]
  // CHECK: %cmp.eq = icmp eq i32 %{{.+}}, %{{.+}}
  // CHECK: %sel.eq = select i1 %cmp.eq, i8 [[EQ]], i8 %sel.lt
  // CHECK: %__value_ = getelementptr inbounds %[[SO]], ptr %[[DEST]]
  // CHECK: store i8 %sel.eq, ptr %__value_
  // CHECK: ret
  return x <=> y;
}

// CHECK-LABEL: @_Z10float_testdd
auto float_test(double x, double y) {
  // CHECK: %[[DEST:retval|agg.result]]
  // CHECK: %cmp.eq = fcmp oeq double %{{.+}}, %{{.+}}
  // CHECK: %sel.eq = select i1 %cmp.eq, i8 [[EQ]], i8 [[UNORD]]
  // CHECK: %cmp.gt = fcmp ogt double %{{.+}}, %{{.+}}
  // CHECK: %sel.gt = select i1 %cmp.gt, i8 [[GT]], i8 %sel.eq
  // CHECK: %cmp.lt = fcmp olt double %{{.+}}, %{{.+}}
  // CHECK: %sel.lt = select i1 %cmp.lt, i8 [[LT]], i8 %sel.gt
  // CHECK: %__value_ = getelementptr inbounds %[[PO]], ptr %[[DEST]]
  // CHECK: store i8 %sel.lt, ptr %__value_
  // CHECK: ret
  return x <=> y;
}

// CHECK-LABEL: @_Z8ptr_testPiS_
auto ptr_test(int *x, int *y) {
  // CHECK: %[[DEST:retval|agg.result]]
  // CHECK: %cmp.lt = icmp ult ptr %{{.+}}, %{{.+}}
  // CHECK: %sel.lt = select i1 %cmp.lt, i8 [[LT]], i8 [[GT]]
  // CHECK: %cmp.eq = icmp eq ptr %{{.+}}, %{{.+}}
  // CHECK: %sel.eq = select i1 %cmp.eq, i8 [[EQ]], i8 %sel.lt
  // CHECK: %__value_ = getelementptr inbounds %[[SO]], ptr %[[DEST]]
  // CHECK: store i8 %sel.eq, ptr %__value_, align 1
  // CHECK: ret
  return x <=> y;
}

// CHECK-LABEL: @_Z13test_constantv
auto test_constant() {
  // CHECK: %[[DEST:retval|agg.result]]
  // CHECK-NOT: icmp
  // CHECK: %__value_ = getelementptr inbounds %[[SO]], ptr %[[DEST]]
  // CHECK-NEXT: store i8 -1, ptr %__value_
  // CHECK: ret
  const int x = 42;
  const int y = 101;
  return x <=> y;
}

// CHECK-LABEL: @_Z18unscoped_enum_testijxy
void unscoped_enum_test(int i, unsigned u, long long l, unsigned long long ul) {
  enum EnumA : int { A };
  enum EnumB : unsigned { B };
  // CHECK: %[[I:.*]] = load {{.*}} %i.addr
  // CHECK: icmp slt i32 {{.*}} %[[I]]
  (void)(A <=> i);

  // CHECK: %[[U:.*]] = load {{.*}} %u.addr
  // CHECK: icmp ult i32 {{.*}} %[[U]]
  (void)(A <=> u);

  // CHECK: %[[L:.*]] = load {{.*}} %l.addr
  // CHECK: icmp slt i64 {{.*}} %[[L]]
  (void)(A <=> l);

  // CHECK: %[[U2:.*]] = load {{.*}} %u.addr
  // CHECK: icmp ult i32 {{.*}} %[[U2]]
  (void)(B <=> u);

  // CHECK: %[[UL:.*]] = load {{.*}} %ul.addr
  // CHECK: icmp ult i64 {{.*}} %[[UL]]
  (void)(B <=> ul);
}
