// RUN: %driver %s %target -S -o %t%output-suffix && %filecheck


class Foo {
public:
  [[clang::annotate("test")]] Foo() {}
};

Foo foo;
