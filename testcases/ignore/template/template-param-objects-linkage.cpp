// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

struct S { char buf[32]; };
template<S s> constexpr const char* f() { return s.buf; }
const char* fbuf = f<S{"a"}>();

namespace {
  struct UN { char buf[64]; };
}
template <UN un> constexpr const char* g() { return un.buf; }
const char* gbuf = g<UN{"b"}>();

struct Foo { int *i; };
int m = 0;
namespace { int n; }

template <Foo foo>
const int* h() { return foo.i; }

const int* hm = h<Foo{&m}>();

const int* hn = h<Foo{&n}>();
