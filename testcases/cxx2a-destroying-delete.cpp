// RUN: %driver -cc1 %isys -std=c++2a -fexceptions %s %target -o %t%output-suffix && %filecheck


namespace std {
  using size_t = decltype(sizeof(0));
  enum class align_val_t : size_t;
  struct destroying_delete_t {};
}

struct A {
  void *data;
  ~A();
  void operator delete(A*, std::destroying_delete_t);
};
void delete_A(A *a) { delete a; }

struct B {
  virtual ~B();
  void operator delete(B*, std::destroying_delete_t);
};
void delete_B(B *b) { delete b; }

struct Padding {
  virtual void f();
};

struct C : Padding, A {};
void delete_C(C *c) { delete c; }

struct VDel { virtual ~VDel(); };
struct D : Padding, VDel, B {};
void delete_D(D *d) { delete d; }

struct J {
  J(); // might throw
  void operator delete(J *, std::destroying_delete_t);
};

J *j() {
  return new J;
}

struct K {
  K(); // might throw
  void operator delete(void *);
  void operator delete(K *, std::destroying_delete_t);
};

K *k() {
  return new K;
}

struct E { void *data; };
struct F { void operator delete(F *, std::destroying_delete_t, std::size_t, std::align_val_t); void *data; };
struct alignas(16) G : E, F { void *data; };

void delete_G(G *g) { delete g; }

void call_in_dtor();

struct H : G { virtual ~H(); } h;
H::~H() { call_in_dtor(); }


struct I : H { virtual ~I(); alignas(32) char buffer[32]; } i;
I::~I() { call_in_dtor(); }

