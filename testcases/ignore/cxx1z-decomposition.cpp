// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

namespace std {
  using size_t = decltype(sizeof(0));
  template<typename> struct tuple_size;
  template<size_t, typename> struct tuple_element;
}

struct Y { int n; };
struct X { X(); X(Y); X(const X&); ~X(); };

struct A { int a : 13; bool b; };

struct B {};
template<> struct std::tuple_size<B> { enum { value = 2 }; };
template<> struct std::tuple_element<0,B> { using type = X; };
template<> struct std::tuple_element<1,B> { using type = const int&; };
template<int N> auto get(B) {
  if constexpr (N == 0)
    return Y();
  else
    return 0.0;
}

using C = int[2];

typedef int D __attribute__((ext_vector_type(2)));

using E = _Complex int;

template<typename T> T &make();

auto [a1, a2] = make<A>();
auto [b1, b2] = make<B>();
auto &[c1, c2] = make<C>();
auto [d1, d2] = make<D>();
auto [e1, e2] = make<E>();






int test_globals() {
  return a2 + b2 + c2 + d2 + e2;
}

int test_locals() {
  auto [b1, b2] = make<B>();


  return b2;

}

void test_bitfield(A &a) {
  auto &[a1, a2] = a;
  a1 = 5;
}

void test_static_simple() {
  static auto [x1, x2] = make<A>();
}

int test_static_tuple() {
  static auto [x1, x2] = make<B>();




  struct Inner {
    int f() { return x2; }
  };
  return Inner().f();
}
