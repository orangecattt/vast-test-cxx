// RUN: %driver -cc1 %isys -std=c++20 %S/cxx20-module-part-1a.cpp -emit-module-interface -o %t-inter
// RUN: %driver -cc1 %isys -std=c++20 %S/cxx20-module-part-1b.cpp -emit-module-interface -o %t-impl
// RUN: %driver -cc1 %isys -std=c++20 %s -fmodule-file=Foo:inter=%t-inter -fmodule-file=Foo:impl=%t-impl %target -o %t%output-suffix && %filecheck
export module Foo;
export import :inter;
import :impl;

void Wrap() {
  Frob();
  Quux();
}
