// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// The template should compile to linkonce linkage, not weak linkage.

// CHECK-NOT: weak
template<class T>
void thefunc();

template<class T>
inline void thefunc() {}

void test() {
  thefunc<int>();
}
