// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


void bar();
struct Foo {
  static void foo() __attribute__((constructor)) {
    bar();
  }
};
