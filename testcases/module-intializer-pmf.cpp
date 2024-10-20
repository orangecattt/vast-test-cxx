
// RUN: %driver -cc1 %isys -std=c++20 %s -emit-module-interface -o %T/HasPMF.pcm
// RUN: %driver -cc1 %isys -std=c++20 %T/HasPMF.pcm %target -o %t%output-suffix && %filecheck

module;

struct Glob {
  Glob(){};
};

Glob G;

export module HasPMF;

export struct InMod {
  InMod(){};
};

export InMod IM;

module :private;

struct InPMF {
  InPMF(){};
};

InPMF P;

// CHECK: define internal void @__cxx_global_var_init
// CHECK: call {{.*}} @_ZN4GlobC1Ev
// CHECK: define internal void @__cxx_global_var_init
// CHECK: call {{.*}} @_ZNW6HasPMF5InPMFC1Ev
// CHECK: define internal void @__cxx_global_var_init
// CHECK: call {{.*}} @_ZNW6HasPMF5InModC1Ev
// CHECK: define void @_ZGIW6HasPMF
// CHECK: store i8 1, ptr @_ZGIW6HasPMF__in_chrg
// CHECK: call void @__cxx_global_var_init
// CHECK: call void @__cxx_global_var_init
// CHECK: call void @__cxx_global_var_init
