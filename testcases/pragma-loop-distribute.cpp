// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void while_test(int *List, int Length, int *List2, int Length2) {
  int i = 0;

#pragma clang loop distribute(enable)
  while (i < Length) {
    List[i] = i * 2;
    i++;
  }

  i = 0;
  while (i < Length2) {
    List2[i] = i * 2;
    i++;
  }
}

