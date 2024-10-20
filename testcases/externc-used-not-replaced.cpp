// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" {
  const char a __attribute__((used)){};
}

// CHECK: @a = internal constant i8 0
// CHECK: @llvm.used = appending global [1 x ptr] [ptr @a]
