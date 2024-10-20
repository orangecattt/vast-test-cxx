// RUN: %driver -cc1 %isys %s -std=c++11 -fblocks -fexceptions %target -o %t%output-suffix && %filecheck

struct A {
	int x;
	A(const A &);
	A();
	~A() noexcept(false);
};

struct B {
	int x;
	B(const B &);
	B();
	~B();
};

int testA() {
	__block A a0, a1;
  ^{ a0.x = 1234; a1.x = 5678; };
	return 0;
}




int testB() {
	__block B b0, b1;
  ^{ b0.x = 1234; b1.x = 5678; };
	return 0;
}



namespace test1 {
  struct A { int x; A(); ~A(); };

  void test() {
    return;
    __block A a;
  }
}
