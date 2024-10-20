// RUN: %driver -cc1 %isys -std=c++11 %s -fexceptions -fcxx-exceptions %target -o %t%output-suffix && %filecheck

void h();

template<typename T> void f() noexcept(sizeof(T) == 4) { h(); }
template<typename T> void g() noexcept(sizeof(T) == 4);

template<typename T> struct S {
  static void f() noexcept(sizeof(T) == 4) { h(); }
  static void g() noexcept(sizeof(T) == 4);
};

template<> void f<short>() { h(); }
template<> void f<short[2]>() noexcept { h(); }

template<> void S<short>::f() { h(); }
template<> void S<short[2]>::f() noexcept { h(); }

template void f<char16_t>();
template void f<char16_t[2]>();

template void S<char16_t>::f();
template void S<char16_t[2]>::f();

void h() {
  f<int>();
  f<int[2]>();

  S<int>::f();
  S<int[2]>::f();

  void (*f1)() = &f<float>;
  void (*f2)() = &f<double>;

  void (*f3)() = &S<float>::f;
  void (*f4)() = &S<double>::f;

  (void)&f<char[4]>;
  (void)&f<char>;

  (void)&S<char[4]>::f;
  (void)&S<char>::f;
}

void i() {
  g<int>();
  g<int[2]>();

  S<int>::g();
  S<int[2]>::g();

  void (*g1)() = &g<float>;
  void (*g2)() = &g<double>;

  void (*g3)() = &S<float>::g;
  void (*g4)() = &S<double>::g;

  (void)&g<char[4]>;
  (void)&g<char>;

  (void)&S<char[4]>::g;
  (void)&S<char>::g;
}

template<typename T> struct Nested {
  template<bool b, typename U> void f() noexcept(sizeof(T) == sizeof(U));
};

void j() {
  Nested<int>().f<true, char>();
  Nested<long>().f<false, long>();
}




namespace PR19190 {
template <class T> struct DWFIterator { virtual void get() throw(int) = 0; };
void foo(DWFIterator<int> *foo) { foo->get(); }
}
