// RUN: %driver %s %target -S -o %t%output-suffix && %filecheck

// Test annotation attributes on constructors do not crash.

class Foo {
public:
  [[clang::annotate("test")]] Foo() {}
};

Foo foo;
