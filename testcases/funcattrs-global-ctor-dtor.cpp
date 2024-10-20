// RUN: %driver -cc1 %isys %s -stack-protector 2 %target -o %t%output-suffix && %filecheck

class A {
 public:
  virtual ~A() {}
};

A g;

// CHECK: define internal void @__cxx_global_var_init() [[ATTR0:#[0-9]+]]
// CHECK: define internal void @_GLOBAL__sub_I_funcattrs_global_ctor_dtor.cpp() [[ATTR0]]
// CHECK: attributes [[ATTR0]] = {{{.*}} sspstrong {{.*}}}
