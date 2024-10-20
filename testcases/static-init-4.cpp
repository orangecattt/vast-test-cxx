// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

typedef __attribute__((vector_size(4*4))) float float32x4_t;
union QDSUnion { float32x4_t q; float s[4]; };
constexpr float32x4_t a = {1,2,3,4};
QDSUnion t = {{(a)}};
// CHECK: @t ={{.*}} global %union.QDSUnion { <4 x float> <float 1.000000e+00, float 2.000000e+00, float 3.000000e+00, float 4.000000e+00> }
