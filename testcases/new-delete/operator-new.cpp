// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-assume-sane-operator-new %s %target -o %t%output-suffix && %filecheck

class teste {
  int A;
public:
  teste() : A(2) {}
};

void f1() {
  new teste();
}

void *f2(long N) {
  return new int[N];

}

