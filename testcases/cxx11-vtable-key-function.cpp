// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// PR13424

namespace Test1 {
struct X {
  virtual ~X(); // Key function.
  virtual void f(); // Not a key function.
};

X::~X() = default;

// Verify that the vtable is emitted.
// CHECK-DAG: @_ZTVN5Test11XE ={{.*}} unnamed_addr constant
}

namespace Test2 {
struct X {
  virtual ~X() = default; // Not a key function.
  virtual void f(); // Key function.
};

void X::f() {}

// Verify that the vtable is emitted.
// CHECK-DAG: @_ZTVN5Test21XE ={{.*}} unnamed_addr constant
}

namespace Test3 {
struct X {
  virtual ~X() = delete; // Not a key function.
  virtual void f(); // Key function.
};

void X::f() {}

// Verify that the vtable is emitted.
// CHECK-DAG: @_ZTVN5Test31XE ={{.*}} unnamed_addr constant
}
