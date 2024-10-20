// RUN: %driver -cc1 %isys %s -std=c++2a %target -o %t%output-suffix && %filecheck

using size_t = decltype(sizeof(int));

#define CONSTINIT __attribute__((require_constant_initialization))

extern "C" [[noreturn]] void BOOM();
extern "C" void OK();
extern "C" size_t RANDU();

namespace std {
inline constexpr bool is_constant_evaluated() noexcept {
  return __builtin_is_constant_evaluated();
}
} // namespace std

bool foo() {
  return __builtin_is_constant_evaluated();
}

constexpr int f() {
  const int n = __builtin_is_constant_evaluated() && std::is_constant_evaluated() ? 13 : 17; // n == 13
  int m = __builtin_is_constant_evaluated() ? 13 : 17;       // m might be 13 or 17 (see below)
  char arr[n] = {};                                          // char[13]
  return m + int(sizeof(arr));
}

CONSTINIT int p = f(); // f().m == 13; initialized to 26
int p2 = f(); // same result without CONSTINIT

int q = p + f(); // m == 17 for this call; initialized to 56

int y;

CONSTINIT int b = __builtin_is_constant_evaluated() ? 2 : y; // static initialization to 2

int c = y + (__builtin_is_constant_evaluated() ? 2 : y); // dynamic initialization to y+y

const int a = __builtin_is_constant_evaluated() ? y : 1; // dynamic initialization to 1
const int *a_sink = &a;

void test_arr_expr() {
  char x1[std::is_constant_evaluated() && __builtin_is_constant_evaluated() ? 101 : 1];

  char x2[std::is_constant_evaluated() && __builtin_is_constant_evaluated() ? 42 : RANDU()];

  char x3[std::is_constant_evaluated() || __builtin_is_constant_evaluated() ? RANDU() : 13];
}

void test_new_arr_expr() {
  new char[std::is_constant_evaluated() || __builtin_is_constant_evaluated() ? 1 : 17];
}

bool test_constant_initialized_local(int k) {
  const bool n = __builtin_is_constant_evaluated() && std::is_constant_evaluated();
  const bool *volatile p = &n;
  return *p;
}

void test_ir_constant_fold() {
  if (std::is_constant_evaluated()) {
    BOOM();
  } else {
    OK();
  }
  std::is_constant_evaluated() ? BOOM() : OK();
}

int i_constant;
int i_not_constant;
int &ir = __builtin_is_constant_evaluated() ? i_constant : i_not_constant;

void test_ref_initialization_local_scope() {
  const int i_constant = 42;
  const int i_non_constant = 101;
  const int &r = __builtin_is_constant_evaluated() ? i_constant : i_non_constant;
}

void test_ref_to_static_var() {
  static int i_constant = 42;
  static int i_non_constant = 101;
  int &r = __builtin_is_constant_evaluated() ? i_constant : i_non_constant;
}

int not_constexpr;

struct DestructorBCE {
  int n;
  constexpr DestructorBCE(int n) : n(n) {}
  constexpr ~DestructorBCE() {
    if (!__builtin_is_constant_evaluated())
      not_constexpr = 1;
  }
};

DestructorBCE global_dtor_bce_1(101);

DestructorBCE global_dtor_bce_2(not_constexpr);

constexpr DestructorBCE global_dtor_bce_3(103);

void test_dtor_bce_1() {

  DestructorBCE local(201);
}

void test_dtor_bce_2() {

  DestructorBCE local(not_constexpr);
}

void test_dtor_bce_3() {

  constexpr DestructorBCE local(203);
}

void test_dtor_bce_static_1() {

  static DestructorBCE local(301);
}

void test_dtor_bce_static_2() {
  static DestructorBCE local(not_constexpr);
}

void test_dtor_bce_static_3() {
  static constexpr DestructorBCE local(303);
}
