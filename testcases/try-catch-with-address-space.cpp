// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck

struct X { };

const X g();

void f() {
  try {
    throw g();
    // CHECK: ptr addrspace(1) @_ZTI1X
  } catch (const X x) {
    // CHECK: catch ptr addrspace(1) @_ZTI1X
    // CHECK: call i32 @llvm.eh.typeid.for(ptr addrspacecast (ptr addrspace(1) @_ZTI1X to ptr))
  }
}

void h() {
  try {
    throw "ABC";
    // CHECK: ptr addrspace(1) @_ZTIPKc
  } catch (char const(&)[4]) {
    // CHECK: catch ptr addrspace(1) @_ZTIA4_c
    // CHECK: call i32 @llvm.eh.typeid.for(ptr addrspacecast (ptr addrspace(1) @_ZTIA4_c to ptr))
  }
}
