// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -funwind-tables=1 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -funwind-tables=2 %s %target -o %t%output-suffix && %filecheck

void caller(void callback()) noexcept { callback(); }

// CHECK: define {{.*}}void @__clang_call_terminate({{[^)]*}}) #[[#ATTRNUM:]]
// CHECK: attributes #[[#ATTRNUM]] = {
// NOUNWIND-NOT: uwtable
// NOUNWIND-SAME: }
// SYNCUNWIND-SAME: uwtable(sync)
// ASYNCUNWIND-SAME: uwtable{{ }}
