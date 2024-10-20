// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

struct A {
  A(int);
  A(A&&);
  A(const A&);
  ~A();

  operator bool();

  int arr[10];
};

A f();
void h();

void g() {
  A a = A( A{ f() } );

  h();

}

void f(A);

void h() {

  f(f());

  h();

}

struct B {
  B(int);
  int n;
};

B fB();
void fB(B);

void i() {

  fB(fB());

}

void j() {
  A &&a = A(1) ?: A(2);

  i();

}
