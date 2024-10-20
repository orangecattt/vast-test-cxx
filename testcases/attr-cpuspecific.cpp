// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fms-compatibility %s %target -o %t%output-suffix && %filecheck

struct S {
  __attribute__((cpu_specific(atom)))
  void Func(){}
  __attribute__((cpu_dispatch(ivybridge,atom)))
  void Func(){}
};

void foo() {
  S s;
  s.Func();
}


