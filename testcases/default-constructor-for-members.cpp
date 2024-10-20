// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

struct S {
  S() { printf("S::S()\n"); }
  int iS;
};

struct M {
  S ARR_S; 
};

int main() {
  M m1;
}

