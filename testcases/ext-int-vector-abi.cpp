// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -I%S %s %target -o %t%output-suffix && %filecheck



using int8_t3 = _BitInt(8)  __attribute__((ext_vector_type(3)));
int8_t3 ManglingTestRetParam(int8_t3 Param) {
  return Param;
}
using int8_t3c = char  __attribute__((ext_vector_type(3)));
int8_t3c ManglingTestRetParam(int8_t3c Param) {
  return Param;
}

typedef unsigned _BitInt(16) uint16_t4 __attribute__((ext_vector_type(4)));
uint16_t4 ManglingTestRetParam(uint16_t4 Param) {
  return Param;
}

typedef unsigned short uint16_t4s __attribute__((ext_vector_type(4)));
uint16_t4s ManglingTestRetParam(uint16_t4s Param) {
  return Param;
}

typedef unsigned _BitInt(32) uint32_t4 __attribute__((ext_vector_type(4)));
uint32_t4 ManglingTestRetParam(uint32_t4 Param) {
  return Param;
}

typedef unsigned int uint32_t4s __attribute__((ext_vector_type(4)));
uint32_t4s ManglingTestRetParam(uint32_t4s Param) {
  return Param;
}

typedef unsigned _BitInt(64) uint64_t4 __attribute__((ext_vector_type(4)));
uint64_t4 ManglingTestRetParam(uint64_t4 Param) {
  return Param;
}

typedef unsigned long long uint64_t4s __attribute__((ext_vector_type(4)));
uint64_t4s ManglingTestRetParam(uint64_t4s Param) {
  return Param;
}

typedef _BitInt(32) vint32_t8 __attribute__((vector_size(32)));
vint32_t8 ManglingTestRetParam(vint32_t8 Param) {
  return Param;
}

typedef int vint32_t8i __attribute__((vector_size(32)));
vint32_t8i ManglingTestRetParam(vint32_t8i Param) {
  return Param;
}

typedef unsigned _BitInt(64) uvint64_t16 __attribute__((vector_size(16)));
uvint64_t16 ManglingTestRetParam(uvint64_t16 Param) {
  return Param;
}
using uvint64_t16l = unsigned long long  __attribute__((vector_size(16)));
uvint64_t16l ManglingTestRetParam(uvint64_t16l Param) {
  return Param;
}
