// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Test that destructors are not passed directly to __cxa_atexit when their
// signatures do not match the type of its first argument.
// e.g. ARM and WebAssembly have destructors that return this instead of void.


class Foo {
 public:
  ~Foo() {
  }
};

Foo global;

// X86 destructors have void return, and are registered directly with __cxa_atexit.
// X86: define internal void @__cxx_global_var_init()
// X86:   call i32 @__cxa_atexit(ptr @_ZN3FooD1Ev, ptr @global, ptr @__dso_handle)

// ARM destructors return this, but can be registered directly with __cxa_atexit
// because the calling conventions tolerate the mismatch.
// ARM: define internal void @__cxx_global_var_init()
// ARM:   call i32 @__cxa_atexit(ptr @_ZN3FooD1Ev, ptr @global, ptr @__dso_handle)

// Wasm destructors return this, and use a wrapper function, which is registered
// with __cxa_atexit.
// WASM: define internal void @__cxx_global_var_init()
// WASM: call i32 @__cxa_atexit(ptr @__cxx_global_array_dtor, ptr null, ptr @__dso_handle)

// WASM: define internal void @__cxx_global_array_dtor(ptr noundef %0)
// WASM: %call = call noundef ptr @_ZN3FooD1Ev(ptr {{[^,]*}} @global)
