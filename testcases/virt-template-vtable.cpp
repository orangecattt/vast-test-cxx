// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template<class T> class A {
public:
  A() {}
  virtual void a() {}
};
class B : A<int> {
  B();
};
B::B() {}

template class A<long>;

extern template class A<short>;
template class A<short>;



template<class T> struct C {
  virtual void c() {}
};
struct D : C<int> {
  virtual void d();
};
void D::d() {}

