// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

namespace std {
  struct strong_ordering {
    int n;
    constexpr operator int() const { return n; }
    static const strong_ordering less, equal, greater;
  };
  constexpr strong_ordering strong_ordering::less = {-1};
  constexpr strong_ordering strong_ordering::equal = {0};
  constexpr strong_ordering strong_ordering::greater = {1};
}

struct Primary {
  virtual void f();
  std::strong_ordering operator<=>(const Primary&) const = default;
};
struct X {
  virtual struct Y &operator=(Y&&);
  virtual struct Y &operator=(const Y&);
  std::strong_ordering operator<=>(const X&) const = default;
};
struct Y : Primary, X {
  virtual std::strong_ordering operator<=>(const Y&) const = default;
};
Y y;

struct A {
  void operator<=>(int);
};

void A::operator<=>(int) {}

void operator<=>(int, A) {}

int operator<=>(A, A);

int f(A a) {
  return a <=> a;
}

void builtin_cmp(int a) {
  a <=> a;
}
