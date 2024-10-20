// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Test that this is not hidden.
// CHECK: @_ZTVN10__cxxabiv120__si_class_type_infoE = external global

class foo {
  virtual void baz();
};
struct __attribute__((__visibility__("hidden"))) bar : public foo {};
bar zed;
