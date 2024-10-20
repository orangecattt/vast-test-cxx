// RUN: %driver -cc1 %isys -fvisibility=hidden %s %target -o %t%output-suffix && %filecheck


template<typename T>
struct C {
  struct Inner {
    void f();
    struct Inner2 {
      void g();
      static int Static;
    };
  };
};

template<typename T> void C<T>::Inner::f() { }
template<typename T> void C<T>::Inner::Inner2::g() { }
template<typename T> int C<T>::Inner::Inner2::Static;

extern template struct C<int>;
template struct C<int>;
