// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" void followup_outer(int n, int *x) {
#pragma clang loop pipeline_initiation_interval(10)
#pragma clang loop unroll_count(4)
#pragma unroll_and_jam
#pragma clang loop vectorize(assume_safety)
#pragma clang loop distribute(enable)
  for(int j = 0; j < n; j++) {
    x[j] = 10;
  }
}








