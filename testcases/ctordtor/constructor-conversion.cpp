// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

class X { // ...
public: 
  X(int) : iX(2), fX(2.3) , name("HELLO\n") {  }

  X(const char* arg, int ix=0) { iX = ix; fX = 6.0; name = arg+ix; }
  X(): iX(100), fX(1.2) {}
  int iX;
  float fX;
  const char *name;
  void pr(void) {
    printf("iX = %d  fX = %f name = %s\n", iX, fX, name);
  }
};

void g(X arg) {
  arg.pr();
}

void f(X arg) {
  X a = 1;        // a = X(1)

  a.pr();

  X b = "Jessie"; //  b=X("Jessie",0)

  b.pr();


  a = 2;          // a = X(2)

  a.pr();
}


int main() {
  X x;
  f(x);
  g(3);           // g(X(3))
}

