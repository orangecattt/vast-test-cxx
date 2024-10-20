// RUN:  rm -rf %t
// RUN:  mkdir %t
// RUN:  split-file %s %t

// RUN: %driver -cc1 %isys -std=c++20 -emit-module-interface %t/parta.cppm -o %t/mod-parta.pcm
// RUN: %driver -cc1 %isys -std=c++20 -emit-module-interface %t/partb.cppm -o %t/mod-partb.pcm
// RUN: %driver -cc1 %isys -std=c++20 -emit-module-interface %t/mod.cppm -fprebuilt-module-path=%t -o %t/mod.pcm
// RUN: %driver -cc1 %isys -std=c++20 %t/mod.pcm -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

//--- parta.cppm
export module mod:parta;

export int a = 43;

export int foo() {
  return 3 + a;
}

//--- partb.cppm
module mod:partb;

int b = 43;

int bar() {
  return 43 + b;
}

//--- mod.cppm
export module mod;
import :parta;
import :partb;
export int use() {
  return foo() + bar() + a + b;
}

// FIXME: The definition of the variables shouldn't be exported too.
// CHECK: @_ZW3mod1a = available_externally global
// CHECK: @_ZW3mod1b = available_externally global
// CHECK: declare{{.*}} i32 @_ZW3mod3foov
// CHECK: declare{{.*}} i32 @_ZW3mod3barv

// CHECK-OPT: @_ZW3mod1a = available_externally global
// CHECK-OPT: @_ZW3mod1b = available_externally global
// CHECK-OPT: declare{{.*}} i32 @_ZW3mod3foov
// CHECK-OPT: declare{{.*}} i32 @_ZW3mod3barv