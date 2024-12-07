// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

struct B;
struct A {
  A();
  A(const A&);

  void operator[](B b);

  int a_member_f(B);
};
struct B {
  B();
  ~B();
};

struct C {
  operator int *();
  A *operator->();
  void operator->*(A);
  friend void operator->*(C, B);

  friend void operator<<(C, B);
  friend void operator>>(C, B);
  void operator<<(A);
  void operator>>(A);

  void operator=(A);
  void operator+=(A);
  friend void operator+=(C, B);

  void operator,(A);
  friend void operator,(C, B);

  void operator&&(A);
  void operator||(A);
  friend void operator&&(C, B);
  friend void operator||(C, B);
};

A make_a();
A *make_a_ptr();
int A::*make_mem_ptr_a();
void (A::*make_mem_fn_ptr_a())();
B make_b();
C make_c();
void side_effect();

void callee(A);
void (*get_f())(A);


void postfix_before_args() {
  get_f()(A{});

  (side_effect(), callee)(A{});
}


void dot_lhs_before_rhs() {
  make_a().a_member_f(make_b());

  make_a_ptr()->a_member_f(make_b());

  make_c()->a_member_f(make_b());
}


void array_lhs_before_rhs() {
  int (&get_arr())[10];
  extern int get_index();

  get_arr()[get_index()] = 0;

  get_index()[get_arr()] = 0;

  make_a()[make_b()];

  make_c()[get_index()] = 0;

  get_index()[make_c()] = 0;
}


void *operator new(decltype(sizeof(0)), C);

void alloc_before_init() {
  struct Q { Q(A) {} };
  delete new Q(make_a());

  new (make_c()) Q(make_a());
}


int dotstar_lhs_before_rhs() {
  int a = make_a().*make_mem_ptr_a();

  int b = make_a_ptr()->*make_mem_ptr_a();

  make_c()->*make_a();

  make_c()->*make_b();

  (make_a().*make_mem_fn_ptr_a())();

  (make_a_ptr()->*make_mem_fn_ptr_a())();

  return a + b;
}


void assign_rhs_before_lhs() {
  extern int &lhs_ref(), rhs();

  lhs_ref() = rhs();

  lhs_ref() += rhs();

  lhs_ref() %= rhs();

  make_c() = make_a();

  make_c() += make_a();

  make_c() += make_b();
}

void shift_lhs_before_rhs() {
  extern int lhs(), rhs();

  (void)(lhs() << rhs());

  (void)(lhs() >> rhs());

  make_c() << make_a();

  make_c() >> make_a();

  make_c() << make_b();

  make_c() >> make_b();
}

void comma_lhs_before_rhs() {
  make_c() , make_a();

  make_c() , make_b();
}

void andor_lhs_before_rhs() {
  make_c() && make_a();

  make_c() || make_a();

  make_c() && make_b();

  make_c() || make_b();
}
