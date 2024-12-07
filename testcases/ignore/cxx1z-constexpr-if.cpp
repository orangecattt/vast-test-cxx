// RUN: %driver -cc1 %isys -std=c++1z %s -fblocks %target -o %t%output-suffix && %filecheck

void should_be_used_1();
void should_be_used_2();
void should_be_used_3();
void should_not_be_used();

struct A {
  constexpr explicit operator bool() const {
    return true;
  }
};

void f() {
  if constexpr (false)
    should_not_be_used();
  else
    should_be_used_1();

  if constexpr (true || ({ label: false; }))
    should_be_used_2();
  else {
    goto foo;
foo: should_not_be_used();
  }
  if constexpr (A())
    should_be_used_3();
  else
    should_not_be_used();
}


namespace BlockThisCapture {
  void foo();
  struct S {
    template <bool b>
    void m() {
      ^{ if constexpr(b) (void)this; else foo();  }();
    }
  };

  void test() {
    S().m<false>();
  }
}

