// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct pod {
  int a, b;
};

void f0();
void f1(struct pod);

struct notpod {
  int a, b;
  ~notpod() { f0(); }
};

void f2(struct notpod);

// CHECK-LABEL: caller
// CHECK: call void @_Z2f13pod(i64
// CHECK: call void @_Z2f26notpod(ptr
void caller()
{
  pod p1;
  notpod p2;
  f1(p1);
  f2(p2);
}
