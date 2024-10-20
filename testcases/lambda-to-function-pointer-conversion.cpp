// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck




struct Trivial {
  int x;
};

void (*fnptr)(Trivial);

void test() {
  fnptr = [](Trivial a){ (void)a; };
}



Trivial (*fnptr2)(int);

void test2() {
  fnptr2 = [](int) -> Trivial { return {}; };
}
