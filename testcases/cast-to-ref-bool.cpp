// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// CHECK-LABEL: main
int main(int argc, char **argv) {
  // CHECK: load i8, ptr %
  // CHECK-NEXT: trunc i8 %{{.+}} to i1
  bool b = (bool &)argv[argc][1];
  return b;
}
