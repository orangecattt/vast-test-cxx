// RUN: %driver -cc1 %isys -std=c++17 -fchar8_t %s %target -o %t%output-suffix && %filecheck

void f(char8_t c) {}

template<typename T> void g(decltype(T() + u8"foo" + u8'r')) {}
template void g<int>(const char8_t*);
