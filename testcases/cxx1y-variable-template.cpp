// RUN: %driver -cc1 %isys -std=c++1y %s %target -o %t%output-suffix && %filecheck

template<typename T> extern const int extern_redecl;
template<typename T> const int extern_redecl = 5;
template const int extern_redecl<int>;


template<typename T> struct Outer {
  template<typename U> struct Inner {
    template<typename V> static int arr[];
  };
};
Outer<char[100]> outer_int;
int init_arr();
template<typename T> template<typename U> template<typename V> int Outer<T>::Inner<U>::arr[sizeof(T) + sizeof(U) + sizeof(V)] = { init_arr() };
int *p = Outer<char[100]>::Inner<char[20]>::arr<char[3]>;

namespace PR35456 {
template<int> int n;
int *p = &n<0>;
}




namespace PR42111 {
  int f();
  namespace { template <int = 0> thread_local int n = f(); }
  int g() { return n<> + n<>; }
}
