// RUN: %driver -cc1 %isys -Werror %s %target -o %t%output-suffix && %filecheck


struct X0 {
  __attribute__((used, retain)) X0() {}
  __attribute__((used, retain)) ~X0() {}
};

struct X1 {
  struct Nested {
    void __attribute__((retain)) f0() {}
    void __attribute__((used, retain)) f1() {}
  };
};

namespace merge_decl {
static void func();
void bar() { void func() __attribute__((used, retain)); }
static void func() {}
} // namespace merge_decl

namespace instantiate_member {
template <typename T>
struct S {
  void __attribute__((used, retain)) f() {}
};

void test() {
  S<int> a;
}
} // namespace instantiate_member
