// RUN: %driver -cc1 %isys %s -fno-c++-static-destructors %target -o %t%output-suffix && %filecheck

struct NonTrivial {
  ~NonTrivial();
};

NonTrivial nt1;
thread_local NonTrivial nt2;

struct NonTrivial2 {
  ~NonTrivial2();
};

[[clang::always_destroy]] NonTrivial2 nt21;
[[clang::always_destroy]] thread_local NonTrivial2 nt22;

void f() {
  [[clang::always_destroy]] static NonTrivial2 nt21;
  [[clang::always_destroy]] thread_local NonTrivial2 nt22;
}

[[clang::no_destroy]] NonTrivial nt3;
[[clang::no_destroy]] thread_local NonTrivial nt4;
