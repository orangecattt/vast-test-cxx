// RUN: %driver -cc1 %isys -DREDECL %s %target -o %t%output-suffix && %filecheck
// ignore: %clang_cc1 -triple spir-unknown-unknown -DREDECL -DSPIR -emit-llvm %s -o - | FileCheck %s -check-prefix SPIR
// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// ignore: %clang_cc1 -triple spir-unknown-unknown -DSPIR -emit-llvm %s -o - | FileCheck %s -check-prefix SPIR
// ignore: %clang_cc1 -triple i386-windows-pc -fdefault-calling-conv=stdcall -emit-llvm %s -o - | FileCheck %s -check-prefix WIN32

#ifdef REDECL
namespace std {
#ifdef SPIR
using size_t = unsigned int;
#else
using size_t = unsigned long;
#endif // SPIR
} // namespace std

float __builtin_atan2f(float, float);
void *operator new(std::size_t);
#endif // REDECL

void foo();

void user() {
  int i;
  ::operator new(5);
  (void)__builtin_atan2f(1.1, 2.2);
  foo();
}

// LINUX: define{{.*}} void @_Z4userv()
// LINUX: call noalias noundef nonnull ptr @_Znwm
// LINUX: call float @atan2f
// LINUX: call void @_Z3foov
// LINUX: declare noundef nonnull ptr @_Znwm(i64 noundef)
// LINUX: declare float @atan2f(float noundef, float noundef)
// LINUX: declare void @_Z3foov()

// SPIR: define{{.*}} spir_func void @_Z4userv()
// SPIR: call spir_func noalias noundef nonnull ptr @_Znwj
// SPIR: call spir_func float @atan2f
// SPIR: call spir_func void @_Z3foov
// SPIR: declare spir_func noundef nonnull ptr @_Znwj(i32 noundef)
// SPIR: declare spir_func float @atan2f(float noundef, float noundef)
// SPIR: declare spir_func void @_Z3foov()

// Note: Windows /G options should not change the platform default calling
// convention of builtins.
// WIN32: define dso_local x86_stdcallcc void @"?user@@YGXXZ"()
// WIN32: call noalias noundef nonnull ptr @"??2@YAPAXI@Z"
// WIN32: call float @atan2f
// WIN32: call x86_stdcallcc void @"?foo@@YGXXZ"
// WIN32: declare dso_local noundef nonnull ptr @"??2@YAPAXI@Z"(
// WIN32: declare dso_local float @atan2f(float noundef, float noundef)
// WIN32: declare dso_local x86_stdcallcc void @"?foo@@YGXXZ"()
