// RUN: %driver -cc1 %isys -std=c++11 -fopenmp -fexceptions -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck


void ffcomplex (int a) {
  double _Complex dc = (double)a;

  dc *= dc;
  #pragma omp parallel
  {
    dc *= dc;
  }
}


void fnoexcp(void) noexcept;

void foo(int a, int b) {

  void (*fptr)(void) noexcept = fnoexcp;

  #pragma omp parallel
  {
    fptr();
  }
}

