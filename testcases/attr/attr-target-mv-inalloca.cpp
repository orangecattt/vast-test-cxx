// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct Foo {
  Foo();
  Foo(const Foo &o);
  ~Foo();
  int x;
};
int __attribute__((target("default"))) bar(Foo o) { return o.x; }
int __attribute__((target("sse4.2"))) bar(Foo o) { return o.x + 1; }
int __attribute__((target("arch=ivybridge"))) bar(Foo o) { return o.x + 2; }

void usage() {
  Foo f;
  bar(f);
}












