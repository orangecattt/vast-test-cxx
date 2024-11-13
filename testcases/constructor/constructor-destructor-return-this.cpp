// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fno-rtti %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fctor-dtor-return-this %target -o %t%output-suffix && %filecheck


class A {
public:
  A();
  virtual ~A();

private:
  int x_;
};

class B : public A {
public:
  B(int *i);
  virtual ~B();

private:
  int *i_;
};

B::B(int *i) : i_(i) { }
B::~B() { }







class C : public A, public B {
public:
  C(int *i, char *c);
  virtual ~C();
private:
  char *c_;
};

C::C(int *i, char *c) : B(i), c_(c) { }
C::~C() { }







class D : public virtual A {
public:
  D();
  ~D();
};

D::D() { }
D::~D() { }







class E {
public:
  E();
  virtual ~E();
};

E* gete();

void test_destructor() {
  const E& e1 = E();
  E* e2 = gete();
  e2->~E();
}




