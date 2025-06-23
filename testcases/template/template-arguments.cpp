// RUN: %driver -cc1 %isys -std=c++20 %s -DCONSTEXPR= %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 %s -DCONSTEXPR=constexpr %target -o %t%output-suffix && %filecheck

template<typename T> CONSTEXPR T id(T v) { return v; }
template<auto V> auto value = id(V);

template int value<1>;

template unsigned long long value<-1ULL>;

template float value<1.0f>;
template double value<1.0>;

enum E{ E1, E2};

template E value<E2>;

int n;
template int *value<&n>;

struct A { int a[3]; } a;
template int *value<&a.a[0]>;
template int *value<&a.a[1]>;
template int *value<&a.a[2]>;
template int *value<&a.a[3]>;

union U {
  int x, y;
  union {
    int x, y;
  } internal;
} u;

template int *value<&u.x>;
template int *value<&u.y>;
template int *value<&u.internal.y>;

struct B { int x, y; };
template int B::*value<&B::x>;
template int B::*value<&B::y>;

struct C : A, B { int z; };
template int C::*value<(int C::*)&B::x>;
template int B::*value<(int B::*)&C::z>;

// template _Complex int value<1 + 2j>;

// template _Complex float value<1.0f + 2.0fj>;

using V3i __attribute__((ext_vector_type(3))) = int;
template V3i value<V3i{1, 2, 3}>;

using V3f [[gnu::vector_size(12)]] = float;
template V3f value<V3f{1, 2, 3}>;


template <int& i>
void setByRef() {
  i = 1;
}

void callSetByRefWithSubobject() {
  setByRef<a.a[1]>();
}
