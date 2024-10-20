// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s -discard-value-names %target -o %t%output-suffix && %filecheck

extern "C" void branch();

bool test(bool pred) {
  // DISCARDVALUE: br i1 %0, label %2, label %3
  // CHECK: br i1 %pred, label %if.then, label %if.end

  if (pred) {
    // DISCARDVALUE: 2:
    // DISCARDVALUE-NEXT: call void @branch()
    // DISCARDVALUE-NEXT: br label %3

    // CHECK: if.then:
    // CHECK-NEXT: call void @branch()
    // CHECK-NEXT: br label %if.end
    branch();
  }

  // DISCARDVALUE: 3:
  // DISCARDVALUE-NEXT: ret i1 %0

  // CHECK: if.end:
  // CHECK-NEXT: ret i1 %pred
  return pred;
}
