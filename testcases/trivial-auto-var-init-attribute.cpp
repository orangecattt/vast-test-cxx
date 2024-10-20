// RUN: %driver -cc1 %isys -fblocks %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fblocks -ftrivial-auto-var-init=pattern %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fblocks -ftrivial-auto-var-init=zero %s %target -o %t%output-suffix && %filecheck

template<typename T> void used(T &) noexcept;

extern "C" {

// UNINIT-LABEL:  test_attribute_uninitialized(
// UNINIT:      alloca
// UNINIT-NEXT: call void
// ZERO-LABEL:    test_attribute_uninitialized(
// ZERO:      alloca
// ZERO-NOT:  !annotation
// ZERO-NEXT: call void
// PATTERN-LABEL: test_attribute_uninitialized(
// PATTERN:      alloca
// PATTERN-NOT:  !annotation
// PATTERN-NEXT: call void
void test_attribute_uninitialized() {
  [[clang::uninitialized]] int i;
  used(i);
}

#pragma clang attribute push([[clang::uninitialized]], apply_to = variable(is_local))
// UNINIT-LABEL:  test_pragma_attribute_uninitialized(
// UNINIT:      alloca
// UNINIT-NEXT: call void
// ZERO-LABEL:    test_pragma_attribute_uninitialized(
// ZERO:      alloca
// ZERO-NEXT: call void
// PATTERN-LABEL: test_pragma_attribute_uninitialized(
// PATTERN:      alloca
// PATTERN-NEXT: call void
void test_pragma_attribute_uninitialized() {
  int i;
  used(i);
}
#pragma clang attribute pop

} // extern "C"
