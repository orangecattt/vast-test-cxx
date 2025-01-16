// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern int aa __attribute__((section(".sdata")));

extern int bb __attribute__((section(".sdata"))) /* = 1 */;

int foo() {
  return aa + bb;
}
