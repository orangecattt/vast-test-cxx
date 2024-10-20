// RUN: %driver -cc1 %isys -std=c++1y %s %target -o %t%output-suffix && %filecheck



template<typename T, typename U, typename Result>
struct plus {
  Result operator()(const T& t, const U& u) const;
};

template<typename T, typename U, typename Result>
Result plus<T, U, Result>::operator()(const T& t, const U& u) const {
  return t + u;
}

template struct plus<int, long, long>;

namespace EarlyInstantiation {
  template<typename T> struct S {
    constexpr int constexpr_function() { return 0; }
    auto deduced_return_type() { return 0; }
  };

  constexpr int a = S<char>().constexpr_function();
  int b = S<char>().deduced_return_type();

  extern template struct S<int>;
  constexpr int c = S<int>().constexpr_function();
  int d = S<int>().deduced_return_type();

  template struct S<char>;
  template struct S<int>;

  template<typename T> constexpr int constexpr_function() { return 0; }
  template<typename T> auto deduced_return_type() { return 0; }

  constexpr int e = constexpr_function<char>();
  int f = deduced_return_type<char>();

  extern template int constexpr_function<int>();
  extern template auto deduced_return_type<int>();
  constexpr int g = constexpr_function<int>();
  int h = deduced_return_type<int>();

  template int constexpr_function<char>();
  template int constexpr_function<int>();
}

namespace LateInstantiation {
  template<typename T> struct S { constexpr int f() { return 0; } };
  template<typename T> constexpr int f() { return 0; }

  int a, b = S<char>().f() + f<char>() + a;
  int c, d = S<int>().f() + f<int>() + a;

  extern template struct S<int>;
  extern template int f<int>();

}

namespace PR21718 {
template <typename T>
struct S {
  __attribute__((used)) constexpr int f() { return 0; }
};
int g() { return S<int>().f(); }
template struct S<int>;
}

namespace NestedClasses {
  template <typename T> struct Outer {
    struct Inner {
      void f() {}
    };
  };

  template struct Outer<int>;

  extern template struct Outer<char>;
  auto use = &Outer<char>::Inner::f;
}

template <typename T> struct S {
  void f();
  static void g();
  static int i;
  struct S2 {
    void h();
  };
};

template void S<int>::f();

template void S<int>::g();

template int S<int>::i;

template void S<int>::S2::h();

template <typename T> void S<T>::f() {}
template <typename T> void S<T>::g() {}
template <typename T> int S<T>::i;
template <typename T> void S<T>::S2::h() {}

namespace ExportedStaticLocal {
void sink(int&);
template <typename T>
inline void f() {
  static int i;
  sink(i);
}
extern template void f<int>();
void use() {
  f<int>();
}
}

namespace DefaultedMembers {
  struct B { B(); B(const B&); ~B(); };
  template<typename T> struct A : B {
    A() = default;
    ~A() = default;
  };
  extern template struct A<int>;

  A<int> ai;

  A<int> ai2(ai);

  template struct A<char>;
}
