// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

class Foo {
  virtual ~Foo();
};
Foo::~Foo() {}

