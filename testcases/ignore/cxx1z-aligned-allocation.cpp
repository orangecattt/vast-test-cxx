// RUN: %driver -cc1 %isys -std=c++11 -fexceptions -fsized-deallocation -faligned-allocation %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 -fexceptions -fsized-deallocation -faligned-allocation %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++1z -fexceptions -fsized-deallocation %s %target -o %t%output-suffix && %filecheck


// RUN: %driver -cc1 %isys -std=c++14 -DUNALIGNED -fexceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++1z -DUNALIGNED -fexceptions -fno-aligned-allocation %s %target -o %t%output-suffix && %filecheck


typedef decltype(sizeof(0)) size_t;
namespace std { enum class align_val_t : size_t {}; }

#define OVERALIGNED alignas(__STDCPP_DEFAULT_NEW_ALIGNMENT__ * 2)

struct OVERALIGNED A { A(); int n[128]; };

void *a0() { return new A; }

void *a1(long n) { return new A[n]; }

void a2(A *p) { delete p; }

void a3(A *p) { delete[] p; }


struct OVERALIGNED B {
  B();
  void *operator new(size_t);
  void operator delete(void*, size_t);
  void operator delete[](void*, size_t);

  void *operator new(size_t, std::align_val_t);
  void operator delete(void*, std::align_val_t);
  void operator delete[](void*, std::align_val_t);

  int n[128];
};

void *b0() { return new B; }

void *b1(long n) { return new B[n]; }

void b2(B *p) { delete p; }

void b3(B *p) { delete[] p; }

struct OVERALIGNED C {
  C();
  void *operator new[](size_t, std::align_val_t);
  void operator delete[](void*, size_t, std::align_val_t);

  void operator delete[](void*);
};

#ifndef UNALIGNED
void *b4(long n) { return new C[n]; }
#endif

void b5(C *p) { delete[] p; }



struct Q { int n; } q;
void *operator new(size_t, Q);
void *operator new(size_t, std::align_val_t, Q);
void operator delete(void*, Q);
void operator delete(void*, std::align_val_t, Q);

void *c0() { return new (q) A; }



struct OVERALIGNED D {
  D();
  void *operator new(size_t, Q);
  void *operator new(size_t, std::align_val_t, Q);
  void operator delete(void*, Q);
  void operator delete(void*, std::align_val_t, Q);
};

void *d0() { return new (q) D; }



#ifndef UNALIGNED
void *e0() { return new (std::align_val_t(4)) A; }

void *e1() { return new (std::align_val_t(4)) B; }
#endif


struct OVERALIGNED F {
  F();
  void *operator new(size_t, ...);
  void operator delete(void*, ...);
  int n[128];
};

void *f0() { return new F; }

void *f1() { return new (q) F; }

struct OVERALIGNED G {
  G();
  void *operator new(size_t, std::align_val_t, ...);
  void operator delete(void*, std::align_val_t, ...);
  int n[128];
};
#ifndef UNALIGNED
void *g0() { return new G; }

void *g1() { return new (q) G; }
#endif
