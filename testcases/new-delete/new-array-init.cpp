// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s -fsanitize=signed-integer-overflow %target -o %t%output-suffix && %filecheck


void fn(int n) {
  new int[n] { 1, 2, 3 };
}

#if __cplusplus >= 202002L
void fn_paren(int n) {
  new int[n](1, 2, 3);
}
#endif

void const_exact() {
  new int[3] { 1, 2, 3 };
}

#if __cplusplus >= 202002L
void const_exact_paren() {
  new int[3](1, 2, 3);
}
#endif

void const_sufficient() {
  new int[4] { 1, 2, 3 };
}

#if __cplusplus >= 202002L
void const_sufficient_paren() {
  new int[4](1, 2, 3);
}
#endif

void check_array_value_init() {
  struct S;
  new (int S::*[3][4][5]) ();


}

void string_nonconst(int n) {
  new char[n] { "abc" };
}

#if __cplusplus >= 202002L
void string_nonconst_paren(int n) {
  new char[n]("abc");
}

void string_nonconst_paren_extra_paren(int n) {
  new char[n](("abc"));
}
#endif

void string_exact() {
  new char[4] { "abc" };
}

#if __cplusplus >= 202002L
void string_exact_paren() {
  new char[4]("abc");
}

void string_exact_paren_extension() {
  new char[4](__extension__ "abc");
}
#endif

void string_sufficient() {
  new char[15] { "abc" };
}

#if __cplusplus >= 202002L
void string_sufficient_paren() {
  new char[15]("abc");
}
#endif

void aggr_exact() {
  struct Aggr { int a, b; };
  new Aggr[2] { 1, 2, 3 };
}

void aggr_sufficient(int n) {
  struct Aggr { int a, b; };
  new Aggr[n] { 1, 2, 3 };
}

void constexpr_test() {
  new int[0+1]{0};
}

void unknown_bound() {
  struct Aggr { int x, y, z; };
  new Aggr[]{1, 2, 3, 4};
}

void unknown_bound_string() {
  new char[]{"hello"};
}
