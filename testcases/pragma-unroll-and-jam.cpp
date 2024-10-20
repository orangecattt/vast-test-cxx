// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void unroll_and_jam(int *List, int Length, int Value) {
#pragma unroll_and_jam
  for (int i = 0; i < Length; i++) {
    for (int j = 0; j < Length; j++) {
      List[i * Length + j] = Value;
    }
  }
}

void unroll_and_jam_count(int *List, int Length, int Value) {
#pragma unroll_and_jam(4)
  for (int i = 0; i < Length; i++) {
    for (int j = 0; j < Length; j++) {
      List[i * Length + j] = Value;
    }
  }
}

void nounroll_and_jam(int *List, int Length, int Value) {
#pragma nounroll_and_jam
  for (int i = 0; i < Length; i++) {
    for (int j = 0; j < Length; j++) {
      List[i * Length + j] = Value;
    }
  }
}

void clang_unroll_plus_nounroll_and_jam(int *List, int Length, int Value) {
#pragma nounroll_and_jam
#pragma unroll(4)
  for (int i = 0; i < Length; i++) {
    for (int j = 0; j < Length; j++) {
      List[i * Length + j] = Value;
    }
  }
}

