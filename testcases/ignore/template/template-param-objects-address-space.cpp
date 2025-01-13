// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

struct S { char buf[32]; };
template<S s> constexpr const char *begin() { return s.buf; }
template<S s> constexpr const char *end() { return s.buf + __builtin_strlen(s.buf); }
template<S s> constexpr const void *retval() { return &s; }
extern const void *callee(const S*);
template<S s> constexpr const void* observable_addr() { return callee(&s); }


const char *p = begin<S{"hello world"}>();

const char *q = end<S{"hello world"}>();

const void *(*r)() = &retval<S{"hello world"}>;

const void *s = observable_addr<S{"hello world"}>();


