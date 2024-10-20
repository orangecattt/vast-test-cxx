// RUN: %driver -cc1 %isys -fnew-infallible %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-new-infallible -fnew-infallible %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-new-infallible %s %target -o %t%output-suffix && %filecheck

// CHECK: call noalias noundef nonnull ptr @_Znwm(i64 noundef 4)

// CHECK: ; Function Attrs: nobuiltin nounwind allocsize(0)
// CHECK-NEXT: declare noundef nonnull ptr @_Znwm(i64 noundef)

// NO-NEW-INFALLIBLE: call noalias noundef nonnull ptr @_Znwm(i64 noundef 4)

// NO-NEW-INFALLIBLE: ; Function Attrs: nobuiltin allocsize(0)
// NO-NEW-INFALLIBLE-NEXT: declare noundef nonnull ptr @_Znwm(i64 noundef)

int *new_infallible = new int;
