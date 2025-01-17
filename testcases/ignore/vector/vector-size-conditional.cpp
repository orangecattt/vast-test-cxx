// RUN: %driver -cc1 %isys %s -Wno-unused -std=c++11 %target -o %t%output-suffix && %filecheck

using FourShorts = short __attribute__((__vector_size__(8)));
using TwoInts = int __attribute__((__vector_size__(8)));
using TwoUInts = unsigned __attribute__((__vector_size__(8)));
using FourInts = int __attribute__((__vector_size__(16)));
using FourUInts = unsigned __attribute__((__vector_size__(16)));
using TwoLongLong = long long __attribute__((__vector_size__(16)));
using FourLongLong = long long __attribute__((__vector_size__(32)));
using TwoFloats = float __attribute__((__vector_size__(8)));
using FourFloats = float __attribute__((__vector_size__(16)));
using TwoDoubles = double __attribute__((__vector_size__(16)));
using FourDoubles = double __attribute__((__vector_size__(32)));

FourShorts four_shorts;
TwoInts two_ints;
TwoUInts two_uints;
FourInts four_ints;
FourUInts four_uints;
TwoLongLong two_ll;
FourLongLong four_ll;
TwoFloats two_floats;
FourFloats four_floats;
TwoDoubles two_doubles;
FourDoubles four_doubles;

short some_short;
unsigned short some_ushort;
int some_int;
float some_float;
unsigned int some_uint;
long long some_ll;
unsigned long long some_ull;
double some_double;

void TwoVectorOps() {
  two_ints ? two_ints : two_ints;

  two_ints ? two_floats : two_floats;

  two_ll ? two_doubles : two_doubles;
}

void TwoScalarOps() {
  four_shorts ? some_short : some_short;

  four_shorts ? some_ushort : some_ushort;

  four_ints ? some_ushort : some_short;

  four_ints ? some_int : some_float;

  four_ll ? some_double : some_ll;

  four_ints ? some_int : some_short;
}

void OneScalarOp() {
  four_ints ? four_ints : some_int;

  four_ints ? four_ints : 5;

  four_ints ?: some_float;

  four_ints ? four_ints : 5.0f;

  four_ints ? some_float : four_ints;

  four_ints ? four_floats : some_float;

  four_ll ? four_doubles : 6.0;

  four_ll ? four_ll : 6.0;

  four_ll ? four_ll : 6;

  four_ll ? four_ll : some_int;

  four_ll ? four_ll : some_ll;

  four_ll ? four_ll : some_double;
}
