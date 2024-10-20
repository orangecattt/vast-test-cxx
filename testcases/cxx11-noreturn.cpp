// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

int g();

// CHECK: _Z1fv(){{.*}} [[NR:#[0-9]+]]
[[noreturn]] int f() {
  while (g()) {}
}

// CHECK: attributes [[NR]] = { mustprogress noinline noreturn nounwind{{.*}} }
