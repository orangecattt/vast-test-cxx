// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck

struct X {
  ~X();
};

struct Error {
  Error(const X&) noexcept;
};

void f() {
  try {
    throw Error(X());
  } catch (...) { }
}

