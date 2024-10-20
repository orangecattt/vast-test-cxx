// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct A {
  A &operator=(A&&);
};

struct B {
  A a;
  int i;
  bool b;
  char c;
  long l;
  float f;
};

void test1() {
  B b1, b2;
  b1 = static_cast<B&&>(b2);
}

// CHECK-LABEL: define {{.*}} @_ZN1BaSEOS_
// CHECK: call {{.*}} @_ZN1AaSEOS_
// CHECK-NOT: store
// CHECK: call {{.*}}memcpy{{.*}}, i64 24
// CHECK-NOT: store
// CHECK: ret
