// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck
module;
# 4 __FILE__ 1
namespace Outer::Inner {
class X;
// CHECK-DAG: void @_ZN5Outer5Inner3BarERNS0_1XE(
void Bar (X &) {}
} // namespace Outer::Inner
# 10 "" 2
export module FOO;	
namespace Outer {
class Y;
namespace Inner {
// CHECK-DAG: void @_ZN5Outer5InnerW3FOO2FnERNS0_1XERNS_S1_1YE(
void Fn (X &, Y &){}  // #1
} // namespace Inner
} // namespace Outer
