// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

using size_t = decltype(sizeof(0));

extern "C" char *something(long long x) {
}

void *operator new(size_t) __attribute__((alias("something")));

int *pr16715 = new int;
