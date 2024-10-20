// RUN: %driver -cc1 %isys -fblocks %s -fexceptions -std=c++1y %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fblocks %s -fexceptions -std=c++1y -fclang-abi-compat=6.0 %target -o %t%output-suffix && %filecheck

namespace non_inline_function {
auto foo() {
  auto L = [](int a) {
    return [](char b) {
     return b;
    };
  };
  L(3)('a');
  return L;
}

template<typename T> 
auto foo2() {
  return [](const T&) { return 42; };
}

auto use = foo2<int>();

}

namespace inline_member_function {
struct X {
auto foo() {
  auto L = [](int a) {
    return [](char b) {
     return b;
    };
  };
  return L;
}
};

auto run1 = X{}.foo()(3)('a');

template<typename S>
struct A {
  template<typename T> static auto default_lambda() {
    return [](const T&) { return 42; };
  }

  template<class U = decltype(default_lambda<S>())>
    U func(U u = default_lambda<S>()) { return u; }
  
  template<class T> auto foo() { return [](const T&) { return 42; }; }
};
int run2 = A<double>{}.func()(3.14);

int run3 = A<char>{}.func()('a');
} // end inline_member_function


namespace inline_function {
inline auto foo() {
  auto L = [](int a) {
    return [](char b) {
     return b;
    };
  };
  return L;
}
auto use = foo()(3)('a');
}

