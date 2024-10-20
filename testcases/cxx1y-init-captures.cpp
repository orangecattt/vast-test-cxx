// RUN: %driver -cc1 %isys -std=c++1y %s %target -o %t%output-suffix && %filecheck

struct S {
  S();
  S(S &&);
  ~S();
};

void f() {
  (void) [s(S{})] {};
}




void g() {
  [a(1), b(2)] { return a + b; } ();
}




void init_capture_dtors() {
  struct HasDtor { ~HasDtor() {} };
  void some_function_call();
  void other_function_call();
  ([x = (HasDtor(), 0)]{}, some_function_call());
  other_function_call();
}

int h(int a) {
  return [&b(a), c(a)] {
    return [=, &c] {

      return b + c;
    } ();
  } ();
}

auto global_lambda = [a = 0] () mutable { return ++a; };
int get_incremented() { return global_lambda(); }
