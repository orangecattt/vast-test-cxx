// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace N {
  void free(void *i) {}
}

int main(void) {
  void *fp __attribute__((cleanup(N::free)));
  return 0;
}
