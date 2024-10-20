// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void while_test(int *List, int Length) {
  int i = 0;

#pragma clang loop vectorize(enable)
#pragma clang loop interleave_count(4)
#pragma clang loop vectorize_width(4)
#pragma clang loop unroll(full)
#pragma clang loop distribute(enable)
  while (i < Length) {
    List[i] = i * 2;
    i++;
  }
}

void do_test(int *List, int Length) {
  int i = 0;

#pragma clang loop vectorize_width(8) interleave_count(4) unroll(disable) distribute(disable)
  do {
    List[i] = i * 2;
    i++;
  } while (i < Length);
}

enum struct Tuner : short { Interleave = 4, Unroll = 8 };

void for_test(int *List, int Length) {
#pragma clang loop interleave(enable)
#pragma clang loop interleave_count(static_cast<int>(Tuner::Interleave))
#pragma clang loop unroll_count(static_cast<int>(Tuner::Unroll))
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

void for_range_test() {
  double List[100];

#pragma clang loop vectorize_width(2) interleave_count(2)
  for (int i : List) {
    List[i] = i;
  }
}

void disable_test(int *List, int Length) {
#pragma clang loop vectorize(disable) unroll(disable) distribute(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

#define VECWIDTH 2
#define INTCOUNT 2
#define UNROLLCOUNT 8

void for_define_test(int *List, int Length, int Value) {
#pragma clang loop vectorize_width(VECWIDTH) interleave_count(INTCOUNT)
#pragma clang loop unroll_count(UNROLLCOUNT)
  for (int i = 0; i < Length; i++) {
    List[i] = i * Value;
  }
}

void for_contant_expression_test(int *List, int Length) {
#pragma clang loop vectorize_width(1 + 4)
  for (int i = 0; i < Length; i++) {
    List[i] = i;
  }

#pragma clang loop vectorize_width(3 + VECWIDTH)
  for (int i = 0; i < Length; i++) {
    List[i] += i;
  }
}

template <typename A>
void for_template_test(A *List, int Length, A Value) {
#pragma clang loop vectorize_width(8) interleave_count(8) unroll_count(8)
  for (int i = 0; i < Length; i++) {
    List[i] = i * Value;
  }
}

template <typename A, typename T>
void for_template_define_test(A *List, int Length, A Value) {
  const T VWidth = VECWIDTH;
  const T ICount = INTCOUNT;
  const T UCount = UNROLLCOUNT;
#pragma clang loop vectorize_width(VWidth) interleave_count(ICount)
#pragma clang loop unroll_count(UCount)
  for (int i = 0; i < Length; i++) {
    List[i] = i * Value;
  }
}

template <typename A, int V, int I, int U>
void for_template_constant_expression_test(A *List, int Length) {
#pragma clang loop vectorize_width(V) interleave_count(I) unroll_count(U)
  for (int i = 0; i < Length; i++) {
    List[i] = i;
  }

#pragma clang loop vectorize_width(V * 2 + VECWIDTH) interleave_count(I * 2 + INTCOUNT) unroll_count(U * 2 + UNROLLCOUNT)
  for (int i = 0; i < Length; i++) {
    List[i] += i;
  }

  const int Scale = 4;
#pragma clang loop vectorize_width(Scale * V) interleave_count(Scale * I) unroll_count(Scale * U)
  for (int i = 0; i < Length; i++) {
    List[i] += i;
  }

#pragma clang loop vectorize_width((Scale * V) + 2)
  for (int i = 0; i < Length; i++) {
    List[i] += i;
  }
}

#undef VECWIDTH
#undef INTCOUNT
#undef UNROLLCOUNT

void template_test(double *List, int Length) {
  double Value = 10;

  for_template_test<double>(List, Length, Value);
  for_template_define_test<double, int>(List, Length, Value);
  for_template_constant_expression_test<double, 2, 4, 8>(List, Length);
}

void for_test_fixed_16(int *List, int Length) {
#pragma clang loop vectorize_width(16, fixed) interleave_count(4) unroll(disable) distribute(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

void for_test_scalable_16(int *List, int Length) {
#pragma clang loop vectorize_width(16, scalable) interleave_count(4) unroll(disable) distribute(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

void for_test_fixed(int *List, int Length) {
#pragma clang loop vectorize_width(fixed) interleave_count(4) unroll(disable) distribute(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

void for_test_scalable(int *List, int Length) {
#pragma clang loop vectorize_width(scalable) interleave_count(4) unroll(disable) distribute(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

void for_test_scalable_1(int *List, int Length) {
#pragma clang loop vectorize_width(1, scalable) interleave_count(4) unroll(disable) distribute(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = i * 2;
  }
}

















