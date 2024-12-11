// RUN: %driver -cc1 %isys --std=c++17 %s %target -o %t%output-suffix && %filecheck

struct stream {
  friend const stream &operator<<(const stream &, const float &);
};

void foo() {
  constexpr float f_zero = 0.0f;
  constexpr float f_one = 1.0f;
  constexpr float f_two = 2.0f;

  stream s;
  [=]() {
    s << f_zero << f_one << f_two;
  }();
}


