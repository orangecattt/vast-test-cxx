// RUN: %driver -cc1 %isys -fdump-record-layouts -std=c++17 %s %target -o %t%output-suffix && %filecheck


class Empty {};

class Second : Empty {
  short A : 1;
};

class Foo : Empty {
  [[no_unique_address]] Second NZNoUnique;
  char B;
};
Foo I;

class SecondEmpty: Empty {
};


class Bar : Empty {
  [[no_unique_address]] SecondEmpty ZNoUnique;
  char C;
};
Bar J;


class IntFieldClass : Empty {
  [[no_unique_address]] Second Field;
  int C;
};
IntFieldClass K;


class UnionClass : Empty {
  [[no_unique_address]] union {
    int I;
    char C;
  } U;
  int C;
};
UnionClass L;


class EnumClass : Empty {
  [[no_unique_address]] enum class E { X, Y, Z } A;
  int C;
};
EnumClass M;


class NoBaseField : Empty {
  [[no_unique_address]] Empty A;
  int B;
};
NoBaseField N;


class FinalEmpty final {};
class FinalClass final : Empty {
  [[no_unique_address]] FinalEmpty A;
  int B;
} O;



class Union2Class : Empty {
  [[no_unique_address]] union PaddedUnion {
  private:
    Empty A;
    alignas(2) char B;
  } U;
  char C;
} P;



struct NotEmptyWithBitfield : Empty {
  char A[2];
  int B : 1;
};
struct C {
  [[no_unique_address]] union {
    short C;
    [[no_unique_address]] NotEmptyWithBitfield A;
  } U;
} Q;
