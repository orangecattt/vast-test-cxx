// RUN:  rm -rf %t
// RUN:  split-file %s %t
//
// RUN: %driver -cc1 %isys -std=c++20 %t/M.cppm -emit-module-interface -o %t/M.pcm
// RUN: %driver -cc1 %isys -std=c++20 %t/Use.cpp -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck
//

//--- foo.h
int func_in_gmf() {
    return 43;
}
int func_in_gmf_not_called() {
    return 44;
}

//--- M.cppm
module;
#include "foo.h"
export module M;
int non_exported_func() {
    return 43 + func_in_gmf();
}
export int exported_func() {
    return non_exported_func();
}

int non_exported_func_not_called() {
    return 44;
}
export int func_not_called() {
    return non_exported_func_not_called();
}

export 
__attribute__((always_inline))
int always_inline_func() {
    return 45;
}

//--- Use.cpp
import M;
int use() {
    return exported_func() + always_inline_func();
}

// Checks that none of the function (except the always_inline_func) in the importees
// are generated in the importer's code.
// CHECK-O0: define{{.*}}_Z3usev(
// CHECK-O0: declare{{.*}}_ZW1M13exported_funcv(
// CHECK-O0: define{{.*}}available_externally{{.*}}_ZW1M18always_inline_funcv(
// CHECK-O0-NOT: func_in_gmf
// CHECK-O0-NOT: func_in_gmf_not_called
// CHECK-O0-NOT: non_exported_func
// CHECK-O0-NOT: non_exported_func_not_called
// CHECK-O0-NOT: func_not_called

// Checks that the generated code within optimizations keep the same behavior with
// O0 to keep consistent ABI.
// CHECK-O1: define{{.*}}_Z3usev(
// CHECK-O1: declare{{.*}}_ZW1M13exported_funcv(
// CHECK-O1: define{{.*}}available_externally{{.*}}_ZW1M18always_inline_funcv(
// CHECK-O1-NOT: func_in_gmf
// CHECK-O1-NOT: func_in_gmf_not_called
// CHECK-O1-NOT: non_exported_func
// CHECK-O1-NOT: non_exported_func_not_called
// CHECK-O1-NOT: func_not_called
