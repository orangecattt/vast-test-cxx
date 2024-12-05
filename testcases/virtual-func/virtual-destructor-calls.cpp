// RUN: %driver -cc1 %isys %s -mconstructor-aliases %target -o %t%output-suffix && %filecheck

struct Member {
  ~Member();
};

struct A {
  virtual ~A();
};

struct B : A {
  Member m;
  virtual ~B();
};





B::~B() { }

struct C : B {
  ~C();
};

C::~C() { }




namespace PR12798 {
  struct A { virtual ~A(); };
  template<typename T> void f(T *p) { p->A::~A(); }

  template void f(A*);
}
