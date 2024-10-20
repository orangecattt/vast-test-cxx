// RUN: %driver -cc1 %isys %s -I%S %target -o %t%output-suffix && %filecheck

#include <typeinfo>

namespace Test1 {
  // A is explicitly marked hidden, so all RTTI data should also be marked hidden.
  // CHECK-TEST1: @_ZTSN5Test11AE = linkonce_odr hidden constant
  // CHECK-TEST1: @_ZTIN5Test11AE = linkonce_odr hidden constant
  // CHECK-TEST1: @_ZTSPN5Test11AE = linkonce_odr hidden constant
  // CHECK-TEST1: @_ZTIPN5Test11AE = linkonce_odr hidden constant
  struct __attribute__((visibility("hidden"))) A { };

  void f() {
    (void)typeid(A);
    (void)typeid(A *);
  }
}

namespace Test2 {
  // A is weak, so its linkage should be linkoce_odr, but not marked hidden.
  // CHECK-TEST2: @_ZTSN5Test21AE = linkonce_odr constant
  // CHECK-TEST2: @_ZTIN5Test21AE = linkonce_odr constant
  struct A { };
  void f() {
    (void)typeid(A);
  }
}
