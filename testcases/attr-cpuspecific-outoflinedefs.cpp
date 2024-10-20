// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fms-compatibility %s %target -o %t%output-suffix && %filecheck

struct OutOfLineDefs {
  int foo(int);
  int foo(int, int);
  __attribute__((cpu_specific(atom))) int foo(int, int, int) { return 1; }
};

int __attribute__((cpu_specific(atom))) OutOfLineDefs::foo(int) {
  return 1;
}
int __attribute__((cpu_specific(ivybridge))) OutOfLineDefs::foo(int) {
  return 2;
}
int __attribute__((cpu_dispatch(ivybridge, atom))) OutOfLineDefs::foo(int) {
}

int __attribute__((cpu_specific(atom))) OutOfLineDefs::foo(int, int) {
  return 1;
}
int __attribute__((cpu_specific(ivybridge))) OutOfLineDefs::foo(int, int) {
  return 2;
}
int __attribute__((cpu_dispatch(ivybridge, atom)))
OutOfLineDefs::foo(int, int) {
}

int __attribute__((cpu_specific(ivybridge))) OutOfLineDefs::foo(int, int, int) {
  return 2;
}
int __attribute__((cpu_specific(sandybridge)))
OutOfLineDefs::foo(int, int, int) {
  return 3;
}
int __attribute__((cpu_dispatch(sandybridge, ivybridge, atom)))
OutOfLineDefs::foo(int, int, int) {
}









