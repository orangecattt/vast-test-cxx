// RUN: %driver -cc1 %isys -std=c++11 -fexceptions -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck

struct Throws {
  Throws(int);
  Throws();
  ~Throws();
};

void cleanup(int n) {
  new Throws[n] { 1, 2, 3 };
}


void cleanup() {
  new Throws[3] { 1, 2, 3 };
}
