// RUN: %driver -cc1 %isys -std=c++11 -fblocks %s %target -o %t%output-suffix && %filecheck

struct S {
  int a[4];
  S(int *, int * __attribute__((noescape)));
  S &operator=(int * __attribute__((noescape)));
  void m0(int *, int * __attribute__((noescape)));
  virtual void vm1(int *, int * __attribute__((noescape)));
};


S::S(int *, int * __attribute__((noescape))) {}

S &S::operator=(int * __attribute__((noescape))) { return *this; }

void S::m0(int *, int * __attribute__((noescape))) {}

void S::vm1(int *, int * __attribute__((noescape))) {}

void test0(S *s, int *p0, int *p1) {
  S t(p0, p1);
  t = p1;
  s->m0(p0, p1);
  s->vm1(p0, p1);
}

namespace std {
  typedef decltype(sizeof(0)) size_t;
}

void *operator new(std::size_t, void * __attribute__((noescape)) p) {
  return p;
}

void *test1(void *p0) {
  return ::operator new(16, p0);
}

void test2(int *p0, int *p1) {
  auto t = [](int *, int * __attribute__((noescape))){};
  t(p0, p1);
}

typedef void (*NoEscapeFunc)(__attribute__((noescape)) int *);

void test3(NoEscapeFunc f, int *p) {
  f(p);
}

namespace TestByref {

struct S {
  S();
  ~S();
  S(const S &);
  int a;
};

typedef void (^BlockTy)(void);
S &getS();
void noescapefunc(__attribute__((noescape)) BlockTy);



void test() {
  __block S &x = getS();
  noescapefunc(^{ (void)x; });
}

}
