// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -exception-model=dwarf -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -exception-model=seh -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -exception-model=sjlj -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck

// ignore: %clang_cc1 -triple i686-unknown-windows-msvc -D __SEH_EXCEPTIONS__ -fms-extensions -fexceptions -fcxx-exceptions -S -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-WIN-SEH-X86
// ignore: %clang_cc1 -triple x86_64-unknown-windows-msvc -D __SEH_EXCEPTIONS__ -fms-extensions -fexceptions -fcxx-exceptions -S -emit-llvm %s -o - | FileCheck %s -check-prefix CHECK-WIN-SEH-X64




extern void g();

// CHECK-GNU: personality ptr @__gxx_personality_v0
// CHECK-GNU-DWARF: personality ptr @__gxx_personality_v0
// CHECK-GNU-SEH: personality ptr @__gxx_personality_seh0
// CHECK-GNU-SJLJ: personality ptr @__gxx_personality_sj0

// CHECK-WIN: personality ptr @__CxxFrameHandler3

// CHECK-AIX: personality ptr @__xlcxx_personality_v1

// CHECK-ZOS: personality ptr @__zos_cxx_personality_v2

void f() {
  try {
    g();
  } catch (...) {
  }
}

#if defined(__SEH_EXCEPTIONS__)
// CHECK-WIN-SEH-X86: personality ptr @_except_handler3
// CHECK-WIN-SEH-X64: personality ptr @__C_specific_handler

void h(void) {
  __try {
    g();
  } __finally {
  }
}
#endif

