// RUN:  rm -rf %t
// RUN:  split-file %s %t
// RUN: %driver -cc1 %isys -std=c++20 %t/M.cppm -emit-module-interface -o %t/M.pcm
// RUN: %driver -cc1 %isys -std=c++20 %t/Use.cpp -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

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


