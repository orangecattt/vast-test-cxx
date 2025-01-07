// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++98 -ffinite-loops %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -ffinite-loops %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 -ffinite-loops %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 -ffinite-loops %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -ffinite-loops %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++98 -fno-finite-loops %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fno-finite-loops %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 -fno-finite-loops %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 -fno-finite-loops %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -fno-finite-loops %s %target -o %t%output-suffix && %filecheck

int a = 0;
int b = 0;


void f0() {
  for (; ;) ;
}

void f1() {
  for (; 1;)
    ;
}

void f2() {
  for (; a == b;)
    ;
}

void F() {
  for (; 1;)
    ;
  for (; a == b;)
    ;
}

void F2() {
  for (; a == b;)
    ;
  for (; 1;)
    ;
}

void w1() {
  while (1)
    ;
}

void w2() {
  while (a == b)
    ;
}

void W() {
  while (a == b)
    ;
  while (1)
    ;
}

void W2() {
  while (1)
    ;
  while (a == b)
    ;
}

void d1() {
  do
    ;
  while (1);
}

void d2() {
  do
    ;
  while (a == b);
}

void D() {
  do
    ;
  while (1);
  do
    ;
  while (a == b);
}

void D2() {
  do
    ;
  while (a == b);
  do
    ;
  while (1);
}

