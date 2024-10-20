// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

struct A { 
  A();
  A(const A&);
  A(A&);
  ~A();
};

struct B {
  B();
  B(B&);
};

struct C {
  C() {}
  C(C& other, A a = A());
  int i, j;
};

struct POD {
  int array[3][4];
};

struct D : A, B, virtual C { 
  D();
  int scalar;
  int scalar_array[2][3];
  B class_member;
  C class_member_array[2][3];
  POD pod_array[2][3];

  union {
    int x;
    float f[3];
  };
};

void f(D d) {
  D d2(d);
}



template<class T> struct X0 { void f0(T * ) { } };
template <class > struct X1 { X1( X1& , int = 0 ) { } };
struct X2 { X1<int> result; };
void test_X2()
{
  typedef X2 impl;
  typedef X0<impl> pimpl;
  impl* i;
  pimpl pdata;
  pdata.f0( new impl(*i));
}

namespace test3 {
  struct A { A(const A&); A&operator=(const A&); };
  struct B { A a; unsigned : 0; };
  void test(const B &x) {
    B y = x;
    y = x;
  }
}

namespace test4 {
  struct S {
    int arr[5][5];
    S(S &);
    S(const S &) = default;
  };
  void f1(S a) {
    S b(a);
  }
  void f2(const S a) {
    S b(a);
  }
}
