// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void test0(int *List, int Length) {

  #pragma clang loop vectorize(enable)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}

void test1(int *List, int Length) {

  #pragma clang loop vectorize(enable) vectorize_predicate(enable)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}

void test2(int *List, int Length) {

  #pragma clang loop vectorize(enable) vectorize_predicate(disable)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}

void test3(int *List, int Length) {

  #pragma clang loop vectorize_predicate(enable)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}

void test4(int *List, int Length) {

  #pragma clang loop vectorize(disable)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}

void test5(int *List, int Length) {

  #pragma clang loop vectorize(disable) vectorize_predicate(enable)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}

void test6(int *List, int Length) {

#pragma clang loop vectorize_predicate(disable) vectorize_width(1)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}


void test7(int *List, int Length) {

#pragma clang loop vectorize_predicate(disable) vectorize_width(4)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}


void test8(int *List, int Length) {

#pragma clang loop vectorize_predicate(enable) vectorize_width(1)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}


void test9(int *List, int Length) {

#pragma clang loop vectorize_predicate(enable) vectorize_width(4)
  for (int i = 0; i < Length; i++)
    List[i] = i * 2;
}










