// RUN: %driver -cc1 %isys -std=c++11 -fsized-deallocation %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 -fsized-deallocation %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck


typedef decltype(sizeof(0)) size_t;

typedef int A;
struct B { int n; };
struct C { ~C() {} };
struct D { D(); virtual ~D() {} };
struct E {
  void *operator new(size_t);
  void *operator new[](size_t);
  void operator delete(void *) noexcept;
  void operator delete[](void *) noexcept;
};
struct F {
  void *operator new(size_t);
  void *operator new[](size_t);
  void operator delete(void *, size_t) noexcept;
  void operator delete[](void *, size_t) noexcept;
};

template<typename T> T get();

template<typename T>
void del() {
  ::delete get<T*>();
  ::delete[] get<T*>();
  delete get<T*>();
  delete[] get<T*>();
}

template void del<A>();
template void del<B>();
template void del<C>();
template void del<D>();
template void del<E>();
template void del<F>();

D::D() {}










