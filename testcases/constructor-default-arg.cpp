// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);


struct C {
  C() : iC(6) {}
  int iC;
};

int foo() {
  return 6;
};

class X { // ...
public: 
  X(int) {}
  X(const X&, int i = 1, int j = 2, int k = foo()) {
    printf("X(const X&, %d, %d, %d)\n", i, j, k);
  }
};

int main() {
  X a(1);
  X b(a, 2);
  X c = b;
  X d(a, 5, 6);
}

// CHECK: call void @_ZN1XC1ERKS_iii
// CHECK: call void @_ZN1XC1ERKS_iii
// CHECK: call void @_ZN1XC1ERKS_iii
