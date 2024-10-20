// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// PR5967

extern void* foo;
static void* const a = foo;
void* bar() { return a; }

// CHECK: @_ZL1a = internal global ptr null

// CHECK-LABEL: define internal {{.*}}void @__cxx_global_var_init
// CHECK: load ptr, ptr @foo
// CHECK: ret void

// CHECK-LABEL: define internal {{.*}}void @_GLOBAL__sub_I_deferred_global_init.cpp
// CHECK: call {{.*}}void @__cxx_global_var_init()
// CHECK: ret void
