// RUN: %driver -cc1 %isys %s -fms-extensions -fexceptions -fcxx-exceptions -std=c++11 %target -o %t%output-suffix && %filecheck

int f(int);

void test_catch() {
  try {
    f(1);
  } catch (int) {
    f(2);
  } catch (double) {
    f(3);
  }
}









struct Cleanup {
  ~Cleanup() { f(-1); }
};

void test_cleanup() {
  Cleanup C;
  f(1);
}








