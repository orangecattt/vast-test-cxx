// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Test that `annotate_type` does not affect mangled names.

int *[[clang::annotate_type("foo")]] f(int *[[clang::annotate_type("foo")]],
                                       int [[clang::annotate_type("foo")]]) {
  return nullptr;
}
// CHECK: @_Z1fPii

template <class T> struct S {};

S<int *[[clang::annotate_type("foo")]]>
g(S<int *[[clang::annotate_type("foo")]]>) {
  return {};
}
// CHECK: @_Z1g1SIPiE
