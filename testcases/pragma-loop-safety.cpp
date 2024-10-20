// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void vectorize_test(int *List, int Length) {
#pragma clang loop vectorize(assume_safety) interleave(disable) unroll(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;

  }
}

void interleave_test(int *List, int Length) {
#pragma clang loop interleave(assume_safety) vectorize(disable) unroll(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;

  }
}

