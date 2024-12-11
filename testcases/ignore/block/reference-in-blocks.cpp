// RUN: %driver -cc1 %isys -fblocks %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(const char*, ...);

template<typename T> class range {
public:
T _i;
        range(T i) {_i = i;};
        T get() {return _i;};
};

class A {
    public:
	A() : field(10), d1(3.14) {}
	void F();
	void S() {
	  printf(" field = %d\n", field);
	  printf(" field = %f\n", d1);
	}
	int field;
	double d1;
};

void A::F()
    {
	__block A &tlc = *this;
        ^{ tlc.S(); }();
    }

int main() {

        void (^bl)(range<int> ) = ^(range<int> i){printf("Hello Blocks %d\n", i.get()); };

        void (^bl2)(range<int>& ) = ^(range<int>& i){printf("Hello Blocks %d\n", i.get()); };

	A *a = new A;
	a->F();
        return 0;
}
