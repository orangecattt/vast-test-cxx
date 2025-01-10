// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void vectorize_outer_test(int *List, int Length) {
#pragma clang loop vectorize(assume_safety) interleave(disable) unroll(disable)
  for (int i = 0; i < Length; i += 2) {
#pragma clang loop unroll(full)
    for (int j = 0; j < 2; j += 1)
      List[i + j] = (i + j) * 2;
  }
}


