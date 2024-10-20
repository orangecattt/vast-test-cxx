// RUN: %driver -cc1 %isys -std=c++20 %S/Inputs/cxx20-module-impl-1a.cpp -emit-module-interface -o %t
// RUN: %driver -cc1 %isys -std=c++20 %s -fmodule-file=%t %target -o %t%output-suffix && %filecheck

module Foo;

void Exported() {
}

void Module() {
}

void Module2() {
}
