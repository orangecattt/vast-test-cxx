// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++11 -disable-llvm-optzns -fno-unroll-loops %s %target -o %t%output-suffix && %filecheck

void while_test(int *List, int Length) {
  int i = 0;

#pragma GCC unroll
  while (i < Length) {
    List[i] = i * 2;
    i++;
  }
}

void do_test(int *List, int Length) {
  int i = 0;

#pragma GCC nounroll
  do {
    List[i] = i * 2;
    i++;
  } while (i < Length);
}

void for_test(int *List, int Length) {
#pragma GCC unroll 8
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

void for_range_test() {
  double List[100];

#pragma GCC unroll(4)
  for (int i : List) {
    List[i] = i;
  }
}

#define UNROLLCOUNT 8

void for_define_test(int *List, int Length, int Value) {
#pragma GCC unroll(UNROLLCOUNT)
  for (int i = 0; i < Length; i++) {
    List[i] = i * Value;
  }
}

template <typename A>
void for_template_test(A *List, int Length, A Value) {
#pragma GCC unroll 8
  for (int i = 0; i < Length; i++) {
    List[i] = i * Value;
  }
}

template <typename A>
void for_template_define_test(A *List, int Length, A Value) {

#pragma GCC unroll(UNROLLCOUNT)
  for (int i = 0; i < Length; i++) {
    List[i] = i * Value;
  }
}

#undef UNROLLCOUNT

void template_test(double *List, int Length) {
  double Value = 10;

  for_template_test<double>(List, Length, Value);
  for_template_define_test<double>(List, Length, Value);
}

