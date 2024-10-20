// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

enum MyEnum : char;
void bar(MyEnum value) { }

// CHECK-LABEL: define{{.*}} void @_Z3foo6MyEnum
void foo(MyEnum value)
{
  // CHECK: call void @_Z3bar6MyEnum(i8 noundef signext
  bar(value);
}
