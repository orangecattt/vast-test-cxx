// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

struct A {
int Ai;
bool foo(int* arg) const;
}; 

bool A::foo(int* arg) const {
    printf("A::foo(%d)\n", *arg);
    return true;
}

struct B : public A {
  void bf() { printf("B::bf called\n"); }
}; 

struct C : public B { }; 

typedef void (A::*pmfa)();
typedef void (B::*pmfb)();
typedef void (C::*pmfc)();

struct X {
	operator pmfa();
	operator pmfb() {
	  return &B::bf;
        }
};


void g(pmfc pm) {
  C c;
  (c.*pm)();
}

void test2(X x) 
{
    g(x);
}

struct B1 {
  bool (A::*pmf)(int*) const;

  B1(int i) : pmf(&A::foo), im(i) {
    ((A*)this->*pmf)(&im);
  }

  int im;
};

int main()
{
	X x;
	test2(x);
        B1 b = B1(1);
  	B1 c = B1(2);
}


