// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct A {
  A();
  A(const A&);
  ~A();
};

struct B {
  B();
  B(const B&);
  ~B();
};

struct C {
  C();
  C(const C&);
  ~C();
};

struct D {
  D();
  D(const D&);
  ~D();

  B *begin();
  B *end();
};

B *begin(C&);
B *end(C&);

extern B array[5];

// CHECK-LABEL: define {{[^@]+}}@_Z9for_arrayv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A:%.*]] = alloca [[STRUCT_A:%.*]], align 1
// CHECK-NEXT:    [[__RANGE1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__BEGIN1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__END1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B:%.*]] = alloca [[STRUCT_B:%.*]], align 1
// CHECK-NEXT:    call void @_ZN1AC1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[A]])
// CHECK-NEXT:    store ptr @array, ptr [[__RANGE1]], align 8
// CHECK-NEXT:    store ptr @array, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    store ptr getelementptr inbounds ([[STRUCT_B]], ptr @array, i64 5), ptr [[__END1]], align 8
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load ptr, ptr [[__END1]], align 8
// CHECK-NEXT:    [[CMP:%.*]] = icmp ne ptr [[TMP0]], [[TMP1]]
// CHECK-NEXT:    br i1 [[CMP]], label [[FOR_BODY:%.*]], label [[FOR_END:%.*]]
// CHECK:       for.body:
// CHECK-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    call void @_ZN1BC1ERKS_(ptr noundef nonnull align 1 dereferenceable(1) [[B]], ptr noundef nonnull align 1 dereferenceable(1) [[TMP2]])
// CHECK-NEXT:    call void @_ZN1BD1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[B]]) #[[ATTR3:[0-9]+]]
// CHECK-NEXT:    br label [[FOR_INC:%.*]]
// CHECK:       for.inc:
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    [[INCDEC_PTR:%.*]] = getelementptr inbounds [[STRUCT_B]], ptr [[TMP3]], i32 1
// CHECK-NEXT:    store ptr [[INCDEC_PTR]], ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    br label [[FOR_COND]]
// CHECK:       for.end:
// CHECK-NEXT:    call void @_ZN1AD1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[A]]) #[[ATTR3]]
// CHECK-NEXT:    ret void
//
void for_array() {
  A a;
  for (B b : array) {
  }
}

// CHECK-LABEL: define {{[^@]+}}@_Z9for_rangev(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A:%.*]] = alloca [[STRUCT_A:%.*]], align 1
// CHECK-NEXT:    [[__RANGE1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[REF_TMP:%.*]] = alloca [[STRUCT_C:%.*]], align 1
// CHECK-NEXT:    [[__BEGIN1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__END1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B:%.*]] = alloca [[STRUCT_B:%.*]], align 1
// CHECK-NEXT:    call void @_ZN1AC1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[A]])
// CHECK-NEXT:    call void @_ZN1CC1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[REF_TMP]])
// CHECK-NEXT:    store ptr [[REF_TMP]], ptr [[__RANGE1]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[__RANGE1]], align 8
// CHECK-NEXT:    [[CALL:%.*]] = call noundef ptr @_Z5beginR1C(ptr noundef nonnull align 1 dereferenceable(1) [[TMP0]])
// CHECK-NEXT:    store ptr [[CALL]], ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load ptr, ptr [[__RANGE1]], align 8
// CHECK-NEXT:    [[CALL1:%.*]] = call noundef ptr @_Z3endR1C(ptr noundef nonnull align 1 dereferenceable(1) [[TMP1]])
// CHECK-NEXT:    store ptr [[CALL1]], ptr [[__END1]], align 8
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[__END1]], align 8
// CHECK-NEXT:    [[CMP:%.*]] = icmp ne ptr [[TMP2]], [[TMP3]]
// CHECK-NEXT:    br i1 [[CMP]], label [[FOR_BODY:%.*]], label [[FOR_COND_CLEANUP:%.*]]
// CHECK:       for.cond.cleanup:
// CHECK-NEXT:    call void @_ZN1CD1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[REF_TMP]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_END:%.*]]
// CHECK:       for.body:
// CHECK-NEXT:    [[TMP4:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    call void @_ZN1BC1ERKS_(ptr noundef nonnull align 1 dereferenceable(1) [[B]], ptr noundef nonnull align 1 dereferenceable(1) [[TMP4]])
// CHECK-NEXT:    call void @_ZN1BD1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[B]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_INC:%.*]]
// CHECK:       for.inc:
// CHECK-NEXT:    [[TMP5:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    [[INCDEC_PTR:%.*]] = getelementptr inbounds [[STRUCT_B]], ptr [[TMP5]], i32 1
// CHECK-NEXT:    store ptr [[INCDEC_PTR]], ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    br label [[FOR_COND]]
// CHECK:       for.end:
// CHECK-NEXT:    call void @_ZN1AD1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[A]]) #[[ATTR3]]
// CHECK-NEXT:    ret void
//
void for_range() {
  A a;
  for (B b : C()) {
  }
}

