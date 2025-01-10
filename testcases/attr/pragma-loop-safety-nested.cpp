// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void vectorize_nested_test(int *List, int Length) {
#pragma clang loop vectorize(assume_safety) interleave(disable) unroll(disable)
  for (int i = 0; i < Length; ++i) {
#pragma clang loop vectorize(assume_safety) interleave(disable) unroll(disable)
    for (int j = 0; j < Length; ++j)
      List[i * Length + j] = (i + j) * 2;
  }
}



