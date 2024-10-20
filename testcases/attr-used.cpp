// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct X0 {
  __attribute__((used)) X0() {}
  __attribute__((used)) ~X0() {}
};

struct X1 {
  struct Nested {
    void __attribute__((used)) f() {}
  };
};

struct X2 {
  void __attribute__((used)) bar() { foo(); }
  void foo() { }

};
