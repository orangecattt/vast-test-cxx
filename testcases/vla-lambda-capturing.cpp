// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -emit-pch -o %t
// RUN: %driver -cc1 %isys %s -std=c++11 -include-pch %t %target -o %t%output-suffix && %filecheck

#ifndef HEADER
#define HEADER

typedef __INTPTR_TYPE__ intptr_t;


void g(intptr_t n) {
  intptr_t buffer[n];
  [&buffer, &n]() {
    __typeof(buffer) x;
  }();
}


template <typename T>
void f(T n, T m) {
  intptr_t buffer[n + m];
  [&buffer]() {
    __typeof(buffer) x;
  }();
}

template <typename T>
intptr_t getSize(T);

template <typename T>
void b(intptr_t n, T arg) {
  typedef intptr_t ArrTy[getSize(arg)];
  ArrTy buffer2;
  ArrTy buffer1[n + arg];
  intptr_t a;
  [&]() {
    n = sizeof(buffer1[n]);
    [&](){
      n = sizeof(buffer2);
      n = sizeof(buffer1);
    }();
  }();
}

int main() {
  g((intptr_t)1);
  f((intptr_t)1, (intptr_t)2);
  b((intptr_t)12, (intptr_t)13);
  return 0;
}




#endif
