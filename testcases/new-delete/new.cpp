// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck

typedef __typeof__(sizeof(0)) size_t;

template<typename T> void *operator new(size_t, int (*)(T));

void *operator new[](size_t);

void t1() {
  delete new int;
  delete [] new int [3];
}


namespace std {
  struct nothrow_t {};
}
std::nothrow_t nothrow;

void *operator new(size_t, void*) throw();
void operator delete(void*, void*) throw();
void *operator new[](size_t, void*) throw();
void operator delete[](void*, void*) throw();

void *operator new(size_t, const std::nothrow_t &) throw();
void *operator new[](size_t, const std::nothrow_t &) throw();
void operator delete(void *, const std::nothrow_t &) throw();
void operator delete[](void *, const std::nothrow_t &) throw();

void *operator new(size_t, void*, bool) throw();
void *operator new[](size_t, void*, bool) throw();

void t2(int* a) {
  int* b = new (a) int;
}

struct S {
  int a;
};

void t3() {
  int *a = new int(10);
  _Complex int* b = new _Complex int(10i);

  S s;
  s.a = 10;
  S *sp = new S(s);
}

struct T {
  T();
  int a;
};

void t4() {
  T *t = new T;
}

struct T2 {
  int a;
  T2(int, int);
};

void t5() {
  T2 *t2 = new T2(10, 10);
}

int *t6() {
  return new (0) int(10);
}

void t7() {
  new int();
}

struct U {
  ~U();
};

void t8(int n) {
  new int[10];
  new int[n];

  new T[10];
  new T[n];

  new U[10];
  new U[n];
}

void t9() {
  bool b;

  new bool(true);
  new (&b) bool(true);
}

struct A {
  void* operator new(__typeof(sizeof(int)), int, float, ...);
  A();
};

A* t10() {
  return new(1, 2, 3.45, 100) A;
}

struct B { int a; };
struct Bmemptr { int Bmemptr::* memptr; int a; };

void t11(int n) {
  B* b = new B();

  B *b2 = new B[n]();

  Bmemptr *b_memptr = new Bmemptr[n]();

}

struct Empty { };

void t12() {
  (void)new Empty[10];

  (void)new Empty[10]();

}

void t13(int n) {
  (void)new int();

  (void)new int[n]();

}

struct Alloc{
  int x;
  void* operator new[](size_t size);
  __attribute__((returns_nonnull)) void *operator new[](size_t size, const std::nothrow_t &) throw();
  void operator delete[](void* p);
  ~Alloc();
};

void f() {
  delete[] new Alloc[10][20];
  delete[] new (nothrow) Alloc[10][20];
  delete new bool;
}

namespace test15 {
  struct A { A(); ~A(); };

  void test0a(void *p) {
    new (p) A();
  }

  void test0b(void *p) {
    new (p, true) A();
  }

  void test1a(void *p) {
    new (p) A[5];
  }

  void test1b(void *p) {
    new (p, true) A[5];
  }

  void test2(void *p, int n) {
    new (p) A[n];
  }
}

namespace PR10197 {
  template<typename T>
  void f() {
    new T;
  }

  template void f<int>();
}

namespace PR11523 {
  class MyClass;
  typedef int MyClass::* NewTy;
  NewTy* f() { return new NewTy[2](); }
}

namespace PR11757 {
  struct X { X(); X(const X&); };
  X* a(X* x) { return new X(X()); }
}

namespace PR13380 {
  struct A { A() {} };
  struct B : public A { int x; };
  void* f() { return new B[2](); }
}

struct MyPlacementType {} mpt;
void *operator new(size_t, MyPlacementType);

namespace N3664 {
  struct S { S() throw(int); };

  void f() {
    int *p = new int;
    delete p;

    int *q = new int[3];
    delete[] p;

    (void) new (nothrow) S[3];

    (void) new (mpt) int;
  }


  void g() {
    int *p = (int*)operator new(4);
    operator delete(p);

    int *q = (int*)operator new[](12);
    operator delete [](p);

    (void) operator new[](3, nothrow);
  }
}

namespace builtins {
  void f() {
    __builtin_operator_delete(__builtin_operator_new(4));
  }
}



