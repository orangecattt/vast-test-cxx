// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck
export module Foo:inter;

export void Frob() {
}
