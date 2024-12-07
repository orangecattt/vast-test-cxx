// RUN: %driver -cc1 %isys -std=c++20 %S/Inputs/cxx20-module-std-subst-2a.cpp -emit-module-interface -o %t
// RUN: %driver -cc1 %isys -std=c++20 %s -fmodule-file=%t %target -o %t%output-suffix && %filecheck
module;
# 5 __FILE__ 1
namespace std {
template <typename A> struct char_traits {};
} // namespace std
# 9 "" 2
export module Bar;
import RenameString;

void g(str<char, std::char_traits<char>> &s) {
}