// CHECK-LABEL: define {{[^@]+}}@_Z16for_member_rangev(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A:%.*]] = alloca [[STRUCT_A:%.*]], align 1
// CHECK-NEXT:    [[__RANGE1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[REF_TMP:%.*]] = alloca [[STRUCT_D:%.*]], align 1
// CHECK-NEXT:    [[__BEGIN1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[__END1:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B:%.*]] = alloca [[STRUCT_B:%.*]], align 1
// CHECK-NEXT:    call void @_ZN1AC1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[A]])
// CHECK-NEXT:    call void @_ZN1DC1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[REF_TMP]])
// CHECK-NEXT:    store ptr [[REF_TMP]], ptr [[__RANGE1]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[__RANGE1]], align 8
// CHECK-NEXT:    [[CALL:%.*]] = call noundef ptr @_ZN1D5beginEv(ptr noundef nonnull align 1 dereferenceable(1) [[TMP0]])
// CHECK-NEXT:    store ptr [[CALL]], ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load ptr, ptr [[__RANGE1]], align 8
// CHECK-NEXT:    [[CALL1:%.*]] = call noundef ptr @_ZN1D3endEv(ptr noundef nonnull align 1 dereferenceable(1) [[TMP1]])
// CHECK-NEXT:    store ptr [[CALL1]], ptr [[__END1]], align 8
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[__END1]], align 8
// CHECK-NEXT:    [[CMP:%.*]] = icmp ne ptr [[TMP2]], [[TMP3]]
// CHECK-NEXT:    br i1 [[CMP]], label [[FOR_BODY:%.*]], label [[FOR_COND_CLEANUP:%.*]]
// CHECK:       for.cond.cleanup:
// CHECK-NEXT:    call void @_ZN1DD1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[REF_TMP]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_END:%.*]]
// CHECK:       for.body:
// CHECK-NEXT:    [[TMP4:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    call void @_ZN1BC1ERKS_(ptr noundef nonnull align 1 dereferenceable(1) [[B]], ptr noundef nonnull align 1 dereferenceable(1) [[TMP4]])
// CHECK-NEXT:    call void @_ZN1BD1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[B]]) #[[ATTR3]]
// CHECK-NEXT:    br label [[FOR_INC:%.*]]
// CHECK:       for.inc:
// CHECK-NEXT:    [[TMP5:%.*]] = load ptr, ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    [[INCDEC_PTR:%.*]] = getelementptr inbounds [[STRUCT_B]], ptr [[TMP5]], i32 1
// CHECK-NEXT:    store ptr [[INCDEC_PTR]], ptr [[__BEGIN1]], align 8
// CHECK-NEXT:    br label [[FOR_COND]]
// CHECK:       for.end:
// CHECK-NEXT:    call void @_ZN1AD1Ev(ptr noundef nonnull align 1 dereferenceable(1) [[A]]) #[[ATTR3]]
// CHECK-NEXT:    ret void
//
void for_member_range() {
  A a;
  for (B b : D()) {
  }
}
