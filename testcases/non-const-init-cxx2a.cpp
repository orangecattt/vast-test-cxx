// RUN: %driver -cc1 %isys %s -std=c++2a %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -emit-pch %s -std=c++2a -o %t.pch
// RUN: %driver -cc1 %isys -include-pch %t.pch -x c++ /dev/null -std=c++2a %target -o %t%output-suffix && %filecheck

struct B {
  constexpr B() {}
  constexpr ~B() { n *= 5; }
  int n = 123;
};

// We emit a dynamic destructor here because b.n might have been modified
// before b is destroyed.
//
// CHECK: @b ={{.*}} global {{.*}} i32 123
B b = B();

// CHECK: define {{.*}}cxx_global_var_init
// CHECK: call {{.*}} @__cxa_atexit({{.*}} @_ZN1BD1Ev, {{.*}} @b
