// RUN: %driver -cc1 %isys -std=c++11 -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fcxx-exceptions -fexceptions -fclang-abi-compat=4.0 %s %target -o %t%output-suffix && %filecheck


struct __attribute__((trivial_abi)) Small {
  int *p;
  Small();
  ~Small();
  Small(const Small &) noexcept;
  Small &operator=(const Small &);
};

struct __attribute__((trivial_abi)) Large {
  int *p;
  int a[128];
  Large();
  ~Large();
  Large(const Large &) noexcept;
  Large &operator=(const Large &);
};

struct Trivial {
  int a;
};

struct NonTrivial {
  NonTrivial();
  ~NonTrivial();
  int a;
};

struct HasTrivial {
  Small s;
  Trivial m;
};

struct HasNonTrivial {
  Small s;
  NonTrivial m;
};

struct B0 {
  virtual Small m0();
};

struct B1 {
  virtual Small m0();
};

struct D0 : B0, B1 {
  Small m0() override;
};


Small D0::m0() { return {}; }


void testParamSmall(Small a) noexcept {
}


Small testReturnSmall() {
  Small t;
  return t;
}


void testCallSmall0() {
  Small t;
  testParamSmall(t);
}


void testCallSmall1() {
  testParamSmall(testReturnSmall());
}


void testIgnoredSmall() {
  testReturnSmall();
}


void testParamLarge(Large a) noexcept {
}


Large testReturnLarge() {
  Large t;
  return t;
}


void testCallLarge0() {
  Large t;
  testParamLarge(t);
}


void testCallLarge1() {
  testParamLarge(testReturnLarge());
}


void testIgnoredLarge() {
  testReturnLarge();
}


Trivial testReturnHasTrivial() {
  Trivial t;
  return t;
}


NonTrivial testReturnHasNonTrivial() {
  NonTrivial t;
  return t;
}





void calleeExceptionSmall(Small, Small);

void testExceptionSmall() {
  calleeExceptionSmall(Small(), Small());
}





void calleeExceptionLarge(Large, Large);

void testExceptionLarge() {
  calleeExceptionLarge(Large(), Large());
}



Small (*fp)() = []() -> Small { return Small(); };
