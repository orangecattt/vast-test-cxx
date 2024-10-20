// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -emit-obj -std=c++20 %s -o -

namespace PR50787 {
extern int x_;
consteval auto& X() { return x_; }
constexpr auto& x1 = X();
auto x2 = X();

}

namespace PR51484 {
struct X { int val; };
consteval X g() { return {0}; }
void f() { g(); }

}

namespace Issue54578 {
inline consteval unsigned char operator""_UC(const unsigned long long n) {
  return static_cast<unsigned char>(n);
}

inline constexpr char f1(const auto octet) {
  return 4_UC;
}

template <typename Ty>
inline constexpr char f2(const Ty octet) {
  return 4_UC;
}

int foo() {
  return f1('a') + f2('a');
}


}

namespace Issue55871 {
struct Item {
  consteval Item(char c) :_char{c}{}
  char _char;
};

int function(const Item& item1, const Item& item2) {
  return 0;
}

int foo() {
  return function(Item{'a'}, Item{'a'});
}
} // namespace Issue58871

namespace Issue55065 {
struct Base {
  consteval virtual int Get() const = 0;
};

struct Derived : Base {
  consteval int Get() const override {
    return 42;
  }
};

int foo() {
  constexpr Derived a;

  auto val = a.Get();
  return val;
}
} // namespace Issue55065

namespace GH60166 {

struct Base {
   void* one = nullptr;
   void* two = nullptr;
};

struct Derived : Base {
   void* three = nullptr;
   consteval Derived() = default;
};

void method() {
   (void)Derived();
}

} // namespace GH60166

namespace GH61142 {

template <typename T>
struct Test {
  constexpr static void bar() {
    foo();
  }
  consteval static void foo() {};
};

consteval void a() {
  Test<int>::bar();
}

void b() {
  Test<int>::bar();
}


} // namespace GH61142
