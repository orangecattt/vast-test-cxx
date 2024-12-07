// RUN: %driver -cc1 %isys %s -std=c++2a %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -Dconsteval="" -std=c++2a %target -o %t%output-suffix && %filecheck


consteval int ret7() {
  return 7;
}

int test_ret7() {
  int i = ret7();
  return i;
}

int global_i = ret7();

constexpr int i_const = 5;

consteval const int &retI() {
  return i_const;
}

const int &test_retRefI() {
  return retI();
}

int test_retI() {
  return retI();
}

consteval const int *retIPtr() {
  return &i_const;
}

int test_retIPtr() {
  return *retIPtr();
}

const int *test_retPIPtr() {
  return retIPtr();
}

consteval const int &&retIRRef() {
  return static_cast<const int &&>(i_const);
}

const int &&test_retIRRef() {
  return static_cast<const int &&>(retIRRef());
}

int test_retIRRefI() {
  return retIRRef();
}

struct Agg {
  int a;
  long b;
};

consteval Agg retAgg() {
  return {13, 17};
}

long test_retAgg() {
  long b = retAgg().b;
  return b;
}

Agg A = retAgg();

consteval const Agg &retRefAgg() {
  const Agg &tmp = A;
  return A;
}

long test_retRefAgg() {
  long b = retAgg().b;
  return b;
}

consteval Agg is_const() {
  return {5, 19 * __builtin_is_constant_evaluated()};
}

long test_is_const() {
  long b = is_const().b;
  return b;
}

struct AggCtor {
  consteval AggCtor(int a = 3, long b = 5) : a(a * a), b(a * b) {}
  int a;
  long b;
};

long test_AggCtor() {
  const int i = 2;
  AggCtor C(i);
  return C.a + C.b;
}

struct UserConv {
  consteval operator int() const noexcept { return 42; }
};

int test_UserConv() {
  return UserConv();
}

int test_UserConvOverload_helper(int a) { return a; }

int test_UserConvOverload() {
  return test_UserConvOverload_helper(UserConv());
}

consteval int test_UserConvOverload_helper_ceval(int a) { return a; }

int test_UserConvOverload_ceval() {
  return test_UserConvOverload_helper_ceval(UserConv());
}

consteval void void_test() {}
void void_call() { // EVAL-FN-LABEL: define {{.*}} @_Z9void_call
  void_test();
}
