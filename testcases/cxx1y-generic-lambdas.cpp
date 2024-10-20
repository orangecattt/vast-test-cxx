// RUN: %driver -cc1 %isys %s -std=c++14 %target -o %t%output-suffix && %filecheck

template<typename> struct custom_copy_ctor {
  custom_copy_ctor() = default;
  custom_copy_ctor(custom_copy_ctor const &) {}
};

// CHECK: define {{.*}} @_ZN16custom_copy_ctorIvEC2ERKS0_(
void pr22354() {
  custom_copy_ctor<void> cc;
  [cc](auto){}(1);
}
