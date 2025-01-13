// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct F {
  void (*x)();
};
void G();
template<class T> class A {
public: A();
};
template<class T> A<T>::A() {
  static F f = { G };
}
A<int> a;
