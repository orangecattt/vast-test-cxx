// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck
module;
# 4 __FILE__ 1
namespace Outer::Inner {
class X;
void Bar (X &) {}
} // namespace Outer::Inner
# 10 "" 2
export module FOO;	
namespace Outer {
class Y;
namespace Inner {
void Fn (X &, Y &){}  // #1
} // namespace Inner
} // namespace Outer
