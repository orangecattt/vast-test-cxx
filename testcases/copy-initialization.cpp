// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Foo {
  Foo();
  Foo(const Foo&);
};

struct Bar {
  Bar();
  operator const Foo&() const;
};

void f(Foo);

// CHECK-LABEL: define{{.*}} void @_Z1g3Foo(ptr noundef %foo)
void g(Foo foo) {
  // CHECK: call void @_ZN3BarC1Ev
  // CHECK: @_ZNK3BarcvRK3FooEv
  // CHECK: call void @_Z1f3Foo
  f(Bar());
  // CHECK: call void @_ZN3FooC1Ev
  // CHECK: call void @_Z1f3Foo
  f(Foo());
  // CHECK: call void @_ZN3FooC1ERKS_
  // CHECK: call void @_Z1f3Foo
  f(foo);
  // CHECK: ret
}

