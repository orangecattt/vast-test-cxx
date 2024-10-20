// RUN: %driver -cc1 %isys %s -std=c++2a %target -o %t%output-suffix && %filecheck

int *const &p = new int;

struct d {
  constexpr d(int &&f) : e(f) {}
  int &e;
};

d &&g{{0}};

