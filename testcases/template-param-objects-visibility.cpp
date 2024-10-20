// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

struct S { char buf[32]; };
template<S s> constexpr const char* f() { return s.buf; }
const char* fbuf = f<S{"a"}>();

struct __attribute__ ((visibility ("hidden"))) HN { char buf[64]; };
template <HN hn> constexpr const char* g() { return hn.buf; }
const char* gbuf = g<HN{"b"}>();
