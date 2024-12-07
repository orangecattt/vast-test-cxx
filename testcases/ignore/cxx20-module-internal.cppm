// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck


export module A;

static void addone() {}
static int x = 5;

namespace {
void frob() {}
int y = 2;
struct Bill {
  void F();
};
void Bill::F() {}
} // namespace

static void Frob(Bill *b) {
  if (b)
    b->F();
}

namespace N {
static void inner() {}
static int z = 3;
} // namespace N

void addsix() {
  Frob(nullptr);
  frob();
  addone();
  void(x + y + N::z);
  N::inner();
}
