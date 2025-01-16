// RUN: %driver -cc1 %isys -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck

void foo();
void test() {
  try {
    foo();
  } catch (int *&i) {
    *i = 5;
  }
}



