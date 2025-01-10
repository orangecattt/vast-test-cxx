// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void vectorize_imperfectly_nested_test(int *List, int Length) {
#pragma clang loop vectorize(assume_safety) interleave(disable) unroll(disable)
  for (int i = 0; i < Length; ++i) {
    List[i * Length] = 42;
#pragma clang loop vectorize(assume_safety) interleave(disable) unroll(disable)
    for (int j = 1; j < Length - 1; ++j)
      List[i * Length + j] = (i + j) * 2;
    List[(i + 1) * Length - 1] = 21;
  }
}




