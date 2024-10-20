// Assert that the ABI switch uses the proper codegen. Fuchsia uses the
// "return this" ABI on constructors and destructors by default, but if we
// explicitly choose the generic itanium C++ ABI, we should not return "this" on
// ctors/dtors.
//
// RUN: %driver -cc1 %isys %s -fc++-abi=itanium %target -o %t%output-suffix && %filecheck

class A {
public:
  virtual ~A();
  int x_;
};

class B : public A {
public:
  B(int *i);
  virtual ~B();
  int *i_;
};

B::B(int *i) : i_(i) {}
B::~B() {}

// CHECK: define{{.*}} void @_ZN1BC2EPi(ptr {{[^,]*}} %this, ptr noundef %i)
// CHECK: define{{.*}} void @_ZN1BC1EPi(ptr {{[^,]*}} %this, ptr noundef %i)
// CHECK: define{{.*}} void @_ZN1BD2Ev(ptr {{[^,]*}} %this)
// CHECK: define{{.*}} void @_ZN1BD1Ev(ptr {{[^,]*}} %this)
