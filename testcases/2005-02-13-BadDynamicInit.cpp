// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// This testcase corresponds to PR509
struct Data {
  unsigned *data;
  unsigned array[1];
};

// CHECK-NOT: llvm.global_ctors
Data shared_null = { shared_null.array };
