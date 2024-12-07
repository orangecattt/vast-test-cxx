// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck
export module Foo:impl;

export void Quux() {
}
