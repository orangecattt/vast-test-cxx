// RUN: %driver -cc1 %isys -I%S %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -I%S %s -fvisibility=hidden -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -I%S %s -fapple-kext -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -I%S %s -fno-assume-unique-vtables -std=c++11 %target -o %t%output-suffix && %filecheck

struct A { virtual ~A(); };
struct B final : A { };

// CHECK-LABEL: @_Z5exactP1A
B *exact(A *a) {
  // INEXACT: call {{.*}} @__dynamic_cast
  // EXACT-NOT: call {{.*}} @__dynamic_cast
  return dynamic_cast<B*>(a);
}
