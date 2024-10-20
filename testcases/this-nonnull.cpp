// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-delete-null-pointer-checks %s %target -o %t%output-suffix && %filecheck

struct Struct {
  int many;
  int member;
  int fields;
  void ReturnsVoid();
};

void TestReturnsVoid(Struct &s) {
  s.ReturnsVoid();

  // CHECK-YES: call void @_ZN6Struct11ReturnsVoidEv(ptr noundef nonnull align 4 dereferenceable(12) %0)
  /// FIXME Use dereferenceable after dereferenceable respects NullPointerIsValid.
  // CHECK-NO: call void @_ZN6Struct11ReturnsVoidEv(ptr noundef align 4 dereferenceable_or_null(12) %0)
}

// CHECK-YES: declare void @_ZN6Struct11ReturnsVoidEv(ptr noundef nonnull align 4 dereferenceable(12))
// CHECK-NO: declare void @_ZN6Struct11ReturnsVoidEv(ptr noundef align 4 dereferenceable_or_null(12))
