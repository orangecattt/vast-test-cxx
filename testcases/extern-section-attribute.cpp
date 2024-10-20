// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern int aa __attribute__((section(".sdata")));
// CHECK-DAG: @aa = external global i32, section ".sdata", align 4

extern int bb __attribute__((section(".sdata"))) = 1;
// CHECK-DAG: @bb ={{.*}} global i32 1, section ".sdata", align 4

int foo() {
  return aa + bb;
}
