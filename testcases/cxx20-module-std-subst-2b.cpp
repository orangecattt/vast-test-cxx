// RUN: %driver -cc1 %isys -std=c++20 %S/Inputs/cxx20-module-std-subst-2a.cpp -emit-module-interface -o %t
// RUN: %driver -cc1 %isys -std=c++20 %s -fmodule-file=%t %target -o %t%output-suffix && %filecheck

export module Foo;
import RenameString;

namespace std {
template <typename T> struct char_traits {};
} // namespace std

void f(str<char, std::char_traits<char>> &s) {
}
