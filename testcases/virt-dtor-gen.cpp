// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// PR5483

// Make sure we generate all three forms of the destructor when it is virtual.
class Foo {
  virtual ~Foo();
};
Foo::~Foo() {}

// CHECK-LABEL: define {{.*}}void @_ZN3FooD0Ev(ptr {{[^,]*}} %this) unnamed_addr
