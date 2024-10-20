// RUN: %driver -cc1 %isys -std=c++20 %S/Inputs/cxx20-module-impl-1a.cpp -emit-module-interface -o %t
// RUN: %driver -cc1 %isys -std=c++20 %s -fmodule-file=%t %target -o %t%output-suffix && %filecheck

module Foo;

// CHECK-DAG: @_ZW3Foo8Exportedv(
void Exported() {
}

// CHECK-DAG: @_ZW3Foo6Modulev(
void Module() {
}

// CHECK-DAG: @_ZW3Foo7Module2v(
void Module2() {
}
