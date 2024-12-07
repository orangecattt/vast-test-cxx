// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++2a -fsanitize=shift-base,shift-exponent %s %target -o %t%output-suffix && %filecheck

int lsh_overflow(int a, int b) {



  return a << b;
}
