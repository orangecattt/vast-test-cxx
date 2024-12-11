// RUN: %driver -cc1 %isys -fblocks %s -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fblocks %s -fexceptions -std=c++14 %target -o %t%output-suffix && %filecheck

namespace non_inline_function {
void foo() {
  auto L = [](int a) {
    return [](char b) {
     return b;
    };
  };
  L(3)('a');
}
}

namespace non_template {
  struct L {
    int t = ([](int a) { return [](int b) { return b; };})(2)(3);    
  };
  L l; 
}

inline auto lambda_in_inline_variable = [] {};
template<typename T> struct Wrap {};
void test_lambda_in_inline_variable(Wrap<decltype(lambda_in_inline_variable)>) {}

namespace lambdas_in_NSDMIs_template_class {
template<class T>
struct L {
    T t2 = ([](int a) { return [](int b) { return b; };})(T{})(T{});    
};
L<int> l;
}





namespace inline_function {
inline int foo() {
  auto L = [](int a) {
    return [](char b) {
     return b;
    };
  };
  L(3)('a');
}
int use = foo();
}

#if __cplusplus >= 201402L
namespace lambda_capture_in_generic_lambda {
template <typename T> auto foo() {
  return [](auto func) {
    [func] { func(); }();
  };
}
static void f() {
  foo<int>()([] { });
}
void f1() { f(); }
}
#endif
