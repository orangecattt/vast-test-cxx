// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" void followup_inner(int n, int *x) {
#pragma unroll_and_jam(4)
  for(int j = 0; j < n; j++) {
#pragma clang loop pipeline_initiation_interval(10)
#pragma clang loop unroll_count(4)
#pragma clang loop vectorize(assume_safety)
#pragma clang loop distribute(enable)
    for(int i = 0; i < n; i++)
      x[j+i*n] = 10;

  }
}








