// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

struct Q {
  static constexpr int k = 5;
};
const int &r = Q::k;

int f();

inline const int external_inline = 5;
const int &use1 = external_inline;

static inline const int internal_inline = 5;
const int &use2 = internal_inline;

int a = f();
inline int b = f();
int c = f();

struct compat {
  static constexpr int a = 1;
  static constexpr int b = 2;
  static constexpr int c = 3;
  static inline constexpr int d = 4;
  static const int e = 5;
  static const int f = 6;
  static const int g = 7;
};
const int &compat_use_before_redecl = compat::b;
const int compat::a;
const int compat::b;
const int compat::c;
const int compat::d;
const int compat::e;
constexpr int compat::f;
constexpr inline int compat::g;
const int &compat_use_after_redecl1 = compat::c;
const int &compat_use_after_redecl2 = compat::d;
const int &compat_use_after_redecl3 = compat::g;

template<typename T> struct X {
  static int a;
  static inline int b;
  static int c;
  static const int d;
  static int e;
};
template<> inline int X<int>::a = 10;
int &use3 = X<int>::a;
template<> int X<int>::b = 20;
template<> inline int X<int>::c = 30;
template<typename T> constexpr int X<T>::d = 40;
template<typename T> inline int X<T>::e = 50;
const int *use_x_int_d = &X<int>::d;
const int *use_x_int_e = &X<int>::e;

template<typename T> struct Y;
template<> struct Y<int> {
  static constexpr int a = 123;
  static constexpr int b = 456;
  static constexpr int c = 789;
};
constexpr int Y<int>::a;
const int &yib = Y<int>::b;




template<typename T> inline int d = f();
int e = d<int>;


namespace PR35599 {
struct Marker1 {};
struct Marker2 {};

template <typename>
struct Foo {
  struct Bar { Bar(); };
  inline static Bar bar;
};

void run() {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-value"
  Foo<Marker1>::bar;
#pragma clang diagnostic pop
  static_cast<void>(Foo<Marker2>::bar);
}

}
