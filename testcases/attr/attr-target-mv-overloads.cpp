// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

int __attribute__((target("sse4.2"))) foo_overload(int) { return 0; }
int __attribute__((target("arch=sandybridge"))) foo_overload(int);
int __attribute__((target("arch=ivybridge"))) foo_overload(int) {return 1;}
int __attribute__((target("default"))) foo_overload(int) { return 2; }
int __attribute__((target("sse4.2"))) foo_overload(void) { return 0; }
int __attribute__((target("arch=sandybridge"))) foo_overload(void);
int __attribute__((target("arch=ivybridge"))) foo_overload(void) {return 1;}
int __attribute__((target("default"))) foo_overload(void) { return 2; }

int bar2() {
  return foo_overload() + foo_overload(1);
}












