// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

struct M {
  M() { printf("M()\n"); }
  M(int i) { iM = i; printf("M(%d)\n", i); }
  int iM;
  void MPR() {printf("iM = %d\n", iM); };
};

struct P {
  P() { printf("P()\n"); }
  P(int i) { iP = i; printf("P(%d)\n", i); }
  int iP;
  void PPR() {printf("iP = %d\n", iP); };
};

struct Q {
  Q() { printf("Q()\n"); }
  Q(int i) { iQ = i; printf("Q(%d)\n", i); }
  int iQ;
  void QPR() {printf("iQ = %d\n", iQ); };
};

struct N : M , P, Q {
  N() : f1(1.314), P(2000), ld(00.1234+f1), M(1000), Q(3000),
        d1(3.4567), i1(1234), m1(100) { printf("N()\n"); }
  M m1;
  M m2;
  float f1;
  int i1;
  float d1;
  void PR() {
    printf("f1 = %f d1 = %f i1 = %d ld = %f \n", f1,d1,i1, ld); 
    MPR();
    PPR();
    QPR();
    printf("iQ = %d\n", iQ);
    printf("iP = %d\n", iP);
    printf("iM = %d\n", iM);
    printf("iQ = %d\n", this->iQ);
    printf("iP = %d\n", this->iP);
    printf("iM = %d\n", this->iM);
  }
  float ld;
  float ff;
  M arr_m[3];
  P arr_p[1][3];
  Q arr_q[2][3][4];
};

int main() {
  M m1;

  N n1;
  n1.PR();
}

template <class T> struct A {
  A() {}
  A(int) {}
  A(const A&) {}
  ~A() {}
  operator int() {return 0;}
};

void f() {
  A<short> a4 = 97;

  int i = 17;

}

namespace InitVTable {
  struct A { A(int); };
  struct B : A {
    virtual int foo();
    B();
    B(int);
  };

  B::B() : A(foo()) {}

  B::B(int x) : A(x + 5) {}
}

namespace rdar9694300 {
  struct X {
    int x;
  };

  void f() {
    X x;
    int i = 17;
  }
}

namespace PR13273 {
  struct U {
    int t;
    U() = default;
  };

  struct S : U {
    S() = default;
  };

  int f() {
    return (new S{})->t;
  }
}

template<typename T>
struct X {
  X(const X &);

  T *start;
  T *end;
};

template<typename T> struct X;

template<typename T>
X<T>::X(const X &other) : start(0), end(0) { }

X<int> get_X(X<int> x) { return x; }

namespace PR10720 {
  struct X { 
    X(const X&); 
    X(X&&); 
    X& operator=(const X&);
    X& operator=(X&&);
    ~X(); 
  };

  struct pair2 {
    X second[4];

    pair2 &operator=(const pair2&) = default;

    pair2 &operator=(pair2&&) = default;



    pair2(pair2&&) = default;

    pair2(const pair2&) = default;
  };

  struct pair : X { // Make the copy constructor non-trivial, so we actually generate it.
    int second[4];
    pair(const pair&) = default;
  };

  void foo(const pair &x, const pair2 &x2) {
    pair y(x);
    pair2 y2(x2);
    pair2 y2m(static_cast<pair2&&>(y2));

    y2 = x2;
    y2m = static_cast<pair2&&>(y2);
  }

}
