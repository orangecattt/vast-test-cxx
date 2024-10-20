// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++98 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck

// Reduced from a crash on boost::interprocess's node_allocator_test.cpp.
namespace test0 {
  struct A { A(); ~A(); };
  struct V { V(const A &a = A()); ~V(); };

  // CHECK-LABEL: define linkonce_odr noundef i32 @_ZN5test04testILi0EEEii
  template<int X> int test(int x) {
    // CHECK:      [[RET:%.*]] = alloca i32
    // CHECK-NEXT: [[X:%.*]] = alloca i32
    // CHECK-NEXT: [[Y:%.*]] = alloca [[A:%.*]],
    // CHECK-NEXT: [[Z:%.*]] = alloca [[A]]
    // CHECK-NEXT: [[EXN:%.*]] = alloca ptr
    // CHECK-NEXT: [[SEL:%.*]] = alloca i32
    // CHECK-NEXT: [[V:%.*]] = alloca ptr,
    // CHECK-NEXT: [[TMP:%.*]] = alloca [[A]]
    // CHECK-NEXT: [[CLEANUPACTIVE:%.*]] = alloca i1
    // CHECK:      call void @_ZN5test01AC1Ev(ptr {{[^,]*}} [[Y]])
    // CHECK-NEXT: invoke void @_ZN5test01AC1Ev(ptr {{[^,]*}} [[Z]])
    // CHECK:      [[NEW:%.*]] = invoke noalias noundef nonnull ptr @_Znwm(i64 noundef 1)
    // CHECK:      store i1 true, ptr [[CLEANUPACTIVE]]
    // CHECK-NEXT: invoke void @_ZN5test01AC1Ev(ptr {{[^,]*}} [[TMP]])
    // CHECK:      invoke void @_ZN5test01VC1ERKNS_1AE(ptr {{[^,]*}} [[NEW]], ptr noundef nonnull align {{[0-9]+}} dereferenceable({{[0-9]+}}) [[TMP]])
    // CHECK:      store i1 false, ptr [[CLEANUPACTIVE]]

    // CHECK98-NEXT: invoke void @_ZN5test01AD1Ev(ptr {{[^,]*}} [[TMP]])
    // CHECK11-NEXT: call void @_ZN5test01AD1Ev(ptr {{[^,]*}} [[TMP]])
    A y;
    try {
      A z;
      V *v = new V();

      if (x) return 1;
    } catch (int ex) {
      return 1;
    }
    return 0;
  }

  int test() {
    return test<0>(5);
  }
}
