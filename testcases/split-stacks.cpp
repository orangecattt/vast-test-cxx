// RUN: %driver -fsplit-stack -std=c++11 %s %target -S -o %t%output-suffix && %filecheck
// RUN: %driver -std=c++11 %s %target -S -o %t%output-suffix && %filecheck

int foo() {
  return 0;
}

template <typename T>
[[gnu::no_split_stack]]
int tnosplit() {
  return 0;
}

[[gnu::no_split_stack]]
int nosplit() {
  return tnosplit<int>();
}

// CHECK-SEGSTK: define dso_local noundef i32 @_Z3foov() [[SS:#[0-9]+]] {
// CHECK-SEGSTK: define dso_local noundef i32 @_Z7nosplitv() [[NSS1:#[0-9]+]] {
// CHECK-SEGSTK: define linkonce_odr dso_local noundef i32 @_Z8tnosplitIiEiv() [[NSS2:#[0-9]+]] comdat {
// CHECK-SEGSTK-NOT: [[NSS1]] = { {{.*}} "split-stack" {{.*}} }
// CHECK-SEGSTK-NOT: [[NSS2]] = { {{.*}} "split-stack" {{.*}} }
// CHECK-SEGSTK: [[SS]] = { {{.*}} "split-stack" {{.*}} }
// CHECK-SEGSTK-NOT: [[NSS1]] = { {{.*}} "split-stack" {{.*}} }
// CHECK-SEGSTK-NOT: [[NSS2]] = { {{.*}} "split-stack" {{.*}} }

// CHECK-NOSEGSTK: define dso_local noundef i32 @_Z3foov() [[NSS0:#[0-9]+]] {
// CHECK-NOSEGSTK: define dso_local noundef i32 @_Z7nosplitv() [[NSS1:#[0-9]+]] {
// CHECK-NOSEGSTK: define linkonce_odr dso_local noundef i32 @_Z8tnosplitIiEiv() [[NSS0]] comdat {
// CHECK-NOSEGSTK-NOT: [[NSS0]] = { {{.*}} "split-stack" {{.*}} }
// CHECK-NOSEGSTK-NOT: [[NSS1]] = { {{.*}} "split-stack" {{.*}} }
