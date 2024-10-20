// RUN: %driver -cc1 %isys %s -std=c++2a %target -o %t%output-suffix && %filecheck

// CHECK-DAG: @p = {{.*}} null
// CHECK-DAG: @_ZGR1p_ = {{.*}} null
int *const &p = new int;

struct d {
  constexpr d(int &&f) : e(f) {}
  int &e;
};

// CHECK-DAG: @g = {{.*}} null
// CHECK-DAG: @_ZGR1g_ = {{.*}} zeroinitializer
d &&g{{0}};

// CHECK: define {{.*}} @__cxx_global_var_init
// CHECK: define {{.*}} @__cxx_global_var_init
// CHECK-NOT: define {{.*}} @__cxx_global_var_init
