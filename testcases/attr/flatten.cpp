// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void f(void) {}

[[gnu::flatten]]
void g(void) {
  f();
}
