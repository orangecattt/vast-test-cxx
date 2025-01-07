// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


struct k {
  ~k() __attribute__((annotate(""))) {}
};
void m() { k(); }

