// RUN: %driver -cc1 %isys %s -std=c++11 -finline-functions %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -finline-hint-functions %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fno-inline %target -o %t%output-suffix && %filecheck

struct A {
  inline void int_run(int);

  template <class T>
  inline void template_run(T);
};

// CHECK: @_ZN1A7int_runEi({{.*}}) [[ATTR:#[0-9]+]]
void A::int_run(int) {}
// CHECK: @_ZN1A12template_runIiEEvT_({{.*}}) [[ATTR]]
template <typename T>
void A::template_run(T) {}

void bar() {
  A().int_run(1);
  A().template_run(1);
}

// SUITABLE: attributes [[ATTR]] = { {{.*}}inlinehint{{.*}} }
//   HINTED: attributes [[ATTR]] = { {{.*}}inlinehint{{.*}} }
// NOINLINE: attributes [[ATTR]] = { {{.*}}noinline{{.*}} }
