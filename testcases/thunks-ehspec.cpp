// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions %s -funwind-tables=2 %target -o %t%output-suffix && %filecheck

// When generating the thunk for secondary, do not push terminate scopes for
// either the varargs or non-varargs case. Related to PR44987.

struct A {
  virtual void primary_key();
};
struct B {
  virtual void secondary();
  virtual void secondary_vararg(int, ...);
};
class C : A, B {
  virtual void primary_key();
  void secondary() noexcept;
  void secondary_vararg(int, ...) noexcept;
};
void C::primary_key() {}

// CHECK-LABEL: define available_externally void @_ZThn8_N1C9secondaryEv(ptr noundef %this) {{.*}} #2
// CHECK-NOT: invoke
// CHECK: tail call void @_ZN1C9secondaryEv(ptr {{[^,]*}} %{{.*}})
// CHECK-NOT: invoke
// CHECK: ret void

// CHECK-LABEL: define available_externally void @_ZThn8_N1C16secondary_varargEiz(ptr noundef %this, i32 noundef %0, ...) {{.*}} #2
// CHECK-NOT: invoke
// CHECK:  musttail call void (ptr, i32, ...) @_ZN1C16secondary_varargEiz(ptr {{[^,]*}} %{{.*}}, i32 noundef %{{.*}}, ...) #3
// CHECK-NEXT:  ret void
