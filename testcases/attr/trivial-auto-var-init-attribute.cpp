// RUN: %driver -cc1 %isys -fblocks %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fblocks -ftrivial-auto-var-init=pattern %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fblocks -ftrivial-auto-var-init=zero %s %target -o %t%output-suffix && %filecheck

template<typename T> void used(T &) noexcept;

extern "C" {

void test_attribute_uninitialized() {
  [[clang::uninitialized]] int i;
  used(i);
}

#pragma clang attribute push([[clang::uninitialized]], apply_to = variable(is_local))
void test_pragma_attribute_uninitialized() {
  int i;
  used(i);
}
#pragma clang attribute pop

} // extern "C"
