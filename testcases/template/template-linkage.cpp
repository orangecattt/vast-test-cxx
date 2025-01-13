// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


template<typename T> struct A {
  virtual void f(T) { }
  inline void g() { } 
};


template void A<int>::g();

template struct A<float>;

template <typename T> void f(T) { }
template void f<int>(int);

template <typename T> inline void g(T) { }
template void g<int>(int);

template<typename T>
struct X0 {
  virtual ~X0() { }
};

template<typename T>
struct X1 : X0<T> {
  virtual void blarg();
};

template<typename T> void X1<T>::blarg() { }

extern template struct X0<char>;
extern template struct X1<char>;

void test_X1() {
  X1<char> i1c;
}

namespace PR14825 {
struct Outer {
  template <typename T> struct Inner {
    static int member;
  };
  template <typename T> void Get() {
    int m = Inner<T>::member;
  }
};

void test() {
  struct local {};
  Outer o;
  typedef void (Outer::*mptr)();
  mptr method = &Outer::Get<local>;
}
}
