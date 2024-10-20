// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

struct S { char buf[32]; };
template<S s> constexpr const char *begin() { return s.buf; }
template<S s> constexpr const char *end() { return s.buf + __builtin_strlen(s.buf); }



const char *p = begin<S{"hello world"}>();
const char *q = end<S{"hello world"}>();
