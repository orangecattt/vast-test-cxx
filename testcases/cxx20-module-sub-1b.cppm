// RUN: %driver -cc1 %isys -std=c++20 %S/cxx20-module-sub-1a.cppm -emit-module-interface -o %t
// RUN: %driver -cc1 %isys -std=c++20 %s -fmodule-file=%t %target -o %t%output-suffix && %filecheck

export module FOO.BAZ;
import FOO.BAR;

namespace Bob {

void Foo (A *, B*) {
}
}

void Bar (A *, Bob::B*) {
}
