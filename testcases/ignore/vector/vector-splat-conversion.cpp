// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck

typedef __attribute__((__ext_vector_type__(8))) float vector_float8;

typedef vector_float8 float8;

void MandelbrotPolyCalcSIMD8() {
  constexpr float8 v4 = 4.0;  // value to compare against abs(z)^2, to see if bounded
  float8 vABS;
  auto vLT  = vABS < v4;
}

typedef __attribute__((__ext_vector_type__(4))) int int4;
typedef __attribute__((__ext_vector_type__(4))) float float4;
typedef __attribute__((__ext_vector_type__(4))) __int128 bigint4;

void BoolConversion() {
  int4 intsT = (int4)true;
  int4 intsF = (int4)false;
  float4 floatsT = (float4)true;
  float4 floatsF = (float4)false;
  bigint4 bigintsT = (bigint4)true;
  bigint4 bigintsF = (bigint4)false;

  constexpr int4 cIntsT = (int4)true;
  constexpr int4 cIntsF = (int4)false;
  constexpr float4 cFloatsT = (float4)true;
  constexpr float4 cFloatsF = (float4)false;
  constexpr bigint4 cBigintsT = (bigint4)true;
  constexpr bigint4 cBigintsF = (bigint4)false;
}

typedef __attribute__((vector_size(8))) int gcc_int_2;
gcc_int_2 FloatToIntConversion(gcc_int_2 Int2, float f) {
  return Int2 + f;
}
