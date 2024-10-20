// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -Oz %target -o %t%output-suffix && %filecheck

void t1(int *a) {
  delete a;
}

struct S {
  int a;
};


void t3(S *s) {


  delete s;
}

struct T {
  ~T();
  int a;
};

void t4(T *t) {
  delete t;
}

template <typename T>
class A {
  public: operator T *() const;
};

void f() {
  A<char*> a;
  
  delete a;
}

namespace test0 {
  struct A {
    void *operator new(__SIZE_TYPE__ sz);
    void operator delete(void *p) { ::operator delete(p); }
    ~A() {}
  };

  void test(A *a) {
    delete a;
  }

}

namespace test1 {
  struct A {
    int x;
    ~A();
  };

  void test(A (*arr)[10][20]) {
    delete [] arr;

  }
}

namespace test2 {
  void f(bool *b) {
    delete b;
    delete [] b;
  }
}

namespace test3 {
  void f(int a[10][20]) {
    delete a;
  }
}

namespace test4 {
  struct X {
    virtual ~X();
    void operator delete (void *);
  };

  void global_delete_virtual(X *xp) {
    ::delete xp;
  }
}

namespace test5 {
  struct Incomplete;
  void array_delete_incomplete(Incomplete *p1, Incomplete *p2) {
    delete p1;
    delete [] p2;
  }
}

