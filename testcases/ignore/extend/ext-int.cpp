// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -I%S %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -no-enable-noundef-analysis -I%S -new-struct-path-tbaa %s %target -o %t%output-suffix && %filecheck




namespace std {
  class type_info { public: virtual ~type_info(); private: const char * name; };
} // namespace std

struct BitFieldsByte {
  _BitInt(7) A : 3;
  _BitInt(7) B : 3;
  _BitInt(7) C : 2;
};

struct BitFieldsShort {
  _BitInt(15) A : 3;
  _BitInt(15) B : 3;
  _BitInt(15) C : 2;
};

struct BitFieldsInt {
  _BitInt(31) A : 3;
  _BitInt(31) B : 3;
  _BitInt(31) C : 2;
};

struct BitFieldsLong {
  _BitInt(63) A : 3;
  _BitInt(63) B : 3;
  _BitInt(63) C : 2;
};

struct HasBitIntFirst {
  _BitInt(35) A;
  int B;
};

struct HasBitIntLast {
  int A;
  _BitInt(35) B;
};

struct HasBitIntMiddle {
  int A;
  _BitInt(35) B;
  int C;
};

void StructEmit() {
  BitFieldsByte A;
  BitFieldsShort B;
  BitFieldsInt C;
  BitFieldsLong D;

  HasBitIntFirst E;
  HasBitIntLast F;
  HasBitIntMiddle G;
}

void BitfieldAssignment() {
  BitFieldsByte B;
  B.A = 3;
  B.B = 2;
  B.C = 1;
}

unsigned _BitInt(33) ManglingTestRetParam(unsigned _BitInt(33) Param) {
  return 0;
}

_BitInt(33) ManglingTestRetParam(_BitInt(33) Param) {
  return 0;
}

typedef unsigned _BitInt(16) uint16_t4 __attribute__((ext_vector_type(4)));
typedef _BitInt(32) vint32_t8 __attribute__((vector_size(32)));

template<typename T>
void ManglingTestTemplateParam(T&);
template<_BitInt(99) T>
void ManglingTestNTTP();
template <int N>
auto ManglingDependent() -> decltype(_BitInt(N){});

void ManglingInstantiator() {
  _BitInt(93) A;
  ManglingTestTemplateParam(A);
  constexpr _BitInt(93) B = 993;
  ManglingTestNTTP<38>();
  ManglingTestNTTP<B>();
  ManglingDependent<4>();
  uint16_t4 V;
  ManglingTestTemplateParam(V);

}

void TakesVarargs(int i, ...) {

  __builtin_va_list args;
  __builtin_va_start(args, i);

  _BitInt(92) A = __builtin_va_arg(args, _BitInt(92));





  _BitInt(31) B = __builtin_va_arg(args, _BitInt(31));




  _BitInt(16) C = __builtin_va_arg(args, _BitInt(16));




  uint16_t4 D = __builtin_va_arg(args, uint16_t4);



  vint32_t8 E = __builtin_va_arg(args, vint32_t8);





  __builtin_va_end(args);
}
void typeid_tests() {
  unsigned _BitInt(33) U33_1, U33_2;
  _BitInt(33) S33_1, S33_2;
  _BitInt(32) S32_1, S32_2;

 auto A = typeid(U33_1);
 auto B = typeid(U33_2);
 auto C = typeid(S33_1);
 auto D = typeid(S33_2);
 auto E = typeid(S32_1);
 auto F = typeid(S32_2);
 auto G = typeid(uint16_t4);
 auto H = typeid(vint32_t8);
}

void ExplicitCasts() {

  _BitInt(33) a;
  _BitInt(31) b;
  int i;

  a = i;
  b = i;
  i = a;
  i = b;
  uint16_t4 c;
  c = i;
}

struct S {
  _BitInt(17) A;
  _BitInt(128) B;
  _BitInt(17) C;
  uint16_t4 D;
  vint32_t8 E;
};

void OffsetOfTest() {

  auto A = __builtin_offsetof(S,A);
  auto B = __builtin_offsetof(S,B);
  auto C = __builtin_offsetof(S,C);
  auto D = __builtin_offsetof(S,D);
  auto E = __builtin_offsetof(S,E);
}


void ShiftBitIntByConstant(_BitInt(28) Ext) {
  Ext << 7;
  Ext >> 7;
  Ext << -7;
  Ext >> -7;

  Ext << 29;
  Ext >> 29;
}
void ShiftBitIntByConstant(uint16_t4 Ext) {
  Ext << 7;
  Ext >> 7;
  Ext << -7;
  Ext >> -7;

  Ext << 29;
  Ext >> 29;
}
void ShiftBitIntByConstant(vint32_t8 Ext) {
  Ext << 7;
  Ext >> 7;
  Ext << -7;
  Ext >> -7;

  Ext << 29;
  Ext >> 29;
}

void ConstantShiftByBitInt(_BitInt(28) Ext, _BitInt(65) LargeExt) {
  10 << Ext;
  10 >> Ext;
  10 << LargeExt;
  10 >> LargeExt;
}

void Shift(_BitInt(28) Ext, _BitInt(65) LargeExt, int i) {
  i << Ext;
  i >> Ext;

  i << LargeExt;
  i >> LargeExt;

  Ext << i;
  Ext >> i;

  LargeExt << i;
  LargeExt >> i;

  Ext << LargeExt;
  Ext >> LargeExt;

  LargeExt << Ext;
  LargeExt >> Ext;
}

void ComplexTest(_Complex _BitInt(12) first, _Complex _BitInt(33) second) {
  first + second;
}

typedef  _BitInt(64) vint64_t16 __attribute__((vector_size(16)));
void VectorTest(vint64_t16 first, vint64_t16 second) {
  __builtin_shufflevector (first, first, 1, 3, 2) + __builtin_shufflevector (second, second, 1, 3, 2);
}

void VectorTest(uint16_t4 first, uint16_t4 second) {
  first.xzw + second.zwx;
}

void TBAATest(_BitInt(sizeof(int) * 8) ExtInt,
              unsigned _BitInt(sizeof(int) * 8) ExtUInt,
              _BitInt(6) Other) {
  ExtInt = 5;
  ExtUInt = 5;
  Other = 5;
}


