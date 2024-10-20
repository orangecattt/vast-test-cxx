// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN:  rm -rf %t
// RUN:  split-file %s %t
//
// RUN: %driver -cc1 %isys -std=c++20 -xc++-user-header -emit-header-unit %t/header.h -o %t/header.pcm
// RUN: %driver -cc1 %isys -std=c++20 -fmodule-file=%t/header.pcm %t/M.cppm %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -fmodule-file=%t/header.pcm %t/Use.cpp %target -o %t%output-suffix && %filecheck
//
//--- header.h
int foo();
static int i = foo();

//--- M.cppm
module;
import "header.h";
export module M;

// CHECK: @_ZL1i = {{.*}}global i32 0
// CHECK: void @__cxx_global_var_init()
// CHECK-NEXT: entry:
// CHECK-NEXT:  %call = call noundef{{.*}} i32 @_Z3foov()
// CHECK-NEXT:  store i32 %call, ptr @_ZL1i

//--- Use.cpp
import "header.h";

// CHECK: @_ZL1i = {{.*}}global i32 0
// CHECK: void @__cxx_global_var_init()
// CHECK-NEXT: entry:
// CHECK-NEXT:  %call = call noundef{{.*}} i32 @_Z3foov()
// CHECK-NEXT:  store i32 %call, ptr @_ZL1i