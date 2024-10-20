// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++2a -fsanitize=shift-base,shift-exponent %s %target -o %t%output-suffix && %filecheck

// CHECK-LABEL: @_Z12lsh_overflow
int lsh_overflow(int a, int b) {
  // SANITIZED: %[[RHS_INBOUNDS:.*]] = icmp ule i32 %[[RHS:.*]], 31
  // SANITIZED-NEXT: br i1 %[[RHS_INBOUNDS]], label %[[VALID:.*]], label

  // SANITIZED: call void @__ubsan_handle_shift_out_of_bounds

  // No check for the LHS here.
  // SANITIZED: [[VALID]]:
  // SANITIZED-NEXT: shl i32 %
  // SANITIZED-NEXT: ret i32

  // Just ensure there's no nsw nuw flags here.
  // REGULAR: shl i32 %
  return a << b;
}
