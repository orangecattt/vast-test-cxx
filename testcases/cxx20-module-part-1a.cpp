// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck
export module Foo:inter;

// CHECK-DAG: @_ZW3Foo4Frobv(
export void Frob() {
}
