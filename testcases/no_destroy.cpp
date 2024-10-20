// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions %s %target -o %t%output-suffix && %filecheck

struct NonTrivial {
  ~NonTrivial();
};

[[clang::no_destroy]] NonTrivial nt1;
[[clang::no_destroy]] thread_local NonTrivial nt2;

struct NonTrivial2 {
  ~NonTrivial2();
};

NonTrivial2 nt21;
thread_local NonTrivial2 nt22;

void f() {
  static NonTrivial2 nt21;
  thread_local NonTrivial2 nt22;
}

void g() {
  [[clang::no_destroy]] static NonTrivial2 nt21;
  [[clang::no_destroy]] thread_local NonTrivial2 nt22;
}

[[clang::always_destroy]] NonTrivial nt3;
[[clang::always_destroy]] thread_local NonTrivial nt4;


struct NonTrivial3 {
  NonTrivial3();
  ~NonTrivial3();
};

[[clang::no_destroy]] NonTrivial3 arr[10];


void h() {
  [[clang::no_destroy]] static NonTrivial3 slarr[10];
}


void i() {
  [[clang::no_destroy]] thread_local NonTrivial3 tlarr[10];
}

