// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -std=c++11 %s %target -o %t%output-suffix && %filecheck



struct A { A(int); virtual ~A(); };
struct B : A { using A::A; ~B(); };
B::~B() {}

B b(123);

struct C { template<typename T> C(T); };
struct D : C { using C::C; };
D d(123);






struct Q { Q(int); Q(const Q&); ~Q(); };
struct Z { Z(); Z(int); ~Z(); int n; };

namespace noninline_nonvirt {
  struct A { A(int, Q&&, void *__attribute__((pass_object_size(0)))); int n; };
  struct B : Z, A { Z z; using A::A; };
  B b(1, 2, &b);



  struct C : B { using B::B; };
  C c(1, 2, &c);

}

namespace noninline_virt {
  struct A { A(int, Q&&, void *__attribute__((pass_object_size(0)))); int n; };
  struct B : Z, virtual A { Z z; using A::A; };
  B b(1, 2, &b);


  struct C : B { using B::B; };
  C c(1, 2, &c);

}

namespace inalloca_nonvirt {
  struct A { A(Q, int, Q, Q&&); int n; };
  struct B : Z, A { Z z; using A::A; };
  B b(1, 2, 3, 4);




  struct C : B { using B::B; };
  C c(1, 2, 3, 4);


}

namespace inalloca_virt {
  struct A { A(Q, int, Q, Q&&); int n; };
  struct B : Z, virtual A { Z z; using A::A; };
  B b(1, 2, 3, 4);




  struct C : B { using B::B; };
  C c(1, 2, 3, 4);



}

namespace inline_nonvirt {
  struct A { A(Q, int, Q, Q&&, ...); int n; };
  struct B : Z, A { Z z; using A::A; };
  B b(1, 2, 3, 4, 5, 6);

  struct C : B { using B::B; };
  C c(1, 2, 3, 4, 5, 6);
}

namespace inline_virt {
  struct A { A(Q, int, Q, Q&&, ...); int n; };
  struct B : Z, virtual A { Z z; using A::A; };
  B b(1, 2, 3, 4, 5, 6);

  struct C : B { using B::B; };
  C c(1, 2, 3, 4, 5, 6);

}




