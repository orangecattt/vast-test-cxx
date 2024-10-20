// RUN: %driver -cc1 %isys -x c++ %s %target -o %t%output-suffix && %filecheck

// According to the Itanium ABI (3.1.1), types with non-trivial copy
// constructors passed by value should be passed indirectly, with the caller
// creating a temporary.

struct Empty;

struct Empty {
  Empty(const Empty &e);
  bool check();
};

bool foo(Empty e) {
// CHECK: @_Z3foo5Empty(ptr noundef %e)
// CHECK: call {{.*}} @_ZN5Empty5checkEv(ptr {{[^,]*}} %e)
  return e.check();
}

void caller(Empty &e) {
// CHECK: @_Z6callerR5Empty(ptr noundef nonnull align {{[0-9]+}} dereferenceable({{[0-9]+}}) %e)
// CHECK: call {{.*}} @_ZN5EmptyC1ERKS_(ptr {{[^,]*}} [[NEWTMP:%.*]], ptr
// CHECK: call {{.*}} @_Z3foo5Empty(ptr noundef [[NEWTMP]])
  foo(e);
}
