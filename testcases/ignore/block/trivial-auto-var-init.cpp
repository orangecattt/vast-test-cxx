// RUN: %driver -cc1 %isys -fblocks %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fblocks -ftrivial-auto-var-init=pattern %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fblocks -ftrivial-auto-var-init=zero %s %target -o %t%output-suffix && %filecheck


template<typename T> void used(T &) noexcept;

extern "C" {

void test_selfinit() {
  int self = self + 1;
  used(self);
}

void test_block() {
  __block int block;
  used(block);
}

using Block = void (^)();
typedef struct XYZ {
  Block block;
} * xyz_t;
void test_block_self_init() {
  extern xyz_t create(Block block);
  __block xyz_t captured = create(^() {
    used(captured);
  });
}

void test_block_captures_self_after_init() {
  extern xyz_t create(Block block);
  __block xyz_t captured;
  captured = create(^() {
    used(captured);
  });
}

void test_goto_unreachable_value() {
  goto jump;
  int oops;
 jump:
  used(oops);
}

void test_goto(int i) {
  if (i)
    goto jump;
  int oops;
 jump:
  used(oops);
}

void test_switch(int i) {
  switch (i) {
  case 0:
    int oops;
    break;
  case 1:
    used(oops);
  }
}

void test_vla(int size) {
  int vla[size];
  int *ptr = vla;
  used(ptr);
}

void test_alloca(int size) {
  void *ptr = __builtin_alloca(size);
  used(ptr);
}

void test_alloca_with_align(int size) {
  void *ptr = __builtin_alloca_with_align(size, 1024);
  used(ptr);
}

void test_alloca_uninitialized(int size) {
  void *ptr = __builtin_alloca_uninitialized(size);
  used(ptr);
}

void test_alloca_with_align_uninitialized(int size) {
  void *ptr = __builtin_alloca_with_align_uninitialized(size, 1024);
  used(ptr);
}

void test_struct_vla(int size) {
  struct {
    float f;
    char c;
    void *ptr;
  } vla[size];
  void *ptr = static_cast<void*>(vla);
  used(ptr);
}

void test_zsa(int size) {
  int zsa[0];
  used(zsa);
}

void test_huge_uninit() {
  char big[65536];
  used(big);
}

void test_huge_small_init() {
  char big[65536] = { 'a', 'b', 'c', 'd' };
  used(big);
}

void test_huge_larger_init() {
  char big[65536] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
  used(big);
}

} // extern "C"

