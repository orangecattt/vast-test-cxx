// RUN: %driver -cc1 %isys -fvisibility=hidden %s %target -o %t%output-suffix && %filecheck

template<typename T>
struct X {
  void f();
  void g() { }
};

template<typename T> void X<T>::f() { }

extern template struct X<int>;
template struct X<int>;
extern template struct X<char>;

void test_X(X<int> xi, X<char> xc) {
  xi.f();
  xi.g();
  xc.f();
  xc.g();
}

