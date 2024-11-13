// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fno-delete-null-pointer-checks %target -o %t%output-suffix && %filecheck

struct Member { int x; Member(); Member(int); Member(const Member &); };
struct VBase { int x; VBase(); VBase(int); VBase(const VBase &); };

struct ValueClass {
  ValueClass(int x, int y) : x(x), y(y) {}
  int x;
  int y;
}; // subject to ABI trickery



/* Test basic functionality. */
struct A {
  A(struct Undeclared &);
  A(ValueClass);
  Member mem;
};

A::A(struct Undeclared &ref) : mem(0) {}



A::A(ValueClass v) : mem(v.y - v.x) {}



/* Test that things work for inheritance. */
struct B : A {
  B(struct Undeclared &);
  Member mem;
};

B::B(struct Undeclared &ref) : A(ref), mem(1) {}




/* Test that the delegation optimization is disabled for classes with
   virtual bases (for now).  This is necessary because a vbase
   initializer could access one of the parameter variables by
   reference.  That's a solvable problem, but let's not solve it right
   now. */
struct C : virtual A {
  C(int);
  Member mem;
};
C::C(int x) : A(ValueClass(x, x+1)), mem(x * x) {}




/* Test that the delegation optimization is disabled for varargs
   constructors. */
struct D : A {
  D(int, ...);
  Member mem;
};

D::D(int x, ...) : A(ValueClass(x, x+1)), mem(x*x) {}



namespace test0 {
  struct A {};
  struct B : virtual A { int x; };
  struct C : B {};
  
  void test(C &in) {
    C tmp = in;
  }
}

namespace test1 {
  struct A { A(); void *ptr; };
  struct B { B(); int x; A a[0]; };
  B::B() {}
}

namespace abstract {
  template<typename T> struct should_not_appear_in_output {
    ~should_not_appear_in_output() { int arr[-(int)sizeof(T)]; }
  };

  struct X { ~X(); };

  struct A : virtual should_not_appear_in_output<int>, X {
    virtual ~A() = 0;
  };



  A::~A() {}

  struct B : virtual should_not_appear_in_output<int>, X {
    virtual void f() = 0;
    ~B();
  };



  B::~B() {}
}
